#include "../include/SymbolTableStack.hpp"

// Contructor
SymbolTableStack::SymbolTableStack() {
	createStack();
}

// Destructor
SymbolTableStack::~SymbolTableStack() {
	deleteStack();
}

// Private methods
void SymbolTableStack::createStack() {
	stack = std::make_unique<SymTableStack>();
}

void SymbolTableStack::deleteStack() {
	stack = nullptr;
}

// Public methods
void SymbolTableStack::createScope() {
	stack->push_back(new SymTable());
}

void SymbolTableStack::deleteScope() {
	stack->pop_back();
}

void SymbolTableStack::addVar(std::string varName, Type varType, uint32_t varDeclPos) {	
	SymTable* currentScope = stack->back();

	auto search = currentScope->find(varName);
	if (search != currentScope->cend()) {
		throw std::runtime_error("SEMANTIC ERROR: variable" + varName + "already exists\n");
	} else {
		currentScope->insert({varName, Variable{varType, varDeclPos}});
	}
}

void SymbolTableStack::addFunc(std::string funcName, Type returnType, uint32_t numParams) {
	createScope();
	
	SymTable* currentScope = stack->back();
	currentScope->insert({funcName, Function{returnType, numParams}});
}

void SymbolTableStack::addParam(std::string paramName, Type paramType, 
								uint32_t paramPos, SymTable* funcScope) {
	
	SymTable* currentScope = stack->back();
	currentScope->insert({paramName, Parameter{paramType, paramPos, funcScope}});
}

SymTable* SymbolTableStack::searchName(std::string name) {
	for (int i = stack->size() - 1; i >= 0; i--) {
		SymTable* currentScope = stack->at(i);

		auto search = currentScope->find(name);
		
		if (search != currentScope->cend()) {
			return currentScope;
		}
	}

	std::cout << "SEMANTIC ERROR: variable not declared\n";
	return nullptr;
}
