#include "lib/lexer.h"
#include "lib/parser.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main(){
    Lexer l;
    vector<token*> tvec;
    try {
        tvec = l.read(cin);
    } catch (string error) {
        cout << error << endl;
        return 1;
    }

    Parser p(tvec);
    try {
        auto ast = p.parse();  // Use auto to let the compiler deduce the unique_ptr type
        p.printAST(ast.get(), cout);  // ast.get() retrieves the raw pointer from the unique_ptr
        cout << endl;
        cout << p.evaluate(ast.get()) << endl;

        // No need to delete ast; unique_ptr will take care of it
    } catch (runtime_error& e) {
        cout << e.what() << endl;
        if (string(e.what()).find("Unexpected token") != string::npos) {
            return 2;
        } else if (string(e.what()).find("division by zero") != string::npos) {
            return 3;
        }
    }

    return 0;
}
