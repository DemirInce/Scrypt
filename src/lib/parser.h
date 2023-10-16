#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <vector>

struct Node {
    token* t;
    std::vector<Node*> children;

    Node(token* tok): t(tok) {}
    
    ~Node() {
        for (Node* child : children) {
            delete child;
        }
    }
};

class Parser {
public:
    Parser(const std::vector<token*>& tokens);
    Node* parse();
    double evaluate(Node* root);
    void printAST(Node* root, std::ostream& out);

private:
    std::vector<token*> tokens;
    int currentToken;

    Node* expression();
    Node* term();
    Node* factor();
};

#endif