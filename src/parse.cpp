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
            delete p;
        }catch(string e){
            cout << e << endl;
            return 2;
        }catch(runtime_error e){
            cout << e.what() << endl;
            return 3;
        }
    }else{
        cout << "Unexpected token at line " << tvec[0]->line << " column " << tvec[0]->column << ": END\n"; //yes I really did this. I'm lazy
        delete l;
        return 2;
    }

    delete l;
    return 0;

}
