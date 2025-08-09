#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace CHTL
{
    class Node
    {
    public:
        virtual ~Node() = default;
        std::vector<std::unique_ptr<Node>>& children() { return children_; }
        const std::vector<std::unique_ptr<Node>>& children() const { return children_; }
    protected:
        std::vector<std::unique_ptr<Node>> children_ {};
    };

    class Text : public Node
    {
    public:
        explicit Text(std::string content) : content_(std::move(content)) {}
        const std::string& content() const noexcept { return content_; }
        void setContent(std::string s) { content_ = std::move(s); }
    private:
        std::string content_ {};
    };

    class Element : public Node
    {
    public:
        explicit Element(std::string tagName) : tagName_(std::move(tagName)) {}
        const std::string& tagName() const noexcept { return tagName_; }
        void setTagName(std::string s) { tagName_ = std::move(s); }

        std::map<std::string, std::string>& attributes() { return attributes_; }
        const std::map<std::string, std::string>& attributes() const { return attributes_; }

    private:
        std::string tagName_ {};
        std::map<std::string, std::string> attributes_ {};
    };
}