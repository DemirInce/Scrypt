#include "lib/parser.h"
#include "lib/lexer.h"

#include <stdexcept>
#include <iostream>
#include <string>

int main(){
    Lexer* l = new Lexer();
    vector<token*> tvec;
    try {
        tvec = l->read(cin);
    } catch (string error) {
        cout << error << endl;
        return 1;
    }

    Parser p(tvec);
    try {
        Node* ast = p.parse();
        p.printAST(ast, cout);
        cout << endl;
        cout << p.evaluate(ast) << endl;
    } catch (runtime_error& e) {
        cout << e.what() << endl;
        if (string(e.what()).find("Unexpected token") != string::npos) {
            return 2;
        } else if (string(e.what()).find("division by zero") != string::npos) {
            return 3;
        }
    }

    delete l;

    return 0;
}

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





// DONT CHANGE ANYTHNG BELLOW HERE!!!! Just here until I fix the linking issue. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!






vector<token*> Lexer::read(istream& i) {
    int line = 1;
    int column = 0; 

    while (!i.eof()) {
        char c = i.get();
        column++;

        if (c == '\n') {
            line++;
            column = 0;
            continue;
        } else if (isspace(c)) {
            continue;
        }

        types type;
        string value;

        if ((c >= 48 && c <= 57) || c == '.') {
            type = types::NUMBER;
            value = number(i, c, column, line);
        } else if (c >= 42 && c <= 47) {
            type = types::OPERATOR;
            value += c;
        } else if (c >= 40 && c <= 41) {
            type = types::PARENTHESES;
            value += c;
        } else if (c != EOF) {
            throw "Syntax error on line " + to_string(line) + " column " + to_string(column) + ".";
        } else {
            break;
        }

        token* t = new token(line, column, value, type);
        tvec.push_back(t);
        column += value.length() - 1;
    }

    token* end = new token(line, column, "END", types::END);
    tvec.push_back(end);

    return tvec;
}

string Lexer::number(istream& i, char c, int column, int line) {
    string buffer;
    buffer += c;
    bool dot_latch = (c == '.');

    char p = i.peek();
    while ((p >= '0' && p <= '9') || p == '.') {
        if (p == '.' && dot_latch) {
            throw "Syntax error on line " + to_string(line) + " column " + to_string(column + 1) + ".";
        }
        if (p == '.') {
            dot_latch = true;
        }
        buffer += i.get();
        column++;
        p = i.peek();
    }

    if (buffer.front() == '.') {
        throw "Syntax error on line " + to_string(line) + " column " + to_string(column - buffer.length() + 1) + ".";
    } else if (buffer.back() == '.'){
        throw "Syntax error on line " + to_string(line) + " column " + to_string(column + 1) + ".";
    }

    return buffer;
}

 Lexer::~Lexer(){
        for (token* t : tvec) {
            delete t;
        }
}

