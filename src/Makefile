CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: all clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

all: lex

lex: lex.cpp lib/lexer.cpp
	${CXX} $(CXXFLAGS) -O3 -o $@ $+

parse: parse.cpp lib/parser.cpp lib/lexer.cpp
	${CXX} $(CXXFLAGS) -O3 -o $@ $+

calc: calc.cpp lib/calculator.cpp lib/lexer.cpp
	${CXX} $(CXXFLAGS) -O3 -o $@ $+

clean:
	rm -f lex
	rm -r lex.dSYM
