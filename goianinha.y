%{
	#include <iostream>
	#include <string>
	#include "../include/FlexLexer.h"
	#include "../include/Scanner.hpp"
	#include "../include/goianinha.tab.hh"

	// Handle lexical errors
	int yylex(void* yylval) {
		int token = scanner->yylex();

		switch (token) {
			case yy::parser::token::UNTERMINATED_COMMENT:
				std::cerr << "\033[0;33mERRO: COMENTÁRIO NÃO TERMINA na linha " << scanner->lineno() << "\033[0m\n";
				exit(EXIT_FAILURE);
				break;
			
			case yy::parser::token::INVALID_CHARACTER:
				std::cerr << "\033[0;33mERRO: CARACTERE INVÁLIDO na linha " << scanner->lineno() << "\033[0m\n";
				std::cerr << "Lexema '" << scanner->YYText() << "'\n";
				exit(EXIT_FAILURE);
				break;
			
			case yy::parser::token::INVALID_STRING:
				std::cerr << "\033[0;33mERRO: CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA na linha " << scanner->lineno() << "\033[0m\n";
				exit(EXIT_FAILURE);
				break;
			
			case yy::parser::token::UNTERMINATED_STRING:
				std::cerr << "\033[0;33mERRO: CADEIA DE CARACTERES NÃO TERMINA na linha " << scanner->lineno() << "\033[0m\n";
				exit(EXIT_FAILURE);
				break;
			
			default:
				return token;
		}
	};
%}

%require "3.8.2"
%language "c++"

// Tokens
%token LEFT_PAREN RIGHT_PAREN LEFT_BRACE RIGHT_BRACE
%token COMMA MINUS PLUS SEMICOLON SLASH STAR
%token BANG BANG_EQUAL EQUAL EQUAL_EQUAL
%token GREATER GREATER_EQUAL
%token LESS LESS_EQUAL
%token ID CARCONST INTCONST
%token PROGRAMA CAR INT NOVALINHA
%token LEIA ESCREVA EXECUTE RETORNE
%token SE ENTAO SENAO ENQUANTO OU E
%token STRING
%token UNTERMINATED_COMMENT INVALID_NUMBER INVALID_CHARACTER INVALID_STRING UNTERMINATED_STRING

// Initial non-terminal
%start Programa

%%

Programa
	: DeclFuncVar DeclProg
	;

DeclFuncVar
	: Tipo ID DeclVar SEMICOLON DeclFuncVar
	| Tipo ID DeclFunc DeclFuncVar
	| /* ε */
	;

DeclProg
	: PROGRAMA Bloco
	;

DeclVar
	: COMMA ID DeclVar
	| /* ε */
	;

DeclFunc
	: LEFT_PAREN ListaParametros RIGHT_PAREN Bloco
	;

ListaParametros
	: /* ε */
	| ListaParametrosCont
	;

ListaParametrosCont
	: Tipo ID
	| Tipo ID COMMA ListaParametrosCont
	;

Bloco
	: LEFT_BRACE ListaDeclVar ListaComando RIGHT_BRACE
	;

ListaDeclVar
	: /* ε */
	| Tipo ID DeclVar SEMICOLON ListaDeclVar
	;

Tipo
	: INT
	| CAR
	;

ListaComando
	: Comando
	| Comando ListaComando
	;

Comando
	: SEMICOLON
	| Expr SEMICOLON
	| RETORNE Expr SEMICOLON
	| LEIA ID SEMICOLON
	| ESCREVA Expr SEMICOLON
	| ESCREVA STRING SEMICOLON
	| NOVALINHA SEMICOLON
	| SE LEFT_PAREN Expr RIGHT_PAREN ENTAO Comando
	| SE LEFT_PAREN Expr RIGHT_PAREN ENTAO Comando SENAO Comando
	| ENQUANTO LEFT_PAREN Expr RIGHT_PAREN EXECUTE Comando
	| Bloco
	;

Expr
	: OrExpr
	| ID EQUAL Expr
	;

OrExpr
	: OrExpr OU AndExpr
	| AndExpr
	;

AndExpr
	: AndExpr E EqExpr
	| EqExpr
	;

EqExpr
	: EqExpr EQUAL_EQUAL DesigExpr
	| EqExpr BANG_EQUAL DesigExpr
	| DesigExpr
	;

DesigExpr
	: DesigExpr LESS AddExpr
	| DesigExpr GREATER AddExpr
	| DesigExpr GREATER_EQUAL AddExpr
	| DesigExpr LESS_EQUAL AddExpr
	| AddExpr
	;

AddExpr
	: AddExpr PLUS MulExpr
	| AddExpr MINUS MulExpr
	| MulExpr
	;

MulExpr
	: MulExpr STAR UnExpr
	| MulExpr SLASH UnExpr
	| UnExpr
	;

UnExpr
	: MINUS PrimExpr
	| BANG PrimExpr
	| PrimExpr
	;

PrimExpr
	: ID LEFT_PAREN ListExpr RIGHT_PAREN
	| ID LEFT_PAREN RIGHT_PAREN
	| ID
	| CARCONST
	| INTCONST
	| LEFT_PAREN Expr RIGHT_PAREN
	;

ListExpr
	: Expr
	| ListExpr COMMA Expr
	;

%%

#include <iostream>
#include <string>
#include "../include/Scanner.hpp"

namespace yy {
	void parser::error(const std::string &msg) {
		std::cerr << "\033[0;31mErro de sintaxe: token inesperado '" << scanner->YYText()
				  << "' perto da linha " << scanner->lineno() << "\033[0m\n";

		exit(EXIT_FAILURE);
	}	
}