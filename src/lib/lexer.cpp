#include "lexer.h"

#include <iostream>
#include <istream>
#include <iomanip>
#include <vector>

#define HERE cout << "HERE\n";

using namespace std;

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

        if ((c >= '0' && c <= '9') || c == '.') {
            type = types::NUMBER;
            value = number(i, c, column, line);
        } else if (c == '*' || c == '+' || c == '-' || c == '/') {
            type = types::OPERATOR;
            value += c;
        } else if (c >= '(' && c <= ')') {
            type = types::PARENTHESES;
            value += c;
        } else if (c == '=') {
            type = types::ASSIGNMENT;
            value += c;
        } else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_')) {
            type = types::VARIABLE;
            value = variable(i, c); 
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

string Lexer::variable(istream& i, char c){
    string buffer;
    buffer += c;

    char p = i.peek();
    while((p >= 'A' && p <= 'Z') || (p >= 'a' && p <= 'z') || (p == '_') || (p >= '0' && p <= '9')){
        buffer += i.get();
        p = i.peek();    
    }

    return buffer;
}

Lexer::~Lexer(){
        for (token* t : tvec) {
            delete t;
        }
}

