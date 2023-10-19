#include "lib/parser.h"
#include "lib/lexer.h"

#include <stdexcept>
#include <iostream>
#include <string>

int main(){
    Lexer* l = new Lexer();
    std::vector<token*> tvec;
    try {
        tvec = l->read(cin);
    } catch (std::string error) {
        std::cout << error << std::endl;
        delete l;
        return 1;
    }

    Parser p(tvec);


    delete l;
    return 0;

}