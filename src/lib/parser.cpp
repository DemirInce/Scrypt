#include "parser.h"
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

Node::Node(token* t) {
    this->value = t->value;
    this->type = t->type;
}

void Node::print(){
    
}

Parser::Parser(const vector<token*>& tokens){
    this->tokens = tokens;
    int i = 0;
    while(tokens[i]->type == types::PARENTHESES){
    i++;
    }
    Node* n = new Node(tokens[i]);
    head = n;
    build(1, head);
    //cout << calculate(head) << endl;;
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

void Parser::print(Node* node) {
    if (node == nullptr) {
        return;
    }

    if (node->type == types::NUMBER) {
        cout << node->value;
    } else if (node->type == types::OPERATOR) {
        cout << "(";
        for (size_t i = 0; i < node->children.size(); i++) {
            print(node->children[i]);
            if (i < node->children.size() - 1) {
                cout << " " << node->value << " ";
            }
        }
        cout << ")";
    }
}


double Parser::calculate(Node* op){
    if(op->value == "*"){
        double multi = 1;
        for(Node* n:op->children){
            if(n->type == types::OPERATOR){
                multi *= calculate(n);
            }else{
                multi *= stod(n->value);
            }
        }
        cout << multi << endl;
        return multi;

    }else if(op->value == "/"){
        double sum = 0;
        for(Node* n:op->children){
            if(n->type == types::OPERATOR){
                sum /= calculate(n);
            }else{
                sum /= stod(n->value);
            }
        }
        cout << sum << endl;

        return sum;

    }else if(op->value == "+"){
        double sum = 0;
        for(Node* n:op->children){
            if(n->type == types::OPERATOR){
                sum += calculate(n);
            }else{
                sum += stod(n->value);
            }
        }
        cout << sum << endl;

        return sum;

    }else if(op->value == "-"){
        double sub = stod(op->children[1]->value);
        for(Node* n:op->children){
            if(n->type == types::OPERATOR){
                sub = sub - calculate(n);
            }else{
                sub -= sub - stod(n->value);
            }
        }
        cout << sub << endl;

        return sub;
    }
    return 0;
}