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

    int token_line;
    int token_column;
};

class Parser {

    private:
        vector<token*> tokens;
        vector<Node*> all_nodes;
        void build(size_t i, Node* n);

        vector<bool> expect = {1, 1 ,0}; // (p, o, n)
        bool check(token* t);

    public:
        Parser(const std::vector<token*>& tokens);
        ~Parser();

        Node* head = NULL;
        double calculate(Node* node);
        void print(Node* node, bool isRoot);

};

#endif
