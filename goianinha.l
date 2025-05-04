%{
	#include <iostream>
	#include <stdlib.h>
	#include <map>
	#include <string>
	#include "../include/goianinha.tab.hh"

	using namespace yy;

	std::map<std::string, parser::token_kind_type> keywords = {
		{"programa", parser::token::PROGRAMA},
		{"car", parser::token::CAR},
		{"int", parser::token::INT},
		{"novalinha", parser::token::NOVALINHA},
		{"leia", parser::token::LEIA},
		{"escreva", parser::token::ESCREVA},
		{"execute", parser::token::EXECUTE},
		{"retorne", parser::token::RETORNE},
		{"se", parser::token::SE},
		{"entao", parser::token::ENTAO},
		{"senao", parser::token::SENAO},
		{"enquanto", parser::token::ENQUANTO},
		{"ou", parser::token::OU},
		{"e", parser::token::E}
	};
%}

%option c++
%option noyywrap
%option yylineno
%option outfile="src/lex.yy.cc"

VALID_NUMBER	-?[0-9][0-9]*|0
	/*INVALID_NUMBER	-?0[0-9]+*/
ID				[a-zA-Z_][a-zA-Z0-9_]*
VALID_STRING	\"[^\"\r\n]*\"
INVALID_STRING	\"[^\"]*\"
NO_END_STRING	\"[^\"]*
VALID_COMMENT	\/\*([^\*]|\*+[^\*\/])*\*+\/
INVALID_COMMENT	\/\*([^\*]|\*+[^\*\/])*\**

%%

[ \t\r\n]			/* Ignore whitespaces */

{VALID_COMMENT} /* Ignore comments */

{INVALID_COMMENT} {
	return parser::token::UNTERMINATED_COMMENT;
}

{VALID_NUMBER} {
	return parser::token::INTCONST;
}

	/*{INVALID_NUMBER} {
		return INVALID_NUMBER;
	}*/

{VALID_STRING} {
	return parser::token::STRING;
}

{INVALID_STRING} {
	return parser::token::INVALID_STRING;
}

{NO_END_STRING} {
	return parser::token::UNTERMINATED_STRING;
}

{ID} {
	auto search = keywords.find(yytext);
	if (search != keywords.cend()) {
		/* keyword found */
		return search->second;
	} else {
		/* not a keyword */
		return parser::token::ID;
	}
}

"("			{ return parser::token::LEFT_PAREN; }
")"			{ return parser::token::RIGHT_PAREN; }
"{"			{ return parser::token::LEFT_BRACE; }
"}"			{ return parser::token::RIGHT_BRACE; }
","			{ return parser::token::COMMA; }
"-"			{ return parser::token::MINUS; }
"+"			{ return parser::token::PLUS; }
";"			{ return parser::token::SEMICOLON; }
"/"			{ return parser::token::SLASH; }
"*"			{ return parser::token::STAR; }
"!"			{ return parser::token::BANG; }
"!="		{ return parser::token::BANG_EQUAL; }
"="			{ return parser::token::EQUAL; }
"=="		{ return parser::token::EQUAL_EQUAL; }
">"			{ return parser::token::GREATER; }
">="		{ return parser::token::GREATER_EQUAL; }
"<"			{ return parser::token::LESS; }
"<="		{ return parser::token::LESS_EQUAL; }
<<EOF>>		{ return parser::token::YYEOF; }

. {
	return parser::token::INVALID_CHARACTER;
}

%%