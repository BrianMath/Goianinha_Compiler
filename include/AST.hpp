#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>

namespace AST {
	// Tipos
	enum class BasicType {
		INT, CAR
	};

	// Classe base para um nó da AST
	class ASTNode {
		public:
			int line;

			ASTNode(int lineNum) : line(lineNum) {}
			virtual ~ASTNode() = default;
	};

	// int a, b;
	/* Um único nó da árvore seria:
		int
	   /   \
	  a     b
	*/

	// Declarações de variáveis
	class VariableDeclNode : public ASTNode {
		public:
			BasicType variableType;
			std::vector<std::string> identifiers;

			VariableDeclNode(BasicType type, std::vector<std::string> ids, int line)
				: variableType(type), 
				  identifiers(std::move(ids)), 
				  ASTNode(line) {}
			virtual ~VariableDeclNode() = default;
	};

	// Classe base para comandos
	class StatementNode : public ASTNode {
		public:


			StatementNode(int line)
				: ASTNode(line) {}
			virtual ~StatementNode() = default;
	};

	// Bloco de comandos
	class Block : public StatementNode {
		public:
			std::vector<std::unique_ptr<VariableDeclNode>> localVariables;
			std::vector<std::unique_ptr<StatementNode>> commands;

			Block(std::vector<std::unique_ptr<VariableDeclNode>> listVar, 
				  std::vector<std::unique_ptr<StatementNode>> cmds, int line)
				: localVariables(std::move(listVar)),
				  commands(std::move(cmds)),
				  StatementNode(line) {}
			virtual ~Block() = default;
	};

	// Declarações de parâmetros
	class ParameterDeclNode : public ASTNode {
		public:
			BasicType parameterType;
			std::string identifier;			

			ParameterDeclNode(BasicType type, std::string id, int line)
				: parameterType(type),
				  identifier(std::move(id)),
				  ASTNode(line) {}
			virtual ~ParameterDeclNode() = default;
	};

	// Declarações de funções
	class FunctionDeclNode : public ASTNode {
		public:
			BasicType returnType;
			std::string identifier;
			std::vector<std::unique_ptr<ParameterDeclNode>> parameters;
			std::unique_ptr<Block> functionBody;

			FunctionDeclNode(BasicType type, std::string id,
							 std::vector<std::unique_ptr<ParameterDeclNode>> params,
							 std::unique_ptr<Block> body, int line)
				: returnType(type),
				  identifier(std::move(id)),
				  parameters(std::move(params)),
				  functionBody(std::move(body)),
				  ASTNode(line) {}
			virtual ~FunctionDeclNode() = default;
	};

	// Classe base para expressões
	class ExpressionNode : public ASTNode {
		public:

			ExpressionNode(int line)
				: ASTNode(line) {}
			virtual ~ExpressionNode() = default;
	};
}

#endif