#include "token.h"
#include <string>

class Lexer{

    string t_buffer;
    vector<token*> t_vec;

    vector<token*>read();
};