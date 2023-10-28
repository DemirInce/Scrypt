#include "calculator.h"
#include <stdexcept>
//////////////////////////////////////////////////////////////////////////////
// Constructor
Calculator::Calculator() {
}

// Destructor
Calculator::~Calculator() {
}

double Calculator::eval(const std::vector<token>& tokens) {
    // Build the AST from the input tokens
    ASTNode* root = buildAST(tokens);

    if (root) {
        // Evaluate the AST by calling 'evaluate' on the root node
        double result = root->evaluate();

        // Clean up and release memory
        delete root;

        return result; // Return the final result
    } else {
        // Handle an error scenario where the AST couldn't be built
        throw std::runtime_error("Failed to build the AST.");
    }
}

//end of things directly related to Calculator
///////////////////////////////////////////////////////////////////////////////////

// Constructor for OperatorNode
Calculator::OperatorNode::OperatorNode(char op, ASTNode* left, ASTNode* right) : op(op), left(left), right(right) {
    // Initialize OperatorNode members
}

double Calculator::OperatorNode::evaluate() const {
    double leftValue = left->evaluate();
    double rightValue = right->evaluate();

    // Implement the operation based on the operator
    switch (op) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            if (rightValue != 0) {
                return leftValue / rightValue;
            } else {
                throw std::runtime_error("Division by zero is not allowed.");
            }
        // Add more cases for other operators as needed
        default:
            throw std::runtime_error("Invalid operator.");
    }
}
/////////////////////////////////////////////////////////////////////////////////

// Constructor for NumberNode
Calculator::NumberNode::NumberNode(double value) : value(value) {
    // Initialize NumberNode members
}

double Calculator::NumberNode::evaluate() const {
    return value;
}

////////////////////////////////////////////////////////////////////////////////

// Constructor for VariableNode
Calculator::VariableNode::VariableNode(const std::string& name, double value) : name(name), value(value) {
    // Initialize VariableNode members
}

// Implementation of 'evaluate' function for OperatorNode
double Calculator::OperatorNode::evaluate() const {
    // Implement how to calculate the result based on the operator and child nodes
    // Return the computed result
}

// Implementation of 'evaluate' function for NumberNode
double Calculator::NumberNode::evaluate() const {
    return value; // Simply return the stored numerical value
}

// Implementation of 'evaluate' function for VariableNode
double Calculator::VariableNode::evaluate() const {
    // Implement how to look up and return the variable's value
    // Return the computed result
}

// Implementation of 'buildAST' function
Calculator::ASTNode* Calculator::buildAST(const std::vector<token>& tokens) {
    // Implement how to build the AST based on the input tokens
    // Return the root node of the AST
}

// Implementation of 'eval' function
double Calculator::eval(const std::vector<token>& tokens) {
    // Implement how to parse tokens, build the AST, and evaluate it
    // Return the final result
}
