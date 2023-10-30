#include "lib/calculator.h"
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

    CNode* curr_head;

    if(tvec.size() > 1){
        try{
            Calculator* c= new Calculator(tvec);
            try{
                c->build(1, c->head[0]);
                for(CNode* head:c->head){
                    curr_head = head;
                    double result = c->calculate(head, true);
                    c->print(head, true);
                    cout << endl;
                    cout << result << endl;
                }
            }catch(string e){
                cout << e << endl;
                delete l;
                delete c;
                return 2;
            }catch(const runtime_error& e){
                c->print(curr_head, true);
                cout << endl;
                cout << e.what() << endl;
                delete l;        
                delete c;
                return 3;
            }
            delete c;
        }catch(string e){
            cout << e << endl;
            delete l;
            return 2;
        }
    }else{
        cout << "Unexpected token at line " << tvec[0]->line << " column " << tvec[0]->column << ": END\n"; //yes I really did this. I'm lazy
        delete l;
        return 2;
    }

    delete l;
    return 0;

}