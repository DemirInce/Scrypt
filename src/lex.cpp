#include "lib/lexer.h"

#include <iostream>
#include <istream>
#include <iomanip>
#include <vector>

#define HERE cout << "HERE\n";

using namespace std;

int main(){
    Lexer* l = new Lexer();
    vector<token*> tvec;
    try {
        tvec = l->read(cin);
    } catch (string error) {
        cout << error << endl;
        return 1;
    }

    for(token* t:tvec){
        std::cout << std::setw(4) << t->line << std::setw(5) << t->column << "  " << t->value << "\n";
    }

    delete l;

    return 0;
}

