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
        try{
            Parser* p= new Parser(tvec);
            double value = p->calculate(p->head);
            p->print(p->head, true);
            cout << endl;
            cout << value << endl;
            delete p;
        }catch(string e){
            cout << e << endl;
            return 3;
        }
    }else{
        cout << "Unexpected token at line 1 column 1: END\n"; //yes I really did this. I'm lazy
        delete l;
        return 2;
    }

    delete l;
    return 0;

}
}