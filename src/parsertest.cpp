#include "lib/lexer.h"
#include "lib/parser.h"
#include <iostream>

int main() {
    std::vector<token*> test_vec;

    token* t1 = new token(1, 1, "38", types::NUMBER);
    token* t2 = new token(1, 2, "+", types::OPERATOR);
    token* t3 = new token(1, 3, "10", types::NUMBER);
    token* t4 = new token(1, 4, "/", types::OPERATOR);
    token* t5 = new token(1, 5, "24", types::NUMBER);
    token* tEnd = new token(1, 6, "END", types::END); 

    test_vec.push_back(t1);
    test_vec.push_back(t2);
    test_vec.push_back(t3);
    test_vec.push_back(t4);
    test_vec.push_back(t5);
    test_vec.push_back(tEnd); // Push the END token

    Parser p(test_vec);

    try {
        Node* ast = p.parse();

        // Printing AST in infix form
        p.printAST(ast, std::cout);
        std::cout << std::endl;

        // Printing the evaluated result
        double result = p.evaluate(ast);
        std::cout << result << std::endl;

        //delete memory
        delete ast; 
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    // Free the tokens
    for (token* t : test_vec) {
        delete t;
    }

    return 0;
}
