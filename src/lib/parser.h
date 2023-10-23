#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include <vector>
#include <ostream>
#include <map>

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

        map<string, double> variables;

        vector<bool> expect = {1, 0 , 0, 0, 0, 0}; // (open-p, close-p, o, n, var, a)
        int para_count;

        bool check(token* t);
        double assign(Node* a_node, int i);

    public:
        Parser(const std::vector<token*>& tokens);
        ~Parser();

        Node* head = NULL;

        void build(size_t i, Node* n);
        double calculate(Node* node);
        void print(Node* node, bool isRoot);


};

#endif
