#include "../include/Tokens.hpp"

std::map<std::string, TokenType> keywords = {
	{"programa", PROGRAMA},
	{"car", CAR},
	{"int", INT},
	{"novalinha", NOVALINHA},
	{"leia", LEIA},
	{"escreva", ESCREVA},
	{"execute", EXECUTE},
	{"retorne", RETORNE},
	{"se", SE},
	{"entao", ENTAO},
	{"senao", SENAO},
	{"enquanto", ENQUANTO},
	{"ou", OU},
	{"e", E}
};

const char* tokenNames[] = {
    "END", "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
    "COMMA", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",
    "BANG_EQUAL", "EQUAL", "EQUAL_EQUAL",
    "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL",
    "ID", "CARCONST", "INTCONST",
    "PROGRAMA", "CAR", "INT", "NOVALINHA",
    "LEIA", "ESCREVA", "EXECUTE", "RETORNE",
    "SE", "ENTAO", "SENAO", "ENQUANTO", "OU", "E",
	"STRING"
};
