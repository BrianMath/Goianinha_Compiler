#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "include/FlexLexer.h"
#include "include/goianinha.tab.hh"

yyFlexLexer* scanner = nullptr;

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cerr << "Uso esperado:\n\t" << argv[0] << " <arquivo_goianinha>\n";
		return EXIT_FAILURE;
	}

	// Open the little goiânia file
	std::ifstream input_file(argv[1]);
	if (!input_file.is_open()) {
		std::cerr << "Erro: não foi possível abrir o arquivo " << argv[1] << '\n';
		return EXIT_FAILURE;
	}

	scanner = new yyFlexLexer(&input_file);
	if (!scanner) {
		std::cerr << "Erro: Falha ao criar o analisador léxico\n";
		return EXIT_FAILURE;
	}

	yy::parser parser_instance;
	int result = parser_instance.parse();

	delete scanner;
	scanner = nullptr;
	// Close the little goiânia file
	input_file.close();

	if (!result) {
		std::cout << "\033[0;32mAnálise sintática realizada com sucesso\033[0m\n";
	} else {
		std::cout << "Análise sintática falhou com código: " << result << '\n';
	}

	return result;
}
