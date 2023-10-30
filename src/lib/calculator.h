#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "token.h"
#include <vector>
#include <ostream>
#include <map>

struct CNode {
    CNode(token* t, int i);

    types type;
    string value;
    int child_count = 0;
    vector<CNode*> children;
    CNode* parent = nullptr;

    int token_line;
    int token_column;
    int token_i;
};

class Calculator {

    private:
        vector<token*> tokens;
        vector<CNode*> all_nodes;

        map<string, double> variables;

        vector<bool> expect = {1, 0 , 0, 1, 0, 0}; // (open-p, close-p, o, n, var, a)
        int para_count;

        int token_i = 1;

        bool check(token* t);
        double assign(CNode* a_node, int i);
        size_t headmaker(size_t i);

        //string Calculator::infixToSExpression(const vector<token*>& tokens);

    public:
        Calculator(const std::vector<token*>& tokens);
        ~Calculator();

        vector<CNode*> head;

        void build(size_t i, CNode* n);
        double calculate(CNode* node, bool isRoot);
        void print(CNode* node, bool isRoot);


};

#endif
