#include "lib/lexer.h"

#include <iostream>
#include <istream>
#include <iomanip>
#include <vector>

#define HERE cout << "HERE\n";

using namespace std;

int main(){
    Lexer* l = new Lexer();
    vector<token*> tvec;
    try {
        tvec = l->read(cin);
    } catch (string error) {
        cout << error << endl;
        return 1;
    }

    for(token* t:tvec){
        std::cout << std::setw(4) << t->line << std::setw(5) << t->column << "  " << t->value << "\n";
    }

    delete l;

    return 0;
}


vector<token*> Lexer::read(istream& i) {
    int line = 1;
    int column = 0;  // Initialize column to 0

    while (!i.eof()) {
        char c = i.get();
        column++;  // Increment column for each character read

        if (c == '\n') {
            line++;
            column = 0;  // Reset column when a newline is encountered
            continue;
        } else if (isspace(c)) {
            continue;
        }

        types type;
        string value;

        if ((c >= 48 && c <= 57) || c == '.') {
            type = types::NUMBER;
            value = number(i, c);
            if (value == "error") {
                throw "Syntax error on line " + to_string(line) + " column " + to_string(column) + ".";
            }
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
        column += value.length() - 1;  // Adjust column based on token value length
    }

    token* end = new token(line, column, "END", types::END);
    tvec.push_back(end);

    return tvec;
}

string Lexer::number(istream& i, char c) {
    string buffer;
    buffer += c;
    bool dot_latch = (c == '.');

    char p = i.peek();
    while ((p >= '0' && p <= '9') || p == '.') {
        if (p == '.' && dot_latch) {
            return "error";
        }
        if (p == '.') {
            dot_latch = true;
        }
        buffer += i.get();
        p = i.peek();
    }

    return buffer;
}

 Lexer::~Lexer(){
        // Clean up dynamically allocated tokens
        for (token* t : tvec) {
            delete t;
        }
}

