#include <iostream>
#include <string>
#include <vector>
#include "lib/lexer.h"


int main(){

    Lexer* l = new Lexer();
    std::vector<token*> tvec;
    try {
        tvec = l->read(cin);
    } catch (std::string error) {
        std::cout << error << std::endl;
        return 1;
    }

    return 0;
}

