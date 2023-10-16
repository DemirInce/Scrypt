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
        Node* ast = p.parse();
        p.printAST(ast, cout);
        cout << endl;
        cout << p.evaluate(ast) << endl;

        delete ast; // Cleanup the AST
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
