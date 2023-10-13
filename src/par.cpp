#include "lib/parser.h"
#include <stdexcept>
#include <iostream>
#include <string>


Parser::Parser(const std::vector<token*>& tokens) : tokens(tokens), currentToken(0) {}

Node* Parser::parse() {
    int x = tokens.size();
    Node* root = expression();
    if (currentToken != x - 1 || tokens[currentToken]->type != types::END) {
        throw std::runtime_error("Unexpected token at line " + std::to_string(tokens[currentToken]->line) +
            " column " + std::to_string(tokens[currentToken]->column) + ": " + tokens[currentToken]->value);
    }
    return root;
}

Node* Parser::expression() {
    int x = tokens.size();
    Node* left = term();
    while (currentToken < x && tokens[currentToken]->type == types::OPERATOR &&
           (tokens[currentToken]->value == "+" || tokens[currentToken]->value == "-")) {
        Node* op = new Node(tokens[currentToken++]);
        op->children.push_back(left);
        op->children.push_back(term());
        left = op;
    }
    return left;
}

Node* Parser::term() {
    int x = tokens.size();
    Node* left = factor();
    while (currentToken < x && tokens[currentToken]->type == types::OPERATOR &&
           (tokens[currentToken]->value == "*" || tokens[currentToken]->value == "/")) {
        Node* op = new Node(tokens[currentToken++]);
        op->children.push_back(left);
        op->children.push_back(factor());
        left = op;
    }
    return left;
}

Node* Parser::factor() {
    if (tokens[currentToken]->type == types::NUMBER) {
        return new Node(tokens[currentToken++]);
    } else if (tokens[currentToken]->type == types::PARENTHESES && tokens[currentToken]->value == "(") {
        currentToken++;
        Node* innerExp = expression();
        if (tokens[currentToken]->type != types::PARENTHESES || tokens[currentToken]->value != ")") {
            throw std::runtime_error("Expected closing parenthesis at line " + std::to_string(tokens[currentToken]->line) +
                " column " + std::to_string(tokens[currentToken]->column));
        }
        currentToken++;
        return innerExp;
    }
    throw std::runtime_error("Unexpected token at line " + std::to_string(tokens[currentToken]->line) +
        " column " + std::to_string(tokens[currentToken]->column) + ": " + tokens[currentToken]->value);
}

double Parser::evaluate(Node* root) {
    if (root->t->type == types::NUMBER) {
        return stod(root->t->value);
    } else if (root->t->type == types::OPERATOR) {
        double leftValue = evaluate(root->children[0]);
        double rightValue = evaluate(root->children[1]);
        if (root->t->value == "+") return leftValue + rightValue;
        if (root->t->value == "-") return leftValue - rightValue;
        if (root->t->value == "*") return leftValue * rightValue;
        if (root->t->value == "/") {
            if (rightValue == 0) throw std::runtime_error("Runtime error: division by zero.");
            return leftValue / rightValue;
        }
    }
    throw std::runtime_error("Unknown node type in AST.");
}

void Parser::printAST(Node* root, std::ostream& out) {
    if (root->t->type == types::NUMBER) {
        out << root->t->value;
    } else if (root->t->type == types::OPERATOR) {
        out << "(";
        printAST(root->children[0], out);
        out << " " << root->t->value << " ";
        printAST(root->children[1], out);
        out << ")";
    } else {
        throw std::runtime_error("Unknown node type in AST.");
    }
}
