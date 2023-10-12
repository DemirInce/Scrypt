#include "lib/lexer.h"
#include "lib/parser.h"

int main(){

vector<token*> test_vec;

token* t1 = new token(1, 1, "38", types::NUMBER);
token* t2 = new token(1, 2, "+", types::OPERATOR);
token* t3 = new token(1, 3, "10", types::NUMBER);
token* t4 = new token(1, 4, "/", types::OPERATOR);
token* t5 = new token(1, 5, "24", types::NUMBER);

test_vec.push_back(t);

}