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
    cout << endl;
    cout << calculate(head) << endl;;
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
        cout << next->value << " ";
        n->child_count++;

        if(next->type == types::OPERATOR){
            build(i+1, next);
        }else if(next->type == types::NUMBER){
            build(i+1, n);    
        }

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
        double sub = 0;
        for(Node* n:op->children){
            if(n->type == types::OPERATOR){
                sub = calculate(n) - sub;
            }else{
                sub = stod(n->value) - sub;
            }
        }
        cout << sub << endl;

        return sub;
    }
    return 0;
}