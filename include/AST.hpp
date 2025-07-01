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

	class CommandNode;
	class BlockNode;
	class ExpressionNode;
	class VariableDeclNode;

	// Basic class for an AST node
	class ASTNode {
		public:
			int line;

			ASTNode(int lineNum) : line(lineNum) {}
			virtual ~ASTNode() = default;

			virtual void print(int indent = 0) const = 0;
	};

	class ProgramNode : public ASTNode {
		public:
			std::vector<std::unique_ptr<ASTNode>> declarations;
			std::unique_ptr<BlockNode> mainBlock;

			ProgramNode(std::vector<std::unique_ptr<ASTNode>> decls, 
						std::unique_ptr<BlockNode> main, int line)
				: ASTNode(line), 
				  declarations(std::move(decls)),
				  mainBlock(std::move(main)) {}
			virtual ~ProgramNode() = default;
			void print(int indent = 0) const override;
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
				: CommandNode(line),
				  localVariables(std::move(listVar)),
				  commands(std::move(cmds)) {}
			virtual ~BlockNode() = default;
			void print(int indent = 0) const override;
	};

	// Simple expression command
	class ExpressionCommandNode : public CommandNode {
		public:
			std::unique_ptr<ExpressionNode> expression;

			ExpressionCommandNode(std::unique_ptr<ExpressionNode> expr, int line)
				: CommandNode(line),
				  expression(std::move(expr)) {}
			virtual ~ExpressionCommandNode() = default;
			void print(int indent = 0) const override;
	};

	// Return command
	class ReturnCommandNode : public CommandNode {
		public:
			std::unique_ptr<ExpressionNode> returnExpression;

			ReturnCommandNode(std::unique_ptr<ExpressionNode> retExpr, int line)
				: CommandNode(line),
				  returnExpression(std::move(retExpr)) {}
			virtual ~ReturnCommandNode() = default;
			void print(int indent = 0) const override;
	};

	// Read command
	class ReadCommandNode : public CommandNode {
		public:
			std::string identifier;

			ReadCommandNode(std::string id, int line) 
				: CommandNode(line),
				  identifier(std::move(id)) {}
			virtual ~ReadCommandNode() = default;
			void print(int indent = 0) const override;
	};

	// Write command
	class WriteCommandNode : public CommandNode {
		public:
			std::variant<std::unique_ptr<ExpressionNode>, std::string> outputValue;

			WriteCommandNode(std::unique_ptr<ExpressionNode> val, int line)
				: CommandNode(line),
				  outputValue(std::move(val)) {}
			
			WriteCommandNode(std::string val, int line)
				: CommandNode(line),
				  outputValue(std::move(val)) {}

			virtual ~WriteCommandNode() = default;
			void print(int indent = 0) const override;
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
				: CommandNode(line),
				  condition(std::move(cond)),
				  thenCommand(std::move(thenCmd)),
				  elseCommand(std::move(elseCmd)) {}
			virtual ~IfCommandNode() = default;
			void print(int indent = 0) const override;
	};

	// While command
	class WhileCommandNode : public CommandNode {
		public:
			std::unique_ptr<ExpressionNode> condition;
			std::unique_ptr<CommandNode> body;
	
			WhileCommandNode(std::unique_ptr<ExpressionNode> cond,
							 std::unique_ptr<CommandNode> cmd,
							 int line)
				: CommandNode(line),
				  condition(std::move(cond)),
				  body(std::move(cmd)) {}
			virtual ~WhileCommandNode() = default;
			void print(int indent = 0) const override;
	};

	// Variables declarations
	class VariableDeclNode : public ASTNode {
		public:
			BasicType variableType;
			std::vector<std::string> identifiers;

			VariableDeclNode(BasicType type, std::vector<std::string> ids, int line)
				: ASTNode(line),
				  variableType(type),
				  identifiers(std::move(ids)) {}
			virtual ~VariableDeclNode() = default;
			void print(int indent = 0) const override;
	};

	// Parameters declarations
	class ParameterDeclNode : public ASTNode {
		public:
			BasicType parameterType;
			std::string identifier;

			ParameterDeclNode(BasicType type, std::string id, int line)
				: ASTNode(line),
				  parameterType(type),
				  identifier(std::move(id)) {}
			virtual ~ParameterDeclNode() = default;
			void print(int indent = 0) const override;
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
				: ASTNode(line),
				  returnType(type),
				  identifier(std::move(id)),
				  parameters(std::move(params)),
				  functionBody(std::move(body)) {}
			virtual ~FunctionDeclNode() = default;
			void print(int indent = 0) const override;
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
				: ExpressionNode(line),
				  leftOperand(std::move(leftOpnd)),
				  binaryOperator(binOp),
				  rightOperand(std::move(rightOpnd)) {}
			virtual ~BinaryOperationNode() = default;
			void print(int indent = 0) const override;
	};

	// Expressions with unary operations
	class UnaryOperationNode : public ExpressionNode {
		public:
			Operator unaryOperator;
			std::unique_ptr<ExpressionNode> rightOperand;

			UnaryOperationNode(Operator unOp, std::unique_ptr<ExpressionNode> rightOpnd,
							   int line)
				: ExpressionNode(line),
				  unaryOperator(unOp),
				  rightOperand(std::move(rightOpnd)) {}
			virtual ~UnaryOperationNode() = default;
			void print(int indent = 0) const override;
	};

	// Expressions with assignment
	class AssignNode : public ExpressionNode {
		public:
			std::string identifier;
			std::unique_ptr<ExpressionNode> value;

			AssignNode(std::string id, std::unique_ptr<ExpressionNode> val, int line)
				: ExpressionNode(line),
				  identifier(std::move(id)),
				  value(std::move(val)) {}
			virtual ~AssignNode() = default;
			void print(int indent = 0) const override;
	};

	// Function call expression
	class FunctionCallNode : public ExpressionNode {
		public:
			std::string identifier;
			std::vector<std::unique_ptr<AST::ExpressionNode>> arguments; // Optional

			FunctionCallNode(std::string id, std::vector<std::unique_ptr<AST::ExpressionNode>> args, 
							 int line)
				: ExpressionNode(line),
				  identifier(std::move(id)),
				  arguments(std::move(args)) {}
			virtual ~FunctionCallNode() = default;
			void print(int indent = 0) const override;
	};

	// Identifier expression
	class IdExpressionNode : public ExpressionNode {
		public:
			std::string identifier;

			IdExpressionNode(std::string id, int line)
				: ExpressionNode(line),
				  identifier(std::move(id)) {}
			virtual ~IdExpressionNode() = default;
			void print(int indent = 0) const override;
	};

	// Integer constant expression
	class IntConstNode : public ExpressionNode {
		public:
			long long intconst;

			IntConstNode(long long intLiteral, int line)
				: ExpressionNode(line),
				  intconst(intLiteral) {}
			virtual ~IntConstNode() = default;
			void print(int indent = 0) const override;
	};

	// Character constant expression
	class CarConstNode : public ExpressionNode {
		public:
			char carconst;

			CarConstNode(char carLiteral, int line)
				: ExpressionNode(line),
				  carconst(carLiteral) {}
			virtual ~CarConstNode() = default;
			void print(int indent = 0) const override;
	};
}

#endif