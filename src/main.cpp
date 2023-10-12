#include "lib/lexer.h"
#include "lib/parser.h"

#include <iostream>

using namespace std;

int main(){

    Lexer l;
    vector<token*> tvec;
    try{
        tvec = l.read(cin);
    } catch(string error){
        cout << error << endl;
        return 1;
    }

    return 0;
}