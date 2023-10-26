
#ifndef CALC_H
#define CALC_H

#include <string>
#include <vector>
#include "token.h"

class Calculator {
public:
    // Constructor
    Calculator();
    ~Calculator();

    double eval(const std::vector<token>& tokens); //'main' funcion, takes input vector, calls buildAST, and starts evaluate() recursion until ans is returned

    // // Member functions for various operations
    // double add(double a, double b);
    // double subtract(double a, double b);
    // double multiply(double a, double b);
    // double divide(double a, double b);

    //double calculateExpression(const std::vector<token>& tokens);
    //this is the main calc function
private:
    struct ASTNode { 
        virtual double evaluate() const = 0;
        virtual ~ASTNode() {}
    };

    struct OperatorNode : public ASTNode { //node with a oprand, a left child and right child
        char op; //+, -, *, /, =  Also can be null which defults to + i.e (3) = 3 + 0
        ASTNode* left;
        ASTNode* right;

        OperatorNode(char op, ASTNode* left, ASTNode* right);
        double evaluate() const override;
    };

    // struct ParenthesesNode : public ASTNode {  //Will just be a function in build tree instead
    //     ASTNode* expression;

    //     ParenthesesNode(ASTNode* expression);
    //     double evaluate() const override;
    // };

    struct NumberNode : public ASTNode { //node with a double value
        double value;

        NumberNode(double value);
        double evaluate() const override; 
    };

    struct VariableNode : public ASTNode { // node with a variable name and a double value 
        std::string name;
        double value;

        VariableNode(const std::string& name, double value);
        double evaluate() const override; //return value of calculation up to that node
    };

    ASTNode* buildAST(const std::vector<token>& tokens); //builds the AST from the token vector
};


#endif