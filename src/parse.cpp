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

    if(tvec.size() > 1){
        Parser* p= new Parser(tvec);
        p->print(p->head, true);
        cout << endl;
        cout << p->calculate(p->head) << endl;
        delete p;
    }else{
        return 2;
    }

    delete l;
    return 0;

}