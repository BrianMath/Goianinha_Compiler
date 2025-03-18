#include "SymbolTableStack.hpp"

int main() {
	SymbolTableStack stack;
	// Global scope
	stack.createScope();

	stack.addVar("x", INT, 0);
	stack.addVar("y", INT, 1);
	stack.addVar("z", INT, 2);

	SymTable* scope = stack.searchName("y");
	std::cout << "z: " << std::get<Variable>(scope->find("z")->second).varType << '\n';

	stack.addFunc("fatorial", INT, 1);
	scope = stack.searchName("fatorial");
	stack.addParam("n", INT, 0, scope);
	stack.addVar("x", CAR, 0);
	stack.addVar("y", CAR, 1);

	scope = stack.searchName("n");
	std::cout << "n: " << std::get<Parameter>(scope->find("n")->second).paramType << '\n';

	scope = stack.searchName("n");
	std::cout << "scope: " << scope << '\n';
	std::cout << "scope: " << std::get<Parameter>(scope->find("n")->second).funcScope << '\n';
	scope = std::get<Parameter>(scope->find("n")->second).funcScope;
	std::cout << "scope: " << std::get<Parameter>(scope->find("n")->second).funcScope << '\n';
	std::cout << "y fora: " << std::get<Variable>(scope->find("y")->second).varType << '\n';

	stack.createScope();
	// scope = stack.searchName("n");
	std::cout << "scope: " << scope << '\n';
	std::cout << "y dentro: " << std::get<Variable>(scope->find("y")->second).varType << '\n';
	stack.deleteScope();

	std::cout << "y fora: " << std::get<Variable>(scope->find("y")->second).varType << '\n';

	scope = stack.searchName("y");
	std::cout << "y: " << std::get<Variable>(scope->find("y")->second).varType << '\n';

	scope = stack.searchName("n");
	std::cout << "x: " << std::get<Variable>(scope->find("x")->second).varType << '\n';

	scope = stack.searchName("z");
	std::cout << "z: " << std::get<Variable>(scope->find("z")->second).varType << '\n';

	scope = stack.searchName("fatorial");
	std::cout << "fatorial: " << std::get<Function>(scope->find("fatorial")->second).returnType << '\n';

	stack.deleteScope();

	std::cout << "Olá, mundo!\n";

	return 0;
}