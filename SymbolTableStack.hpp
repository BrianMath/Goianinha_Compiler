#ifndef SYMBOL_TABLE_STACK_H
#define SYMBOL_TABLE_STACK_H

#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <memory>
#include <map>

enum Type {
	INT,
	CAR
};

struct Variable {
	Type varType;
	uint varDeclPos;
};

struct Function {
	Type returnType;
	uint numParams;
};

struct Parameter {
	Type paramType;
	uint paramPos;
	std::map<std::string, std::variant<Variable, Function, Parameter>>* funcScope;
};

using Name = std::variant<Variable, Function, Parameter>;
using SymTable = std::map<std::string, Name>;
using SymTableStack = std::vector<SymTable*>;
using StackPtr = std::unique_ptr<SymTableStack>;

class SymbolTableStack {
	private:
		StackPtr stack;

		void createStack();
		void deleteStack();

	public:
		SymbolTableStack();
		~SymbolTableStack();

		void createScope();
		void deleteScope();
		void addVar(std::string varName, Type varType, uint varDeclPos);
		void addFunc(std::string funcName, Type returnType, uint numParams);
		void addParam(std::string paramName, Type paramType, uint paramPos, SymTable* funcScope);
		SymTable* searchName(std::string);
};

#endif