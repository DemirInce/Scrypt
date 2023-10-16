#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <vector>
#include <memory> // for std::unique_ptr
#include <ostream>

struct Node {
    token* t;
    std::vector<std::unique_ptr<Node>> children;

    Node(token* tok): t(tok) {}
    
    ~Node() = default; // With std::unique_ptr, we don't need a custom destructor
};

class Parser {
public:
    Parser(const std::vector<token*>& tokens);
    
    std::unique_ptr<Node> parse(); // Updated return type
    double evaluate(Node* root);
    void printAST(Node* root, std::ostream& out);

private:
    std::vector<token*> tokens;
    int currentToken;

    std::unique_ptr<Node> expression(); // Updated return type
    std::unique_ptr<Node> term();       // Updated return type
    std::unique_ptr<Node> factor();     // Updated return type
};

#endif
