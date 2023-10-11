#include "lib/lexer.h"
#include "lib/parser.h"

#include <iostream>

using namespace std;

int main(){

    Lexer l;
    try{
        l.read(cin);
    } catch(string error){
        cout << error << endl;
    }

    return 0;
}