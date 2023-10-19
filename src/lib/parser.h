#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <vector>
#include <ostream>

struct Node {
    Node(token* t);

    types type;
    string value;
    int child_count = 0;
    vector<Node*> children;
    Node* parent = nullptr;
    
    ~Node();
    void print();
};

class Parser {

    private:
        vector<token*> tokens;
        void build(size_t i, Node* n);
        double calculate(Node* op);

    public:
        Node* head = NULL;
        Parser(const std::vector<token*>& tokens);
        void print(Node* root, bool isRoot);

};

#endif
