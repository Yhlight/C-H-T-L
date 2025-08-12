#include "v2/Js/JsParser.h"
#include <stdexcept>

namespace chtl::v2::js {

JsParser::JsParser(const std::string& source) : source_(source), current_(0) {
    JsTokenizer tokenizer(source);
    tokens_ = tokenizer.tokenize();
}

JsParseResult JsParser::parse() {
    JsParseResult result;
    
    try {
        result.ast = parseProgram();
        result.success = result.errors.empty();
    } catch (const std::exception& e) {
        result.errors.push_back(std::string("Parse error: ") + e.what());
        result.success = false;
    }
    
    return result;
}

std::shared_ptr<JsProgram> JsParser::parseProgram() {
    auto program = std::make_shared<JsProgram>();
    program->type = JsNodeType::PROGRAM;
    
    while (!isAtEnd()) {
        try {
            auto stmt = parseStatement();
            if (stmt) {
                program->body.push_back(stmt);
            }
        } catch (const std::exception& e) {
            // Error recovery: skip to next statement
            synchronize();
            errors_.push_back(e.what());
        }
    }
    
    return program;
}

std::shared_ptr<JsStatement> JsParser::parseStatement() {
    // Variable declarations
    if (match(JsTokenType::VAR) || match(JsTokenType::LET) || match(JsTokenType::CONST)) {
        return parseVariableDeclaration();
    }
    
    // Function declaration
    if (match(JsTokenType::FUNCTION)) {
        return parseFunctionDeclaration();
    }
    
    // Control flow
    if (match(JsTokenType::IF)) return parseIfStatement();
    if (match(JsTokenType::WHILE)) return parseWhileStatement();
    if (match(JsTokenType::FOR)) return parseForStatement();
    if (match(JsTokenType::RETURN)) return parseReturnStatement();
    if (match(JsTokenType::BREAK)) return parseBreakStatement();
    if (match(JsTokenType::CONTINUE)) return parseContinueStatement();
    
    // Try-catch
    if (match(JsTokenType::TRY)) return parseTryStatement();
    
    // Block
    if (check(JsTokenType::LEFT_BRACE)) {
        return parseBlockStatement();
    }
    
    // Expression statement
    return parseExpressionStatement();
}

std::shared_ptr<JsVariableDeclaration> JsParser::parseVariableDeclaration() {
    auto decl = std::make_shared<JsVariableDeclaration>();
    decl->type = JsNodeType::VARIABLE_DECLARATION;
    
    JsToken kindToken = previous();
    if (kindToken.type == JsTokenType::VAR) decl->kind = "var";
    else if (kindToken.type == JsTokenType::LET) decl->kind = "let";
    else if (kindToken.type == JsTokenType::CONST) decl->kind = "const";
    
    // Parse declarators
    do {
        JsVariableDeclarator declarator;
        
        // Pattern (for now just identifier)
        declarator.id = consume(JsTokenType::IDENTIFIER, "Expected variable name");
        
        // Initializer
        if (match(JsTokenType::EQUAL)) {
            declarator.init = parseExpression();
        } else if (decl->kind == "const") {
            throw std::runtime_error("Missing initializer in const declaration");
        }
        
        decl->declarations.push_back(declarator);
        
    } while (match(JsTokenType::COMMA));
    
    consume(JsTokenType::SEMICOLON, "Expected ';' after variable declaration");
    
    return decl;
}

std::shared_ptr<JsExpression> JsParser::parseExpression() {
    return parseAssignmentExpression();
}

std::shared_ptr<JsExpression> JsParser::parseAssignmentExpression() {
    auto expr = parseBinaryExpression();
    
    if (match(JsTokenType::EQUAL)) {
        auto value = parseAssignmentExpression();
        auto assign = std::make_shared<JsBinaryExpression>();
        assign->type = JsNodeType::ASSIGNMENT_EXPRESSION;
        assign->op = "=";
        assign->left = expr;
        assign->right = value;
        return assign;
    }
    
    return expr;
}

std::shared_ptr<JsExpression> JsParser::parseBinaryExpression(int minPrec) {
    auto left = parseUnaryExpression();
    
    while (!isAtEnd()) {
        JsToken op = peek();
        int prec = getBinaryPrecedence(op.type);
        
        if (prec < minPrec) break;
        
        advance(); // consume operator
        
        auto right = parseBinaryExpression(prec + 1);
        
        auto binary = std::make_shared<JsBinaryExpression>();
        binary->type = JsNodeType::BINARY_EXPRESSION;
        binary->op = op.lexeme;
        binary->left = left;
        binary->right = right;
        
        left = binary;
    }
    
    return left;
}

std::shared_ptr<JsExpression> JsParser::parseUnaryExpression() {
    if (match(JsTokenType::BANG) || match(JsTokenType::MINUS) || 
        match(JsTokenType::PLUS) || match(JsTokenType::TILDE) ||
        match(JsTokenType::TYPEOF) || match(JsTokenType::VOID) ||
        match(JsTokenType::DELETE)) {
        
        JsToken op = previous();
        auto expr = parseUnaryExpression();
        
        auto unary = std::make_shared<JsUnaryExpression>();
        unary->type = JsNodeType::UNARY_EXPRESSION;
        unary->op = op.lexeme;
        unary->argument = expr;
        unary->prefix = true;
        
        return unary;
    }
    
    return parsePostfixExpression();
}

std::shared_ptr<JsExpression> JsParser::parsePostfixExpression() {
    auto expr = parseCallExpression();
    
    if (match(JsTokenType::PLUS_PLUS) || match(JsTokenType::MINUS_MINUS)) {
        auto unary = std::make_shared<JsUnaryExpression>();
        unary->type = JsNodeType::UPDATE_EXPRESSION;
        unary->op = previous().lexeme;
        unary->argument = expr;
        unary->prefix = false;
        return unary;
    }
    
    return expr;
}

std::shared_ptr<JsExpression> JsParser::parseCallExpression() {
    auto expr = parseMemberExpression();
    
    while (true) {
        if (match(JsTokenType::LEFT_PAREN)) {
            // Function call
            auto call = std::make_shared<JsCallExpression>();
            call->type = JsNodeType::CALL_EXPRESSION;
            call->callee = expr;
            
            // Arguments
            if (!check(JsTokenType::RIGHT_PAREN)) {
                do {
                    call->arguments.push_back(parseExpression());
                } while (match(JsTokenType::COMMA));
            }
            
            consume(JsTokenType::RIGHT_PAREN, "Expected ')' after arguments");
            expr = call;
        }
        else if (match(JsTokenType::DOT)) {
            // Member access
            auto member = std::make_shared<JsMemberExpression>();
            member->type = JsNodeType::MEMBER_EXPRESSION;
            member->object = expr;
            member->property = std::make_shared<JsIdentifier>();
            member->property->name = consume(JsTokenType::IDENTIFIER, "Expected property name").lexeme;
            member->computed = false;
            expr = member;
        }
        else if (match(JsTokenType::LEFT_BRACKET)) {
            // Computed member access
            auto member = std::make_shared<JsMemberExpression>();
            member->type = JsNodeType::MEMBER_EXPRESSION;
            member->object = expr;
            member->property = parseExpression();
            member->computed = true;
            consume(JsTokenType::RIGHT_BRACKET, "Expected ']'");
            expr = member;
        }
        else {
            break;
        }
    }
    
    return expr;
}

std::shared_ptr<JsExpression> JsParser::parseMemberExpression() {
    return parsePrimaryExpression();
}

std::shared_ptr<JsExpression> JsParser::parsePrimaryExpression() {
    // Literals
    if (match(JsTokenType::TRUE)) {
        auto lit = std::make_shared<JsLiteral>();
        lit->type = JsNodeType::LITERAL;
        lit->value = true;
        return lit;
    }
    
    if (match(JsTokenType::FALSE)) {
        auto lit = std::make_shared<JsLiteral>();
        lit->type = JsNodeType::LITERAL;
        lit->value = false;
        return lit;
    }
    
    if (match(JsTokenType::NULL_LITERAL)) {
        auto lit = std::make_shared<JsLiteral>();
        lit->type = JsNodeType::LITERAL;
        lit->value = std::monostate{}; // null
        return lit;
    }
    
    if (match(JsTokenType::UNDEFINED)) {
        auto id = std::make_shared<JsIdentifier>();
        id->type = JsNodeType::IDENTIFIER;
        id->name = "undefined";
        return id;
    }
    
    if (match(JsTokenType::NUMBER)) {
        auto lit = std::make_shared<JsLiteral>();
        lit->type = JsNodeType::LITERAL;
        try {
            lit->value = std::stod(previous().lexeme);
        } catch (...) {
            lit->value = previous().lexeme; // Keep as string if conversion fails
        }
        return lit;
    }
    
    if (match(JsTokenType::STRING)) {
        auto lit = std::make_shared<JsLiteral>();
        lit->type = JsNodeType::LITERAL;
        std::string str = previous().lexeme;
        // Remove quotes
        if (str.length() >= 2) {
            str = str.substr(1, str.length() - 2);
        }
        lit->value = str;
        return lit;
    }
    
    if (match(JsTokenType::IDENTIFIER)) {
        auto id = std::make_shared<JsIdentifier>();
        id->type = JsNodeType::IDENTIFIER;
        id->name = previous().lexeme;
        return id;
    }
    
    if (match(JsTokenType::THIS)) {
        auto thisExpr = std::make_shared<JsThisExpression>();
        thisExpr->type = JsNodeType::THIS_EXPRESSION;
        return thisExpr;
    }
    
    // Parenthesized expression
    if (match(JsTokenType::LEFT_PAREN)) {
        auto expr = parseExpression();
        consume(JsTokenType::RIGHT_PAREN, "Expected ')' after expression");
        return expr;
    }
    
    // Array literal
    if (match(JsTokenType::LEFT_BRACKET)) {
        auto array = std::make_shared<JsArrayExpression>();
        array->type = JsNodeType::ARRAY_EXPRESSION;
        
        if (!check(JsTokenType::RIGHT_BRACKET)) {
            do {
                array->elements.push_back(parseExpression());
            } while (match(JsTokenType::COMMA));
        }
        
        consume(JsTokenType::RIGHT_BRACKET, "Expected ']'");
        return array;
    }
    
    // Object literal
    if (match(JsTokenType::LEFT_BRACE)) {
        auto obj = std::make_shared<JsObjectExpression>();
        obj->type = JsNodeType::OBJECT_EXPRESSION;
        
        if (!check(JsTokenType::RIGHT_BRACE)) {
            do {
                // Property
                JsProperty prop;
                
                if (match(JsTokenType::IDENTIFIER)) {
                    prop.key = std::make_shared<JsIdentifier>();
                    static_cast<JsIdentifier*>(prop.key.get())->name = previous().lexeme;
                } else if (match(JsTokenType::STRING)) {
                    prop.key = std::make_shared<JsLiteral>();
                    static_cast<JsLiteral*>(prop.key.get())->value = previous().lexeme;
                } else {
                    throw std::runtime_error("Expected property name");
                }
                
                consume(JsTokenType::COLON, "Expected ':' after property name");
                prop.value = parseExpression();
                
                obj->properties.push_back(prop);
                
            } while (match(JsTokenType::COMMA));
        }
        
        consume(JsTokenType::RIGHT_BRACE, "Expected '}'");
        return obj;
    }
    
    throw std::runtime_error("Unexpected token: " + peek().lexeme);
}

std::shared_ptr<JsFunction> JsParser::parseFunctionDeclaration() {
    auto func = std::make_shared<JsFunction>();
    func->type = JsNodeType::FUNCTION_DECLARATION;
    
    // Function name
    func->id = consume(JsTokenType::IDENTIFIER, "Expected function name").lexeme;
    
    // Parameters
    consume(JsTokenType::LEFT_PAREN, "Expected '(' after function name");
    
    if (!check(JsTokenType::RIGHT_PAREN)) {
        do {
            func->params.push_back(consume(JsTokenType::IDENTIFIER, "Expected parameter name").lexeme);
        } while (match(JsTokenType::COMMA));
    }
    
    consume(JsTokenType::RIGHT_PAREN, "Expected ')' after parameters");
    
    // Body
    func->body = parseBlockStatement();
    
    return func;
}

std::shared_ptr<JsBlockStatement> JsParser::parseBlockStatement() {
    auto block = std::make_shared<JsBlockStatement>();
    block->type = JsNodeType::BLOCK_STATEMENT;
    
    consume(JsTokenType::LEFT_BRACE, "Expected '{'");
    
    while (!check(JsTokenType::RIGHT_BRACE) && !isAtEnd()) {
        block->body.push_back(parseStatement());
    }
    
    consume(JsTokenType::RIGHT_BRACE, "Expected '}'");
    
    return block;
}

std::shared_ptr<JsIfStatement> JsParser::parseIfStatement() {
    auto ifStmt = std::make_shared<JsIfStatement>();
    ifStmt->type = JsNodeType::IF_STATEMENT;
    
    consume(JsTokenType::LEFT_PAREN, "Expected '(' after 'if'");
    ifStmt->test = parseExpression();
    consume(JsTokenType::RIGHT_PAREN, "Expected ')' after condition");
    
    ifStmt->consequent = parseStatement();
    
    if (match(JsTokenType::ELSE)) {
        ifStmt->alternate = parseStatement();
    }
    
    return ifStmt;
}

std::shared_ptr<JsWhileStatement> JsParser::parseWhileStatement() {
    auto whileStmt = std::make_shared<JsWhileStatement>();
    whileStmt->type = JsNodeType::WHILE_STATEMENT;
    
    consume(JsTokenType::LEFT_PAREN, "Expected '(' after 'while'");
    whileStmt->test = parseExpression();
    consume(JsTokenType::RIGHT_PAREN, "Expected ')' after condition");
    
    whileStmt->body = parseStatement();
    
    return whileStmt;
}

std::shared_ptr<JsForStatement> JsParser::parseForStatement() {
    auto forStmt = std::make_shared<JsForStatement>();
    forStmt->type = JsNodeType::FOR_STATEMENT;
    
    consume(JsTokenType::LEFT_PAREN, "Expected '(' after 'for'");
    
    // Init
    if (!check(JsTokenType::SEMICOLON)) {
        if (match(JsTokenType::VAR) || match(JsTokenType::LET) || match(JsTokenType::CONST)) {
            forStmt->init = parseVariableDeclaration();
            // Variable declaration already consumes semicolon
        } else {
            forStmt->init = parseExpression();
            consume(JsTokenType::SEMICOLON, "Expected ';' after for init");
        }
    } else {
        advance(); // consume semicolon
    }
    
    // Test
    if (!check(JsTokenType::SEMICOLON)) {
        forStmt->test = parseExpression();
    }
    consume(JsTokenType::SEMICOLON, "Expected ';' after for test");
    
    // Update
    if (!check(JsTokenType::RIGHT_PAREN)) {
        forStmt->update = parseExpression();
    }
    
    consume(JsTokenType::RIGHT_PAREN, "Expected ')' after for clauses");
    
    forStmt->body = parseStatement();
    
    return forStmt;
}

std::shared_ptr<JsReturnStatement> JsParser::parseReturnStatement() {
    auto ret = std::make_shared<JsReturnStatement>();
    ret->type = JsNodeType::RETURN_STATEMENT;
    
    if (!check(JsTokenType::SEMICOLON) && !isAtEnd()) {
        ret->argument = parseExpression();
    }
    
    consume(JsTokenType::SEMICOLON, "Expected ';' after return");
    
    return ret;
}

std::shared_ptr<JsBreakStatement> JsParser::parseBreakStatement() {
    auto brk = std::make_shared<JsBreakStatement>();
    brk->type = JsNodeType::BREAK_STATEMENT;
    
    consume(JsTokenType::SEMICOLON, "Expected ';' after break");
    
    return brk;
}

std::shared_ptr<JsContinueStatement> JsParser::parseContinueStatement() {
    auto cont = std::make_shared<JsContinueStatement>();
    cont->type = JsNodeType::CONTINUE_STATEMENT;
    
    consume(JsTokenType::SEMICOLON, "Expected ';' after continue");
    
    return cont;
}

std::shared_ptr<JsTryStatement> JsParser::parseTryStatement() {
    auto tryStmt = std::make_shared<JsTryStatement>();
    tryStmt->type = JsNodeType::TRY_STATEMENT;
    
    tryStmt->block = parseBlockStatement();
    
    if (match(JsTokenType::CATCH)) {
        auto handler = std::make_shared<JsCatchClause>();
        
        if (match(JsTokenType::LEFT_PAREN)) {
            handler->param = consume(JsTokenType::IDENTIFIER, "Expected parameter name").lexeme;
            consume(JsTokenType::RIGHT_PAREN, "Expected ')' after catch parameter");
        }
        
        handler->body = parseBlockStatement();
        tryStmt->handler = handler;
    }
    
    if (match(JsTokenType::FINALLY)) {
        tryStmt->finalizer = parseBlockStatement();
    }
    
    if (!tryStmt->handler && !tryStmt->finalizer) {
        throw std::runtime_error("Missing catch or finally after try");
    }
    
    return tryStmt;
}

std::shared_ptr<JsExpressionStatement> JsParser::parseExpressionStatement() {
    auto stmt = std::make_shared<JsExpressionStatement>();
    stmt->type = JsNodeType::EXPRESSION_STATEMENT;
    
    stmt->expression = parseExpression();
    consume(JsTokenType::SEMICOLON, "Expected ';' after expression");
    
    return stmt;
}

int JsParser::getBinaryPrecedence(JsTokenType type) {
    switch (type) {
        case JsTokenType::OR_OR: return 1;
        case JsTokenType::AND_AND: return 2;
        case JsTokenType::OR: return 3;
        case JsTokenType::XOR: return 4;
        case JsTokenType::AND: return 5;
        case JsTokenType::EQUAL_EQUAL:
        case JsTokenType::BANG_EQUAL:
        case JsTokenType::EQUAL_EQUAL_EQUAL:
        case JsTokenType::BANG_EQUAL_EQUAL: return 6;
        case JsTokenType::LESS:
        case JsTokenType::LESS_EQUAL:
        case JsTokenType::GREATER:
        case JsTokenType::GREATER_EQUAL:
        case JsTokenType::IN:
        case JsTokenType::INSTANCEOF: return 7;
        case JsTokenType::LESS_LESS:
        case JsTokenType::GREATER_GREATER:
        case JsTokenType::GREATER_GREATER_GREATER: return 8;
        case JsTokenType::PLUS:
        case JsTokenType::MINUS: return 9;
        case JsTokenType::STAR:
        case JsTokenType::SLASH:
        case JsTokenType::PERCENT: return 10;
        case JsTokenType::STAR_STAR: return 11;
        default: return 0;
    }
}

void JsParser::synchronize() {
    advance();
    
    while (!isAtEnd()) {
        if (previous().type == JsTokenType::SEMICOLON) return;
        
        switch (peek().type) {
            case JsTokenType::CLASS:
            case JsTokenType::FUNCTION:
            case JsTokenType::VAR:
            case JsTokenType::FOR:
            case JsTokenType::IF:
            case JsTokenType::WHILE:
            case JsTokenType::RETURN:
                return;
            default:
                advance();
        }
    }
}

bool JsParser::match(JsTokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool JsParser::check(JsTokenType type) const {
    if (isAtEnd()) return false;
    return peek().type == type;
}

JsToken JsParser::advance() {
    if (!isAtEnd()) current_++;
    return previous();
}

bool JsParser::isAtEnd() const {
    return peek().type == JsTokenType::EOF_TOKEN;
}

JsToken JsParser::peek() const {
    return tokens_[current_];
}

JsToken JsParser::previous() const {
    return tokens_[current_ - 1];
}

JsToken JsParser::consume(JsTokenType type, const std::string& message) {
    if (check(type)) return advance();
    throw std::runtime_error(message + " at line " + std::to_string(peek().line));
}

} // namespace chtl::v2::js