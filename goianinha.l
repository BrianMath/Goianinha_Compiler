%{
	#include <iostream>
	#include <stdlib.h>
	#include "include/Tokens.hpp"
	#include "include/Errors.hpp"
%}

%option c++
%option noyywrap
%option yylineno

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
	return UNTERMINATED_COMMENT;
}

{VALID_NUMBER} {
	return INTCONST;
}

	/*{INVALID_NUMBER} {
		return INVALID_NUMBER;
	}*/

{VALID_STRING} {
	return STRING;
}

{INVALID_STRING} {
	return INVALID_STRING;
}

{NO_END_STRING} {
	return UNTERMINATED_STRING;
}

{ID} {
	auto search = keywords.find(yytext);
	if (search != keywords.cend()) {
		/* keyword found */
		return search->second;
	} else {
		/* not a keyword */
		return ID;
	}
}

"("			{ return LEFT_PAREN; }
")"			{ return RIGHT_PAREN; }
"{"			{ return LEFT_BRACE; }
"}"			{ return RIGHT_BRACE; }
","			{ return COMMA; }
"-"			{ return MINUS; }
"+"			{ return PLUS; }
";"			{ return SEMICOLON; }
"/"			{ return SLASH; }
"*"			{ return STAR; }
"!="		{ return BANG_EQUAL; }
"="			{ return EQUAL; }
"=="		{ return EQUAL_EQUAL; }
">"			{ return GREATER; }
">="		{ return GREATER_EQUAL; }
"<"			{ return LESS; }
"<="		{ return LESS_EQUAL; }
<<EOF>>		{ return END; }

. {
	return INVALID_CHARACTER;
}

%%