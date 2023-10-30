#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "token.h"
#include <vector>
#include <ostream>
#include <map>

struct Node {
    Node(token* t, int i);

    types type;
    string value;
    int child_count = 0;
    vector<Node*> children;
    Node* parent = nullptr;

    int token_line;
    int token_column;
    int token_i;
};

class Calculator {

    private:
        vector<token*> tokens;
        vector<Node*> all_nodes;

        map<string, double> variables;

        vector<bool> expect = {1, 0 , 0, 1, 0, 0}; // (open-p, close-p, o, n, var, a)
        int para_count;

        int token_i = 1;

        bool check(token* t);
        double assign(Node* a_node, int i);
        size_t headmaker(size_t i);

        string Calculator::infixToSExpression(const vector<token*>& tokens);

    public:
        Calculator(const std::vector<token*>& tokens);
        ~Calculator();

        vector<Node*> head;

        void build(size_t i, Node* n);
        double calculate(Node* node, bool isRoot);
        void print(Node* node, bool isRoot);


};

#endif
