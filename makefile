CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./include
FLEX = flex
BISON = bison

all: src/goianinha

# Gera o arquivo de código do lexer usando Flex
src/lex.yy.cc: src/goianinha.l include/goianinha.tab.hh
	$(FLEX) -+ -o src/lex.yy.cc src/goianinha.l

# Gera o arquivo do código do parser usando Bison
src/goianinha.tab.cc: src/goianinha.y
	$(BISON) -d --defines=include/goianinha.tab.hh -o src/goianinha.tab.cc src/goianinha.y

# Regra para compilar o executável principal
src/goianinha: src/Main.cpp src/goianinha.tab.cc src/lex.yy.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

printer: src/printer.cpp
	$(CXX) $(CXXFLAGS) $^ -o src/printer

print:
	src/printer

run: src/goianinha
	src/goianinha tests/goianinha.g

clean:
	rm -f goianinha src/lex.yy.cc src/goianinha.tab.cc src/goianinha src/printer include/goianinha.tab.hh 