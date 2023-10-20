#include "parser.h"

#include <vector>
#include <iostream>
#include <numeric>
#include <stdexcept>

using namespace std;

#define HERE cout << "here\n";

Node::Node(token* t) {
    this->value = t->value;
    this->type = t->type;
    this->token_line = t->line;
    this->token_column = t->column;
}

Parser::Parser(const vector<token*>& tokens) {
    this->tokens = tokens;
    size_t i = 0; 
    para_count = 0;
    while (i < tokens.size() && tokens[i]->type == types::PARENTHESES) {
        para_count++;
        i++;
    }
    token* t = tokens[i];
    if(!check(t)){
        throw string("Unexpected token at line ") + to_string(t->line) 
        + " column " + to_string(t->column) + ": " + t->value;
    }
    Node* n = new Node(t);
    all_nodes.push_back(n);
    head = n;
}

Parser::~Parser(){
    for(Node* n:all_nodes){
        delete n;
    }
}


void Parser::build(size_t i, Node* n) {
    token* t = tokens[i];
    if (t->type == types::END) {
        if(para_count != 0){
            throw string("Unexpected token at line ") + to_string(t->line) 
            + " column " + to_string(t->column) + ": " + t->value;            
        }
        return;
    }
    if(!check(t) || (para_count == 0 && t->type != types::END)){
        throw string("Unexpected token at line ") + to_string(t->line) 
        + " column " + to_string(t->column) + ": " + t->value;
    }

    if (t->value == "(") {
        expect = {0, 0 , 1, 0};
        para_count++;
        build(i + 1, n);
    } else if (t->value == ")") {
        expect = {1, 1 , 0, 1};
        para_count--;
        build(i + 1, n->parent);
    } else {

        Node* next = new Node(t);
        all_nodes.push_back(next);
        next->parent = n;
        n->children.push_back(next);
        n->child_count++;

        if (next->type == types::OPERATOR) {
            expect = {1, 0 , 0, 1};
            build(i + 1, next);
        } else if (next->type == types::NUMBER) {
            expect = {1, 1 , 0, 1};
            build(i + 1, n);
        }
    }
}

void Parser::print(Node* node, bool isRoot = true) {
    if (node == nullptr) {
        return;
    }

    if (node->type == types::NUMBER) {
        string value = node->value;
        size_t decimalPos = value.find('.');
        if (decimalPos != string::npos) {
            size_t nonZeroPos = value.find_last_not_of('0');
            if (nonZeroPos == decimalPos) {
                value = value.substr(0, decimalPos);
            }
        }
        cout << value;

    } else if (node->type == types::OPERATOR) {
        if (!isRoot) {
            cout << "(";
        }
        for (size_t i = 0; i < node->children.size(); i++) {
            print(node->children[i], false); 
            if (i < node->children.size() - 1) {
                cout << " " << node->value << " ";
            }
        }
        if (!isRoot) {
            cout << ")";
        }
    }
}

double Parser::calculate(Node* node) {
    if (node == nullptr) {
        return 0.0;
    }
    if (node->type == types::NUMBER) {
        return stod(node->value);
    } else if (node->type == types::OPERATOR) {
        double result = 0.0;
        for (size_t i = 0; i < node->children.size(); i++) {
            if (i == 0) {
                result = calculate(node->children[i]);
            } else {
                if (node->value == "+") {
                    result += calculate(node->children[i]);
                } else if (node->value == "-") {
                    result -= calculate(node->children[i]);
                } else if (node->value == "*") {
                    result *= calculate(node->children[i]);
                } else if (node->value == "/") {
                    double step = calculate(node->children[i]);
                    if (step == 0) {
                        throw runtime_error("Runtime error: division by zero.");
                    }
                    result /= step;
                }
            }
        }
        return result;
    } else {
        throw string("Unexpected token at line ") + to_string(node->token_line) 
        + " column " + to_string(node->token_column) + ": " + node->value;
    }
}

bool Parser::check(token* t){
    types type = t->type;
    if(t->value == "(" && expect[0] == false){
        return false;
    }else if(t->value == ")" && expect[1] == false){
        return false;
    }else if(type == types::OPERATOR && expect[2] == false){
        return false;
    }else if(type == types::NUMBER && expect[3] == false){
        return false;
    }else{
        return true;
    }
}