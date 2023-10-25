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

    Node* curr_head;

    if(tvec.size() > 1){
        try{
            Parser* p= new Parser(tvec);
            try{
                p->build(1, p->head[0]);
                for(Node* head:p->head){
                    curr_head = head;
                    double result = p->calculate(head, true);
                    p->print(head, true);
                    cout << endl;
                    cout << result << endl;
                }
            }catch(string e){
                cout << e << endl;
                delete l;
                delete p;
                return 2;
            }catch(const runtime_error& e){
                p->print(curr_head, true);
                cout << e.what() << endl;
                delete l;        
                delete p;
                return 3;
            }
            delete p;
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