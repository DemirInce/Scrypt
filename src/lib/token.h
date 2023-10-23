#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum class types{
    VARIABLE,
    ASSIGNMENT,
    NUMBER,
    OPERATOR,
    PARENTHESES,
    END
};

struct token{
    int     line;
    int     column;
    string  value;
    types   type;

    token(int line, int column, string value, types type){
        this->line = line;
        this->column = column;
        this->value = value;
        this->type = type; 
    }
};

#endif
