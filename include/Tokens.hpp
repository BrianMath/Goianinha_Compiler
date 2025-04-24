#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>
#include <map>

enum TokenType {
	// End of file
	END,

	// Single-character tokens
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens
	BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals
	ID, CARCONST, INTCONST,

	// Keywords
	PROGRAMA, CAR, INT, NOVALINHA,
	LEIA, ESCREVA, EXECUTE, RETORNE,
	SE, ENTAO, SENAO, ENQUANTO, OU, E,

	// Special
	STRING,
};

extern std::map<std::string, TokenType> keywords;
extern const char* tokenNames[];

#endif