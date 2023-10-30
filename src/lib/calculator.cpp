#include "calculator.h"

#include <vector>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <stack>

using namespace std;

#define HERE cout << "here\n";

Node::Node(token* t, int i) {
    this->value = t->value;
    this->type = t->type;
    this->token_line = t->line;
    this->token_column = t->column;
    this->token_i = i;
}

Calculator::Calculator(const vector<token*>& tokens) {
    this->tokens = tokens;
    size_t i = 0; 
    para_count = 0;
    
    i = headmaker(i);
}

Calculator::~Calculator(){
    for(Node* n:all_nodes){
        delete n;
    }
}


void Calculator::build(size_t i, Node* n) {
    token* t = tokens[i];
    token_i++;
    if (t->type == types::END) {  
        if(para_count != 0){
            throw string("Unexpected token at line ") + to_string(t->line) 
            + " column " + to_string(t->column + 1) + ": " + t->value;            
        }
        return;
    }
    if((para_count == 0 && t->type != types::END)){
        expect = {1, 0 , 0, 0, 0, 0};
        para_count = 0;
        i = headmaker(i);
        build(i, head[head.size()-1]);
        return;
    }
    if(!check(t)){ 
        throw string("Unexpected token at line ") + to_string(t->line) 
        + " column " + to_string(t->column) + ": " + t->value;
    }

    if (t->value == "(") { 
        expect = {0, 0, 1, 0, 0, 1};  // (open-p, close-p, o, n, var, a)
        para_count++;
        build(i + 1, n);
    } else if (t->value == ")") {
        expect = {1, 1, 0, 1, 1, 0};
        para_count--;
        build(i + 1, n->parent);
    } else {                                                                       

        Node* next = new Node(t, i);
        all_nodes.push_back(next);
        next->parent = n;
        n->children.push_back(next);
        n->child_count++;

        if (next->type == types::OPERATOR) {
            expect = {1, 0 , 0, 1, 1, 0};
            build(i + 1, next);
        } else if (next->type == types::NUMBER || next->type == types::VARIABLE) {
            expect = {1, 1 , 0, 1, 1, 0};
            build(i + 1, n);
        } else if (next->type == types::ASSIGNMENT) {
            expect = {0, 0 , 0, 0, 1, 0};
            build(i + 1, next);
        }
    }
}

void Calculator::print(Node* node, bool isRoot = true) {
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

    } else if (node->type == types::VARIABLE){
        cout << node->value;
    
    } else if (node->type == types::OPERATOR || node->type == types::ASSIGNMENT) {
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

double Calculator::calculate(Node* node, bool isRoot) {
    if (node == nullptr) {
        return 0.0;
    }
    if (node->type == types::NUMBER) {
        return stod(node->value);
    } else if (node->type == types::ASSIGNMENT){
        if(isRoot){
            return assign(node->children[0], 0);
        }else{
            return assign(node, 0);
        }
    } else if (node->type == types::VARIABLE){
        if(variables.find(node->value) != variables.end()){
            return variables[node->value];
        }else{
            throw runtime_error("Runtime error: unknown identifier " + node->value);
        }
    } else if (node->type == types::OPERATOR) {
        double result = 0.0;
        for (size_t i = 0; i < node->children.size(); i++) {
            if (i == 0) {
                result = calculate(node->children[i], false);
            } else {
                if (node->value == "+") {
                    result += calculate(node->children[i], false);
                } else if (node->value == "-") {
                    result -= calculate(node->children[i], false);
                } else if (node->value == "*") {
                    result *= calculate(node->children[i], false);
                } else if (node->value == "/") {
                    double step = calculate(node->children[i], false);
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

double Calculator::assign(Node* a_node, int i){
    Node* child = a_node->children[i];
    vector<string> variable_buffer;
    while(child->type == types::VARIABLE){
        if(i+1 == a_node->child_count){
            throw string("Unexpected token at line ") + to_string(tokens[child->token_i+1]->line) 
            + " column " + to_string(tokens[child->token_i+1]->column) + ": " + tokens[child->token_i+1]->value;
        }
        variable_buffer.push_back(child->value);
        i++;
        child = a_node->children[i];
    }
    if(i != a_node->child_count-1){
        throw string("Unexpected token at line ") + to_string(a_node->children[i+1]->token_line) 
        + " column " + to_string(a_node->children[i+1]->token_column) + ": " + a_node->children[i+1]->value;
    }
    double value = calculate(a_node->children[i], false);
    for(string s:variable_buffer){
        variables[s] = value;
    }
    return value;
}

bool Calculator::check(token* t){ // (open-p, close-p, o, n, var, a)
    types type = t->type;
    if(t->value == "(" && expect[0] == false){
        return false;
    }else if(t->value == ")" && expect[1] == false){
        return false;
    }else if(type == types::OPERATOR && expect[2] == false){
        return false;
    }else if(type == types::NUMBER && expect[3] == false){
        return false;
    }else if(type == types::VARIABLE && expect[4] == false){
        return false;
    }else if(type == types::ASSIGNMENT && expect[5] == false){
        return false;
    }else{
        return true;
    }
}

size_t Calculator::headmaker(size_t i){
    while (i < tokens.size() && tokens[i]->value == "(") {
        expect = {0, 0, 1, 0, 0, 1};
        para_count++;
        i++;
    }

    token* t = tokens[i];
    if(!check(t)){
        throw string("Unexpected token at line ") + to_string(t->line) 
        + " column " + to_string(t->column) + ": " + t->value;          
    }

    Node* n = new Node(t, i);
    all_nodes.push_back(n);
    head.push_back(n);

    return i;
}


