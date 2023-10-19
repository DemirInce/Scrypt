#include "parser.h"
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

Node::Node(token* t) {
    this->value = t->value;
    this->type = t->type;
}

Parser::Parser(const vector<token*>& tokens) {
    this->tokens = tokens;
    size_t i = 0; 
    while (tokens[i]->type == types::PARENTHESES) {
        i++;
    }
    Node* n = new Node(tokens[i]);
    all_nodes.push_back(n);
    head = n;
    build(1, head);
}

Parser::~Parser(){
    for(Node* n:all_nodes){
        delete n;
    }
}

void Parser::build(size_t i , Node* n){
    token* t = tokens[i];
    if(t->type == types::END){return;}

    if(t->value == "("){
        build(i+1, n);
    }else if(t->value == ")"){
        build(i+1, n->parent);
    }else{

        Node* next = new Node(t);  
        all_nodes.push_back(next); 
        next->parent = n;     
        n->children.push_back(next);
        n->child_count++;

        if(next->type == types::OPERATOR){
            build(i+1, next);
        }else if(next->type == types::NUMBER){
            build(i+1, n);    
        }

    }
}

void Parser::print(Node* node, bool isRoot = true) {
    if (node == nullptr) {
        return;
    }

    if (node->type == types::NUMBER) {
        string value = node->value;
        
        // Check if the number has a decimal point with all trailing zeros
        size_t decimalPos = value.find('.');
        if (decimalPos != string::npos) {
            size_t nonZeroPos = value.find_last_not_of('0');
            if (nonZeroPos == decimalPos) {
                // The number has all zeros after the decimal point, so truncate it
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
                    result /= calculate(node->children[i]);
                }
            }
        }
        return result;
    } else {
        return 0.0;
    }
}
