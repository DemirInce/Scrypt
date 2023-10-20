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
        return 1;
    }

    if(tvec.size() > 1){
        Parser* p= new Parser(tvec);
        try{
            p->build(1, p->head);
            p->print(p->head, true);
            cout << endl;
            cout << p->calculate(p->head) << endl;
        }catch(string e){
            cout << e << endl;
            delete l;
            delete p;
            return 2;
        }catch(const runtime_error& e){
            cout << e.what() << endl;
            delete l;        
            delete p;
            return 3;
        }
        delete p;
    }else{
        cout << "Unexpected token at line " << tvec[0]->line << " column " << tvec[0]->column << ": END\n"; //yes I really did this. I'm lazy
        delete l;
        return 2;
    }

    delete l;
    return 0;

}