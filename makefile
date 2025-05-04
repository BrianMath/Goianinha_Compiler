CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./include
FLEX = flex
BISON = bison

all: goianinha

# Gera o arquivo de código do lexer usando Flex
src/lex.yy.cc: goianinha.l include/goianinha.tab.hh
	$(FLEX) -+ -o src/lex.yy.cc goianinha.l

# Gera o arquivo do código do parser usando Bison
src/goianinha.tab.cc include/goianinha.tab.hh: goianinha.y
	$(BISON) -d --defines=include/goianinha.tab.hh -o src/goianinha.tab.cc goianinha.y

# Regra para compilar o executável principal
goianinha: Main.cpp src/goianinha.tab.cc src/lex.yy.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

run: goianinha
	./goianinha tests/goianinha.g

clean:
	rm -f goianinha src/lex.yy.cc src/goianinha.tab.cc include/goianinha.tab.hh