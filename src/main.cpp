#include "lib/lexer.h"
#include "lib/parser.h"

#include <iostream>

using namespace std;

int main(){

    cout << "Hello World!\n"; 
    token t(1,1,"69",types::NUMBER);
    cout << t.value << " " << t.line << " " << t.column << endl;

    // TEST 2

    return 0;
}