#include <string>

enum class types{
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