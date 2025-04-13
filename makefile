# Lexer makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/usr/include
FLEX = flex

all: main

# Gera o arquivo de código do lexer usando Flex
lex.yy.cc: goianinha.l
	$(FLEX) -+ goianinha.l

# Regra para compilar o executável principal
main: Main.cpp src/Tokens.cpp lex.yy.cc
	$(CXX) $(CXXFLAGS) Main.cpp src/Tokens.cpp lex.yy.cc -o goianinha

run: main
	./goianinha tests/goianinha.g

clean:
	rm -f lex.yy.cc goianinha