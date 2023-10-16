#include "parser.h"
#include "lexer.h"

#include <stdexcept>
#include <iostream>
#include <string>
#include <memory>

Parser::Parser(const std::vector<token*>& tokens) : tokens(tokens), currentToken(0) {}

std::unique_ptr<Node> Parser::parse() {
    int x = tokens.size();
    auto root = expression();
    if (currentToken != x - 1 || tokens[currentToken]->type != types::END) {
        cout << "1st\n";
        throw std::runtime_error("Unexpected token at line " + std::to_string(tokens[currentToken]->line) +
            " column " + std::to_string(tokens[currentToken]->column) + ": " + tokens[currentToken]->value);
    }
    return root;
}

std::unique_ptr<Node> Parser::expression() {
    int x = tokens.size();
    auto left = term();
    while (currentToken < x && tokens[currentToken]->type == types::OPERATOR &&
           (tokens[currentToken]->value == "+" || tokens[currentToken]->value == "-")) {
        auto op = std::make_unique<Node>(tokens[currentToken++]);
        op->children.push_back(std::move(left));
        op->children.push_back(term());
        left = std::move(op);
    }
    return left;
}

std::unique_ptr<Node> Parser::term() {
    int x = tokens.size();
    auto left = factor();
    while (currentToken < x && tokens[currentToken]->type == types::OPERATOR &&
           (tokens[currentToken]->value == "*" || tokens[currentToken]->value == "/")) {
        auto op = std::make_unique<Node>(tokens[currentToken++]);
        op->children.push_back(std::move(left));
        op->children.push_back(factor());
        left = std::move(op);
    }
    return left;
}

std::unique_ptr<Node> Parser::factor() {
    if (tokens[currentToken]->type == types::NUMBER) {
        return std::make_unique<Node>(tokens[currentToken++]);
    } else if (tokens[currentToken]->type == types::PARENTHESES && tokens[currentToken]->value == "(") {
        currentToken++;
        auto innerExp = expression();
        if (tokens[currentToken]->type != types::PARENTHESES || tokens[currentToken]->value != ")") {
            throw std::runtime_error("Expected closing parenthesis at line " + std::to_string(tokens[currentToken]->line) +
               " column " + std::to_string(tokens[currentToken]->column));
        }
        currentToken++;
        return innerExp;
    }
    cout << "2nd\n";
    throw std::runtime_error("Unexpected token at line " + std::to_string(tokens[currentToken]->line) +
        " column " + std::to_string(tokens[currentToken]->column) + ": " + tokens[currentToken]->value);
    return NULL;
}


double Parser::evaluate(Node* root) {
    if (root->t->type == types::NUMBER) {
        return std::stod(root->t->value);
    } else if (root->t->type == types::OPERATOR) {
        double leftValue = evaluate(root->children[0].get());
        double rightValue = evaluate(root->children[1].get());

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
        printAST(root->children[0].get(), out);
        out << " " << root->t->value << " ";
        printAST(root->children[1].get(), out);
        out << ")";
    } else {
        throw std::runtime_error("Unknown node type in AST.");
    }
}