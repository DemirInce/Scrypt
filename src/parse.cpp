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
    try {
        auto ast = p.parse();
        p.printAST(ast.get(), std::cout);
        std::cout << std::endl;
        std::cout << p.evaluate(ast.get()) << std::endl;
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        if (std::string(e.what()).find("Unexpected token") != std::string::npos || std::string(e.what()).find("closing") != std::string::npos) {
            delete l;
            return 2;
        } else if (std::string(e.what()).find("division by zero") != std::string::npos) {
            delete l;
            return 3;
        }
    }

    delete l;
    return 0;

}
