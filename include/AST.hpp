#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include <memory>
#include <variant>

namespace AST {
	// Basic types
	enum class BasicType {
		INT, CAR
	};

	// Operators
	enum class Operator {
		// Logical operators
		OR, AND, NOT,

		// Relational operators
		EQUAL, DIFFERENT, LESS, LESS_EQUAL, GREATER, GREATER_EQUAL,

		// Arithmetic operators
		PLUS, MINUS, TIMES, DIVIDED,

		// Negation of a number
		NEGATIVE
	};

	// Basic class for an AST node
	class ASTNode {
		public:
			int line;

			ASTNode(int lineNum) : line(lineNum) {}
			virtual ~ASTNode() = default;
	};

	class ProgramNode : public ASTNode {
		public:
			std::vector<std::unique_ptr<ASTNode>> declarations;
			std::unique_ptr<BlockNode> mainBlock;

			ProgramNode(std::vector<std::unique_ptr<ASTNode>> decls, 
						std::unique_ptr<BlockNode> main, int line)
				: declarations(std::move(decls)),
				  mainBlock(std::move(main)),
				  ASTNode(line) {}
			virtual ~ProgramNode() = default;
	};

	// Base class for commands
	class CommandNode : public ASTNode {
		public:

			CommandNode(int line)
				: ASTNode(line) {}
			virtual ~CommandNode() = default;
	};

	// Block of commmands
	class BlockNode : public CommandNode {
		public:
			std::vector<std::unique_ptr<VariableDeclNode>> localVariables;
			std::vector<std::unique_ptr<CommandNode>> commands;

			BlockNode(std::vector<std::unique_ptr<VariableDeclNode>> listVar, 
				  std::vector<std::unique_ptr<CommandNode>> cmds, int line)
				: localVariables(std::move(listVar)),
				  commands(std::move(cmds)),
				  CommandNode(line) {}
			virtual ~BlockNode() = default;
	};

	// Simple expression command
	class ExpressionCommandNode : public CommandNode {
		public:
			std::unique_ptr<ExpressionNode> expression;

			ExpressionCommandNode(std::unique_ptr<ExpressionNode> expr, int line)
				: expression(std::move(expr)),
				  CommandNode(line) {}
			virtual ~ExpressionCommandNode() = default;
	};

	// Return command
	class ReturnCommandNode : public CommandNode {
		public:
			std::unique_ptr<ExpressionNode> returnExpression;

			ReturnCommandNode(std::unique_ptr<ExpressionNode> retExpr, int line)
				: returnExpression(std::move(retExpr)),
				  CommandNode(line) {}
			virtual ~ReturnCommandNode() = default;
	};

	// Read command
	class ReadCommandNode : public CommandNode {
		public:
			std::string identifier;

			ReadCommandNode(std::string id, int line) 
				: identifier(std::move(id)),
				  CommandNode(line) {}
			virtual ~ReadCommandNode() = default;
	};

	// Write command
	class WriteCommandNode : public CommandNode {
		public:
			std::variant<std::unique_ptr<ExpressionNode>, std::string> outputValue;

			WriteCommandNode(std::unique_ptr<ExpressionNode> val, int line)
				: outputValue(std::move(val)),
				  CommandNode(line) {}
			
			WriteCommandNode(std::string val, int line)
				: outputValue(std::move(val)),
				  CommandNode(line) {}

			virtual ~WriteCommandNode() = default;
	};

	// If/else command
	class IfCommandNode : public CommandNode {
		public:
			std::unique_ptr<ExpressionNode> condition;
			std::unique_ptr<CommandNode> thenCommand;
			std::unique_ptr<CommandNode> elseCommand; // Optional

			IfCommandNode(std::unique_ptr<ExpressionNode> cond,
						  std::unique_ptr<CommandNode> thenCmd,
						  std::unique_ptr<CommandNode> elseCmd,
						  int line)
				: condition(std::move(cond)),
				  thenCommand(std::move(thenCmd)),
				  elseCommand(std::move(elseCmd)),
				  CommandNode(line) {}
			virtual ~IfCommandNode() = default;
	};

	// While command
	class WhileCommandNode : public CommandNode {
		public:
			std::unique_ptr<ExpressionNode> condition;
			std::unique_ptr<CommandNode> body;
	
			WhileCommandNode(std::unique_ptr<ExpressionNode> cond,
							 std::unique_ptr<CommandNode> cmd,
							 int line)
				: condition(std::move(cond)),
				  body(std::move(cmd)),
				  CommandNode(line) {}
			virtual ~WhileCommandNode() = default;
	};

	// Variables declarations
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

	// Parameters declarations
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

	// Functions declarations
	class FunctionDeclNode : public ASTNode {
		public:
			BasicType returnType;
			std::string identifier;
			std::vector<std::unique_ptr<ParameterDeclNode>> parameters;
			std::unique_ptr<BlockNode> functionBody;

			FunctionDeclNode(BasicType type, std::string id,
							 std::vector<std::unique_ptr<ParameterDeclNode>> params,
							 std::unique_ptr<BlockNode> body, int line)
				: returnType(type),
				  identifier(std::move(id)),
				  parameters(std::move(params)),
				  functionBody(std::move(body)),
				  ASTNode(line) {}
			virtual ~FunctionDeclNode() = default;
	};

	// Base class for expressions
	class ExpressionNode : public ASTNode {
		public:

			ExpressionNode(int line)
				: ASTNode(line) {}
			virtual ~ExpressionNode() = default;
	};

	// Expressions with binary operations
	class BinaryOperationNode : public ExpressionNode {
		public:
			std::unique_ptr<ExpressionNode> leftOperand;
			Operator binaryOperator;
			std::unique_ptr<ExpressionNode> rightOperand;

			BinaryOperationNode(std::unique_ptr<ExpressionNode> leftOpnd, Operator binOp,
								std::unique_ptr<ExpressionNode> rightOpnd, int line)
				: leftOperand(std::move(leftOpnd)),
				  binaryOperator(binOp),
				  rightOperand(std::move(rightOpnd)),
				  ExpressionNode(line) {}
			virtual ~BinaryOperationNode() = default;
	};

	// Expressions with unary operations
	class UnaryOperationNode : public ExpressionNode {
		public:
			Operator unaryOperator;
			std::unique_ptr<ExpressionNode> rightOperand;

			UnaryOperationNode(Operator unOp, std::unique_ptr<ExpressionNode> rightOpnd,
							   int line)
				: unaryOperator(unOp),
				  rightOperand(std::move(rightOpnd)),
				  ExpressionNode(line) {}
			virtual ~UnaryOperationNode() = default;
	};

	// Expressions with assignment
	class AssignNode : public ExpressionNode {
		public:
			std::string identifier;
			std::unique_ptr<ExpressionNode> value;

			AssignNode(std::string id, std::unique_ptr<ExpressionNode> val, int line)
				: identifier(std::move(id)),
				  value(std::move(val)),
				  ExpressionNode(line) {}
			virtual ~AssignNode() = default;
	};

	// Identifier expression
	class IdExpressionNode : public ExpressionNode {
		public:
			std::string identifier;

			IdExpressionNode(std::string id, int line)
				: identifier(std::move(id)),
				  ExpressionNode(line) {}
			virtual ~IdExpressionNode() = default;
	};

	// Integer constant expression
	class IntConstNode : public ExpressionNode {
		public:
			long long intconst;

			IntConstNode(long long intLiteral, int line)
				: intconst(intLiteral),
				  ExpressionNode(line) {}
			virtual ~IntConstNode() = default;
	};

	// Character constant expression
	class CarConstNode : public ExpressionNode {
		public:
			char carconst;

			CarConstNode(char carLiteral, int line)
				: carconst(carLiteral),
				  ExpressionNode(line) {}
			virtual ~CarConstNode() = default;
	};
}

#endif