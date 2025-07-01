#include <iostream>
#include <string>
#include "../include/AST.hpp"


// Imprime espaços para a indentação
void printIndent(int indent) {
    std::cout << std::string(indent * 2, ' ');
}

// Converte BasicType para string
std::string basicTypeToString(AST::BasicType type) {
    switch (type) {
        case AST::BasicType::INT: return "INT";
        case AST::BasicType::CAR: return "CAR";
    }
    return "UNKNOWN_TYPE";
}

// Converte Operator para string
std::string operatorToString(AST::Operator op) {
    switch (op) {
        case AST::Operator::OR: return "OR";
        case AST::Operator::AND: return "AND";
        case AST::Operator::NOT: return "NOT";
        case AST::Operator::EQUAL: return "==";
        case AST::Operator::DIFFERENT: return "!=";
        case AST::Operator::LESS: return "<";
        case AST::Operator::LESS_EQUAL: return "<=";
        case AST::Operator::GREATER: return ">";
        case AST::Operator::GREATER_EQUAL: return ">=";
        case AST::Operator::PLUS: return "+";
        case AST::Operator::MINUS: return "-";
        case AST::Operator::TIMES: return "*";
        case AST::Operator::DIVIDED: return "/";
        case AST::Operator::NEGATIVE: return "- (unary)";
    }
    return "UNKNOWN_OPERATOR";
}

// --- Implementações do Método Print ---

void AST::ProgramNode::print(int indent) const {
    printIndent(indent);
    std::cout << "ProgramNode (line " << line << ")" << std::endl;
    
    if (!declarations.empty()) {
        printIndent(indent + 1);
        std::cout << "Declarations:" << std::endl;
        for (const auto& decl : declarations) {
            decl->print(indent + 2);
        }
    }

    printIndent(indent + 1);
    std::cout << "Main Block:" << std::endl;
    mainBlock->print(indent + 2);
}

void AST::BlockNode::print(int indent) const {
    printIndent(indent);
    std::cout << "BlockNode (line " << line << ")" << std::endl;

    if (!localVariables.empty()) {
        printIndent(indent + 1);
        std::cout << "Local Variables:" << std::endl;
        for (const auto& var : localVariables) {
            var->print(indent + 2);
        }
    }

    if (!commands.empty()) {
        printIndent(indent + 1);
        std::cout << "Commands:" << std::endl;
        for (const auto& cmd : commands) {
            cmd->print(indent + 2);
        }
    }
}

void AST::ExpressionCommandNode::print(int indent) const {
    printIndent(indent);
    std::cout << "ExpressionCommandNode (line " << line << ")" << std::endl;
    expression->print(indent + 1);
}

void AST::ReturnCommandNode::print(int indent) const {
    printIndent(indent);
    std::cout << "ReturnCommandNode (line " << line << ")" << std::endl;
    if (returnExpression) {
        returnExpression->print(indent + 1);
    }
}

void AST::ReadCommandNode::print(int indent) const {
    printIndent(indent);
    std::cout << "ReadCommandNode (line " << line << "): " << identifier << std::endl;
}

void AST::WriteCommandNode::print(int indent) const {
    printIndent(indent);
    std::cout << "WriteCommandNode (line " << line << ")" << std::endl;
    
    std::visit([indent](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::unique_ptr<ExpressionNode>>) {
            arg->print(indent + 1);
        } else if constexpr (std::is_same_v<T, std::string>) {
            printIndent(indent + 1);
            std::cout << "StringLiteral: \"" << arg << "\"" << std::endl;
        }
    }, outputValue);
}

void AST::IfCommandNode::print(int indent) const {
    printIndent(indent);
    std::cout << "IfCommandNode (line " << line << ")" << std::endl;
    
    printIndent(indent + 1);
    std::cout << "Condition:" << std::endl;
    condition->print(indent + 2);

    printIndent(indent + 1);
    std::cout << "Then:" << std::endl;
    thenCommand->print(indent + 2);

    if (elseCommand) {
        printIndent(indent + 1);
        std::cout << "Else:" << std::endl;
        elseCommand->print(indent + 2);
    }
}

void AST::WhileCommandNode::print(int indent) const {
    printIndent(indent);
    std::cout << "WhileCommandNode (line " << line << ")" << std::endl;

    printIndent(indent + 1);
    std::cout << "Condition:" << std::endl;
    condition->print(indent + 2);

    printIndent(indent + 1);
    std::cout << "Body:" << std::endl;
    body->print(indent + 2);
}

void AST::VariableDeclNode::print(int indent) const {
    printIndent(indent);
    std::cout << "VariableDeclNode (line " << line << ")" << std::endl;
    printIndent(indent + 1);
    std::cout << "Type: " << basicTypeToString(variableType) << std::endl;
    printIndent(indent + 1);
    std::cout << "Identifiers: ";
    for (size_t i = 0; i < identifiers.size(); ++i) {
        std::cout << identifiers[i] << (i == identifiers.size() - 1 ? "" : ", ");
    }
    std::cout << std::endl;
}

void AST::ParameterDeclNode::print(int indent) const {
    printIndent(indent);
    std::cout << "ParameterDeclNode (line " << line << "): " << identifier 
              << " | Type: " << basicTypeToString(parameterType) << std::endl;
}

void AST::FunctionDeclNode::print(int indent) const {
    printIndent(indent);
    std::cout << "FunctionDeclNode (line " << line << "): " << identifier << std::endl;
    printIndent(indent + 1);
    std::cout << "Return Type: " << basicTypeToString(returnType) << std::endl;

    if (!parameters.empty()) {
        printIndent(indent + 1);
        std::cout << "Parameters:" << std::endl;
        for (const auto& param : parameters) {
            param->print(indent + 2);
        }
    }
    
    printIndent(indent + 1);
    std::cout << "Body:" << std::endl;
    functionBody->print(indent + 2);
}

void AST::BinaryOperationNode::print(int indent) const {
    printIndent(indent);
    std::cout << "BinaryOperationNode (line " << line << "): " << operatorToString(binaryOperator) << std::endl;
    leftOperand->print(indent + 1);
    rightOperand->print(indent + 1);
}

void AST::UnaryOperationNode::print(int indent) const {
    printIndent(indent);
    std::cout << "UnaryOperationNode (line " << line << "): " << operatorToString(unaryOperator) << std::endl;
    rightOperand->print(indent + 1);
}

void AST::AssignNode::print(int indent) const {
    printIndent(indent);
    std::cout << "AssignNode (line " << line << "): " << identifier << " =" << std::endl;
    value->print(indent + 1);
}

void AST::FunctionCallNode::print(int indent) const {
    printIndent(indent);
    std::cout << "FunctionCallNode (line " << line << "): " << identifier << std::endl;

    if (!arguments.empty()) {
        printIndent(indent + 1);
        std::cout << "Arguments:" << std::endl;
        for (const auto& arg : arguments) {
            arg->print(indent + 2);
        }
    }
}

void AST::IdExpressionNode::print(int indent) const {
    printIndent(indent);
    std::cout << "IdExpressionNode (line " << line << "): " << identifier << std::endl;
}

void AST::IntConstNode::print(int indent) const {
    printIndent(indent);
    std::cout << "IntConstNode (line " << line << "): " << intconst << std::endl;
}

void AST::CarConstNode::print(int indent) const {
    printIndent(indent);
    std::cout << "CarConstNode (line " << line << "): '" << carconst << "'" << std::endl;
}

int main() {
    using namespace AST;

    // Constrói a AST para o programa:
    // int x,y,z,v;
    // programa{
    // 	z=y=x=50; 
    // 	escreva x; escreva " "; escreva y; escreva " "; escreva z;
    // 	novalinha; 
    // 	escreva x*2-y/4;
    // 	escreva "boi";
    // }

    // 1. Declaração de variáveis globais
    auto global_var_decl = std::make_unique<VariableDeclNode>(
        BasicType::INT,
        std::vector<std::string>{"x", "y", "z", "v"},
        1 // número da linha
    );

    std::vector<std::unique_ptr<ASTNode>> global_decls;
    global_decls.push_back(std::move(global_var_decl));

    // 2. Bloco Principal (programa)
    std::vector<std::unique_ptr<CommandNode>> main_cmds;

    // Comando: z=y=x=50; (linha 3)
    // Representado como z = (y = (x = 50))
    auto assign_x = std::make_unique<AssignNode>("x", std::make_unique<IntConstNode>(50, 3), 3);
    auto assign_y = std::make_unique<AssignNode>("y", std::move(assign_x), 3);
    auto assign_z = std::make_unique<AssignNode>("z", std::move(assign_y), 3);
    main_cmds.push_back(std::make_unique<ExpressionCommandNode>(std::move(assign_z), 3));
    
    // Comandos: escreva x; escreva " "; escreva y; escreva " "; escreva z; (linha 4)
    main_cmds.push_back(std::make_unique<WriteCommandNode>(std::make_unique<IdExpressionNode>("x", 4), 4));
    main_cmds.push_back(std::make_unique<WriteCommandNode>(" ", 4));
    main_cmds.push_back(std::make_unique<WriteCommandNode>(std::make_unique<IdExpressionNode>("y", 4), 4));
    main_cmds.push_back(std::make_unique<WriteCommandNode>(" ", 4));
    main_cmds.push_back(std::make_unique<WriteCommandNode>(std::make_unique<IdExpressionNode>("z", 4), 4));

    // Comando: novalinha; (linha 5)
    // Representado como escreva "\n"
    main_cmds.push_back(std::make_unique<WriteCommandNode>("\n", 5));

    // Comando: escreva x*2-y/4; (linha 6)
    // Representado como (x * 2) - (y / 4) para respeitar a precedência de operadores
    auto expr_mult = std::make_unique<BinaryOperationNode>(
        std::make_unique<IdExpressionNode>("x", 6), Operator::TIMES, std::make_unique<IntConstNode>(2, 6), 6);
    auto expr_div = std::make_unique<BinaryOperationNode>(
        std::make_unique<IdExpressionNode>("y", 6), Operator::DIVIDED, std::make_unique<IntConstNode>(4, 6), 6);
    auto expr_sub = std::make_unique<BinaryOperationNode>(
        std::move(expr_mult), Operator::MINUS, std::move(expr_div), 6);
    main_cmds.push_back(std::make_unique<WriteCommandNode>(std::move(expr_sub), 6));

    // Comando: escreva "boi"; (linha 7)
    main_cmds.push_back(std::make_unique<WriteCommandNode>("boi", 7));

    auto main_block = std::make_unique<BlockNode>(
        std::vector<std::unique_ptr<VariableDeclNode>>(), // sem variáveis locais no bloco
        std::move(main_cmds),
        2 // linha de início do bloco 'programa'
    );

    // 3. Nó do Programa (Raiz da AST)
    auto program = std::make_unique<ProgramNode>(std::move(global_decls), std::move(main_block), 1);

    // 4. Imprimir a AST
    program->print();

    return 0;
}