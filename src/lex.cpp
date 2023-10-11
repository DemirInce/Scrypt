#include "lib/lexer.h"

#include <iostream>
#include <istream>

using namespace std;


vector<token*> Lexer::read(istream& i){
    vector<token*> tvec;
    int line = 1;
    int column = 1;

    while(!i.eof()){
        char c = i.get();
        if (c == '\n') {
            line++;
            column = 1;
            continue;
        } else if (isspace(c)) {
            column++;
            continue;
        }
        token* t;

        if(c >= 48 && c <= 57){ // 0-9
            string op = number(i, c);
            t = new token(line, column, op, types::NUMBER);
            column += op.length();
        } else if(c >= 42 && c <= 47){ // operators
            string op;
            op += c;
            t = new token(line, column, op, types::OPERATOR);
            column++;
        } else if(c >= 40 && c <= 41){ // parentheses
            string par;
            par += c;
            t = new token(line, column, par, types::PARENTHESES);
            column++;
        } else{
            throw "Syntax error on line " + to_string(line) + " column " + to_string(column) + ".";
        }
        tvec.push_back(t);
    }
    token* end = new token(line, column, "END", types::END);
    tvec.push_back(end);

    for(token* t:tvec){
        cout << t->line << " " << t->column << " " << t->value << endl;
    }

    return tvec;
}

string Lexer::number(istream& i, char c){
    string buffer;
    buffer += c;
    char p = i.peek();
    if((p >= 48 && p <= 57) || p == 46){
        char next = i.get();
        buffer += next;
        char p_next = i.peek();
        while(p_next >= 48 && p_next <= 57){
            next = i.get();
            buffer += next;
            p_next = i.peek();
        }
    }
    return buffer;
}
