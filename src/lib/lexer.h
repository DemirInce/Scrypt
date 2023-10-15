#include "token.h"
#include <string>
#include <vector>

class Lexer{

public:
    vector<token*> read(istream& i);
    string number(istream& i, char c);
    
};