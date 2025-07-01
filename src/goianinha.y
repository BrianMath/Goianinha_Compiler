%{
	#include <iostream>
	#include <string>
	#include "../include/FlexLexer.h"
	#include "../include/goianinha.tab.hh"

	extern yyFlexLexer* scanner;

	// Handle lexical errors
	int yylex(void* yylval) {
		return scanner->yylex();
	};
%}

%require "3.8.2"
%language "c++"
%define api.namespace {boi}

// Tokens without type
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

// Initial non-terminal
%start Programa

%%

Programa
	: DeclFuncVar DeclProg {
		// List of global declarations is inverted due to right recursion
		// std::reverse($1->begin(), $1->end());

		// auto program_node = std::make_unique<AST::ProgramNode>(
		// 	std::move(*$1), std::move($2), scanner.lineno()
		// );

		// ast_root = std::move(program_node);
	  }
	;

DeclFuncVar
	: Tipo ID DeclVar SEMICOLON DeclFuncVar {
		// Pushes to the list of variables the first one
		// $3->push_back(std::move($2));
		// // List of variables is inverted due to right recursion
		// std::reverse($3->begin(), $3->end());

		// // Creates a new var declarations with the type and list of variables
		// auto vars = std::make_unique<AST::VariableDeclNode>(
		// 	$1, std::move(*$3), scanner.lineno()
		// );

		// // Fills in the list of global declarations with var declarations in inverse order
		// $5->push_back(std::move(vars));
		// $$ = std::move($5);
	  }
	| Tipo ID DeclFunc DeclFuncVar {
		// Creates a function
		// auto func = std::make_unique<AST::FunctionDeclNode>(
		// 	$1, std::move($2), std::move($3->params), std::move($3->body), scanner.lineno()
		// );

		// // Deletes the IR struct used for the function
		// delete $3;

		// // Fills in the list of global declarations with functions in inverse order
		// $4->push_back(std::move(func));
		// $$ = std::move($4);
	  }
	| /* ε */ {
		// Creates the list of global declarations
		// auto global_decls = std::make_unique<NodeList>();
		// $$ = std::move(global_decls);
	  }
	;

DeclProg
	: PROGRAMA Bloco {/* $$ = $2;*/ }
	;

DeclVar
	: COMMA ID DeclVar {
		// Fills in the list of variables in inverse order
		// $3->push_back(std::move($2));
		// $$ = std::move($3);
	  }
	| /* ε */ {
		// Creates a list of variables (string)
		// auto vars = std::make_unique<std::vector<std::string>>();
		// $$ = std::move(vars);
	  }
	;

DeclFunc
	: LEFT_PAREN ListaParametros RIGHT_PAREN Bloco {
		// It's not possible to create a function already,
		// because the return type and name are not know

		// Creates an intermediate representation for the function info
		// auto func_info = new PartialFunction();

		// func_info->params = std::move($2);
		// func_info->body = std::move($4);

		// $$ = func_info;
	  }
	;

ListaParametros
	: /* ε */ {
		// Empty vector representing no parameters
		// auto no_params = std::make_unique<ParameterList>();
		// $$ = std::move(no_params);
	  }
	| ListaParametrosCont {
		// List of parameters is inverted due to right recursion
		// std::reverse($1->begin(), $1->end());
		// $$ = std::move($1);
	  }
	;

ListaParametrosCont
	: Tipo ID {
		// Creates the last parameter
		// auto param = std::make_unique<AST::ParameterDeclNode>(
		// 	$1, std::move($2), scanner.lineno()
		// );

		// // Creates the list of parameters and pushes the last one
		// auto list_params = std::make_unique<ParameterList>();
		// list_params->push_back(std::move(param));
		// $$ = std::move(list_params);
	  }
	| Tipo ID COMMA ListaParametrosCont {
		// Creates the parameters in inverse order
		// auto param = std::make_unique<AST::ParameterDeclNode>(
		// 	$1, std::move($2), scanner.lineno()
		// );

		// // Fills in the list of parameters in inverse order
		// $4->push_back(std::move(param));
		// $$ = std::move($4);
	  }
	;

Bloco
	: LEFT_BRACE ListaDeclVar ListaComando RIGHT_BRACE {
		// List of var declarations is inverted due to right recursion
		// std::reverse($2->begin(), $2->end());
		
		// // List of commands is inverted due to right recursion
		// std::reverse($3->begin(), $3->end());

		// // Creates a new block with the list of var declarations and the list of commands
	    // $$ = std::make_unique<AST::BlockNode>(
		// 	std::move(*$2), std::move(*$3), scanner.lineno()
		// );
	  }
	;

ListaDeclVar
	: /* ε */ {
		// Creates a list of var declarations
		// auto list_vars = std::make_unique<VariableList>();
		// $$ = std::move(list_vars);
	  }
	| Tipo ID DeclVar SEMICOLON ListaDeclVar {
		// Pushes to the list of variables the first one
		// $3->push_back(std::move($2));
		// // List of variables is inverted due to right recursion
		// std::reverse($3->begin(), $3->end());

		// // Creates a new var declarations with the type and list of variables
		// auto vars = std::make_unique<AST::VariableDeclNode>(
		// 	$1, std::move(*$3), scanner.lineno()
		// );

		// // Fills in the list of var declarations in inverse order
		// $5->push_back(std::move(vars));

		// $$ = std::move($5);
	  }
	;

Tipo
	: INT {/* $$ = AST::BasicType::INT;*/ }
	| CAR {/* $$ = AST::BasicType::CAR;*/ }
	;

ListaComando
	: Comando {
		// Creates a list of commands and adds the last one
		// auto cmds = std::make_unique<CommandList>();
		// cmds->push_back(std::move($1));
		// $$ = std::move(cmds);
	  }
	| Comando ListaComando {
		// Fills in the list of commands in inverse order
		// $2->push_back(std::move($1));
		// $$ = std::move($2);
	  }
	;

Comando
	: SEMICOLON {}
	| NOVALINHA SEMICOLON {}
	| Expr SEMICOLON {
		// $$ = std::make_unique<AST::ExpressionCommandNode>(
		// 	std::move($1), scanner.lineno()
		// );
	  }
	| Bloco {/* $$ = $1;*/ }
	| RETORNE Expr SEMICOLON {
		// $$ = std::make_unique<AST::ReturnCommandNode>(
		// 	std::move($2), scanner.lineno()
		// );
	  }
	| LEIA ID SEMICOLON {
		// $$ = std::make_unique<AST::ReadCommandNode>(
		// 	std::move($2), scanner.lineno()
		// );
	  }
	| ESCREVA Expr SEMICOLON {
		// $$ = std::make_unique<AST::WriteCommandNode>(
		// 	std::move($2), scanner.lineno()
		// );
	  }
	| ESCREVA STRING SEMICOLON {
		// $$ = std::make_unique<AST::WriteCommandNode>(
		// 	std::move($2), scanner.lineno()
		// );
	  }
	| SE LEFT_PAREN Expr RIGHT_PAREN ENTAO Comando {
		// $$ = std::make_unique<AST::IfCommandNode>(
		// 	std::move($3), std::move($6), nullptr, scanner.lineno()
		// );
	  }
	| SE LEFT_PAREN Expr RIGHT_PAREN ENTAO Comando SENAO Comando {
		// $$ = std::make_unique<AST::IfCommandNode>(
		// 	std::move($3), std::move($6), std::move($8), scanner.lineno()
		// );
	  }
	| ENQUANTO LEFT_PAREN Expr RIGHT_PAREN EXECUTE Comando {
		// $$ = std::make_unique<AST::WhileCommandNode>(
		// 	std::move($3), std::move($6), scanner.lineno()
		// );
	  }
	;

Expr
	: ID EQUAL Expr { 
		// $$ = std::make_unique<AST::AssignNode>(
		// 	std::move($1), std::move($3), scanner.lineno()
		// );
	  }
	| OrExpr {/* $$ = $1;*/ }
	;

OrExpr
	: OrExpr OU AndExpr { 
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::OR, std::move($3), scanner.lineno()
		// );
	  }
	| AndExpr {/* $$ = $1;*/ }
	;

AndExpr
	: AndExpr E EqExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::AND, std::move($3), scanner.lineno()
		// );
	  }
	| EqExpr {/* $$ = $1;*/ }
	;

EqExpr
	: EqExpr EQUAL_EQUAL DesigExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::EQUAL, std::move($3), scanner.lineno()
		// );
	  }
	| EqExpr BANG_EQUAL DesigExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::DIFFERENT, std::move($3), scanner.lineno()
		// );
	  }
	| DesigExpr {/* $$ = $1;*/ }
	;

DesigExpr
	: DesigExpr LESS AddExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::LESS, std::move($3), scanner.lineno()
		// );
	  }
	| DesigExpr LESS_EQUAL AddExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::LESS_EQUAL, std::move($3), scanner.lineno()
		// );
	  }
	| DesigExpr GREATER AddExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::GREATER, std::move($3), scanner.lineno()
		// );
	  }
	| DesigExpr GREATER_EQUAL AddExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::GREATER_EQUAL, std::move($3), scanner.lineno()
		// );
	  }
	| AddExpr {/* $$ = $1;*/ }
	;

AddExpr
	: AddExpr PLUS MulExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::PLUS, std::move($3), scanner.lineno()
		// );
	  }
	| AddExpr MINUS MulExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::MINUS, std::move($3), scanner.lineno()
		// );
	  }
	| MulExpr {/* $$ = $1;*/ }
	;

MulExpr
	: MulExpr STAR UnExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::TIMES, std::move($3), scanner.lineno()
		// );
	  }
	| MulExpr SLASH UnExpr {
		// $$ = std::make_unique<AST::BinaryOperationNode>(
		// 	std::move($1), AST::Operator::DIVIDED, std::move($3), scanner.lineno()
		// );
	  }
	| UnExpr {/* $$ = $1;*/ }
	;

UnExpr
	: MINUS PrimExpr {
		// $$ = std::make_unique<AST::UnaryOperationNode>(
		// 	AST::Operator::NEGATIVE, std::move($2), scanner.lineno()
		// );
	  }
	| BANG PrimExpr {
		// $$ = std::make_unique<AST::UnaryOperationNode>(
		// 	AST::Operator::NOT, std::move($2), scanner.lineno()
		// );
	  }
	| PrimExpr {/* $$ = $1;*/ }
	;

PrimExpr
	: ID LEFT_PAREN ListExpr RIGHT_PAREN {
		// Function call with a list of arguments (ListExpr)
		// $$ = std::make_unique<AST::FunctionCallNode>(
		// 	std::move($1), std::move($3), scanner.lineno()
		// );
	  }
	| ID LEFT_PAREN RIGHT_PAREN {
		// Empty vector representing no arguments
		// auto no_args = std::vector<std::unique_ptr<AST::ExpressionNode>>();

		// $$ = std::make_unique<AST::FunctionCallNode>(
		// 	std::move($1), no_args, scanner.lineno()
		// );
	  }
	| ID { 
		// $$ = std::make_unique<AST::IdExpressionNode>(
		// 	std::move($1), scanner.lineno()
		// );
	  }
	| CARCONST { 
		// $$ = std::make_unique<AST::CarConstNode>(
		// 	$1, scanner.lineno()
		// );
	  }
	| INTCONST { 
		// $$ = std::make_unique<AST::IntConstNode>(
		// 	$1, scanner.lineno()
		// );
	  }
	| LEFT_PAREN Expr RIGHT_PAREN {/* $$ = $2;*/ }
	;

ListExpr
	: Expr {
		// Creates a list of arguments (expressions) and adds the first one
		// auto exprs = std::make_unique<std::vector<std::unique_ptr<AST::ExpressionNode>>>();
		// exprs->push_back(std::move($1));
		// $$ = std::move(exprs);
	  }
	| ListExpr COMMA Expr {
		// Pushes to the list of arguments the next one
		// $1->push_back(std::move($3));
		// $$ = std::move($1);
	  }
	;

%%

namespace boi {
	void parser::error(const std::string &msg) {
		std::cerr << "\033[0;31mErro de sintaxe: token inesperado '" << scanner->YYText()
					<< "' perto da linha " << scanner->lineno() << "\033[0m\n";

		exit(EXIT_FAILURE);
	}	
}
