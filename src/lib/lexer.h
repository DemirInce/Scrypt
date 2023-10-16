#include "token.h"
#include <string>
#include <vector>

class Lexer{

public:
    vector<token*> tvec;

    vector<token*> read(istream& i);
    string number(istream& i, char c, int column, int line);
    ~Lexer();

};