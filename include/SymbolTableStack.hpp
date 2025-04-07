#ifndef SYMBOL_TABLE_STACK_HPP
#define SYMBOL_TABLE_STACK_HPP

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
	uint32_t varDeclPos;
};

struct Function {
	Type returnType;
	uint32_t numParams;
};

struct Parameter {
	Type paramType;
	uint32_t paramPos;
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
		void addVar(std::string varName, Type varType, uint32_t varDeclPos);
		void addFunc(std::string funcName, Type returnType, uint32_t numParams);
		void addParam(std::string paramName, Type paramType, uint32_t paramPos, SymTable* funcScope);
		SymTable* searchName(std::string);
};

#endif