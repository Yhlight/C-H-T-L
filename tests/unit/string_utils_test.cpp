#include "test_framework.h"
#include "../../src/chtl/utils/StringUtils.h"

using namespace chtl::utils;
using namespace chtl::test;

TEST(StringUtils, Trim) {
    ASSERT_EQ(StringUtils::trim("  hello  "), "hello");
    ASSERT_EQ(StringUtils::trim("\t\nhello\r\n"), "hello");
    ASSERT_EQ(StringUtils::trim("hello"), "hello");
    ASSERT_EQ(StringUtils::trim(""), "");
    ASSERT_EQ(StringUtils::trim("   "), "");
}

TEST(StringUtils, Split) {
    auto parts = StringUtils::split("a,b,c", ',');
    ASSERT_EQ(parts.size(), 3);
    ASSERT_EQ(parts[0], "a");
    ASSERT_EQ(parts[1], "b");
    ASSERT_EQ(parts[2], "c");
    
    parts = StringUtils::split("hello", ',');
    ASSERT_EQ(parts.size(), 1);
    ASSERT_EQ(parts[0], "hello");
    
    parts = StringUtils::split("", ',');
    ASSERT_EQ(parts.size(), 1);
    ASSERT_EQ(parts[0], "");
}

TEST(StringUtils, StartsWith) {
    ASSERT_TRUE(StringUtils::startsWith("hello world", "hello"));
    ASSERT_TRUE(StringUtils::startsWith("hello", "hello"));
    ASSERT_FALSE(StringUtils::startsWith("hello", "world"));
    ASSERT_FALSE(StringUtils::startsWith("hi", "hello"));
    ASSERT_TRUE(StringUtils::startsWith("", ""));
}

TEST(StringUtils, EndsWith) {
    ASSERT_TRUE(StringUtils::endsWith("hello world", "world"));
    ASSERT_TRUE(StringUtils::endsWith("hello", "hello"));
    ASSERT_FALSE(StringUtils::endsWith("hello", "world"));
    ASSERT_FALSE(StringUtils::endsWith("hi", "hello"));
    ASSERT_TRUE(StringUtils::endsWith("", ""));
}

TEST(StringBuilder, Append) {
    StringBuilder builder;
    builder.append("Hello")
           .append(" ")
           .append("World")
           .append('!');
    
    ASSERT_EQ(builder.toString(), "Hello World!");
}

TEST(StringBuilder, Numbers) {
    StringBuilder builder;
    builder << "The answer is " << 42 << " and pi is " << 3.14;
    
    auto result = builder.toString();
    ASSERT_TRUE(result.find("42") != std::string::npos);
    ASSERT_TRUE(result.find("3.14") != std::string::npos);
}

TEST(StringUtils, EscapeHtml) {
    ASSERT_EQ(StringUtils::escapeHtml("<div>"), "&lt;div&gt;");
    ASSERT_EQ(StringUtils::escapeHtml("a & b"), "a &amp; b");
    ASSERT_EQ(StringUtils::escapeHtml("\"quote\""), "&quot;quote&quot;");
    ASSERT_EQ(StringUtils::escapeHtml("'apostrophe'"), "&#39;apostrophe&#39;");
}

TEST(StringUtils, IsValidIdentifier) {
    ASSERT_TRUE(StringUtils::isValidIdentifier("hello"));
    ASSERT_TRUE(StringUtils::isValidIdentifier("_private"));
    ASSERT_TRUE(StringUtils::isValidIdentifier("var123"));
    ASSERT_TRUE(StringUtils::isValidIdentifier("camelCase"));
    
    ASSERT_FALSE(StringUtils::isValidIdentifier("123var"));
    ASSERT_FALSE(StringUtils::isValidIdentifier("hello-world"));
    ASSERT_FALSE(StringUtils::isValidIdentifier("hello world"));
    ASSERT_FALSE(StringUtils::isValidIdentifier(""));
}

RUN_ALL_TESTS()