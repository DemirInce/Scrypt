# Mathematical Expression Parser and Lexer

## Introduction

This C++ project comprises a mathematical expression parser (`parser.cpp`) and a lexer (`lexer.cpp`) that work in tandem to interpret and evaluate mathematical expressions. Whether you need to perform simple arithmetic calculations or handle more complex mathematical expressions, this project provides a flexible solution.

## Features

### Lexer (`lexer.cpp`)

- Tokenizes input expressions, breaking them down into meaningful units.
- Identifies various token types, including numbers, operators, and parentheses, allowing for precise parsing.
- Provides robust error handling for syntax errors, ensuring the reliability of the tokenization process.

### Parser (`parser.cpp`)

- Parses mathematical expressions by utilizing the tokens produced by the lexer.
- Evaluates expressions that may encompass fundamental arithmetic operations, such as addition, subtraction, multiplication, and division.
- Handles parentheses to establish the correct order of operations, crucial for complex mathematical expressions.
- Supports variables and assignments, allowing you to incorporate variables into your calculations.
- Provides comprehensive error handling for invalid expressions, ensuring that the parsing process is both reliable and informative.

## Prerequisites

Before you begin, make sure you have the following prerequisites in place:

- A C++ compiler compatible with C++11 or later.
- Access to the Standard Template Library (STL).
- An input stream of mathematical expressions to be tokenized and parsed.

## Installation

To get started with this project, follow these installation steps:

1. Clone the repository or download the `parser.cpp` and `lexer.cpp` files to your local machine.

2. Integrate both `parser.cpp` and `lexer.cpp` into your C++ project. Ensure that they are compiled together to guarantee the proper functioning of the mathematical expression parser.

3. Set up an input stream containing the mathematical expressions you wish to tokenize and parse.

## Usage

To utilize this project effectively, follow these usage guidelines:

1. Utilize the `Lexer` class to tokenize mathematical expressions:

   ```cpp
   #include "lexer.h"
   #include <fstream>
   #include <vector>

   std::ifstream input("input.txt");

   Lexer lexer;
   std::vector<token*> tokens = lexer.read(input);
