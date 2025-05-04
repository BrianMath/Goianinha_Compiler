#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "include/FlexLexer.h"
#include "include/Tokens.hpp"
#include "include/Errors.hpp"

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

	yyFlexLexer lexer(&input_file);
	
	int token;
	while ((token = lexer.yylex()) != END) {
		if (token == UNTERMINATED_COMMENT) {
			std::cout << "ERRO: COMENTÁRIO NÃO TERMINA na linha " << lexer.lineno() << '\n';
			return EXIT_FAILURE;
		};

		// Comentar depois de pronto
		// if (token == INVALID_NUMBER) {
		// 	int number = atoi(lexer.YYText());
		// 	std::cout << "Número inválido: " << number << '\n';
		// 	continue;
		// }

		if (token == INVALID_CHARACTER) {
			std::cout << "ERRO: CARACTERE INVÁLIDO na linha " << lexer.lineno() << '\n';
			std::cout << "Lexema '" << lexer.YYText() << "'\n";
			return EXIT_FAILURE;
		}

		if (token == INVALID_STRING) {
			std::cout << "ERRO: CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA na linha " << lexer.lineno() << '\n';
			return EXIT_FAILURE;
		}

		if (token == UNTERMINATED_STRING) {
			std::cout << "ERRO: CADEIA DE CARACTERES NÃO TERMINA na linha " << lexer.lineno() << '\n';
			return EXIT_FAILURE;
		}

		std::cout << "Encontrado o lexema " << lexer.YYText()
				  << " pertencente ao token de codigo " << tokenNames[token] 
				  << " linha " << lexer.lineno() << '\n';

		//  std::cout << "Lexema '" << lexer.YYText()
		//  		  << "' -> " << tokenNames[token] 
		//  		  << " | linha " << lexer.lineno() << '\n';
    }
	
	// std::cout << "\ntchau\n";

	// Close the little goiânia file
	input_file.close();

	return 0;
}
