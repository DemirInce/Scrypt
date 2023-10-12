#include "lib/lexer.h"

#include <iostream>
#include <istream>
#include <iomanip>

#define HERE cout << "HERE\n";

using namespace std;


vector<token*> Lexer::read(istream& i){
    vector<token*> tvec;
    int line = 1;
    int column = 1;

    while(true){
        char c = i.get();
        if (c == '\n') {
            line++;
            column = 1;
            continue;
        } else if (isspace(c)) {
            column++;
            continue;
        }
        types type;
        string value;

        if(c >= 48 && c <= 57){ // 0-9
            type = types::NUMBER;
            value = number(i, c);
        } else if(c >= 42 && c <= 47){ // operators
            type = types::OPERATOR;
            value += c;
        } else if(c >= 40 && c <= 41){ // parentheses
            type = types::PARENTHESES;
            value += c;
        } else if(c != EOF){
            throw "Syntax error on line " + to_string(line) + " column " + to_string(column) + ".";
        } else{
            break;
        }

        column += value.length();
        token* t = new token(line, column, value, type);
        tvec.push_back(t);
    }
    token* end = new token(line, column, "END", types::END);
    tvec.push_back(end);

    for(token* t:tvec){
        std::cout << std::setw(4) << t->line << std::setw(5) << t->column << "  " << t->value << "\n";
    }

    return tvec;
}

string Lexer::number(istream& i, char c) {
    string buffer;
    buffer += c;
    bool dot_latch = false;

    char p = i.peek();
    while ((p >= '0' && p <= '9') || p == '.') {
        if(p == '.' && !dot_latch){
            dot_latch = true;
        } else if(p == '.' && dot_latch){
            return buffer;
        }
        buffer += i.get();
        p = i.peek();
    }

    return buffer;
}
