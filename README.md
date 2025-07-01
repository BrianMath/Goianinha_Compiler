# Compilador para a linguagem Goianinha

## Descrição
Esse compilador está sendo desenvolvido para a disciplina de Compiladores do curso de Ciência da Computação da [Universidade Federal de Goiás](https://ufg.br). 

A linguagem Goianinha é uma linguagem de programação simples (um subconjunto de C e em português), criada para fins didáticos. O compilador está sendo desenvolvido em **C++**.

## Progresso
O compilador consiste em 3 partes:
- ✅ Analisador Léxico e Tabela de Símbolos
- ✅ Analisador Sintático e Tratamento de Erros
- 🔁 Analisador Semântico e Geração de Código
	- ✅ Criação da árvore sintática abstrata (AST)
	- ⬜️ Análise semântica
	- ⬜️ Geração de código

## Como compilar
Para compilar o compilador, você precisa ter o **make** instalado. Execute algum dos comandos abaixo no terminal:

```bash
# Comando para compilar os arquivos do compilador
make all

# Comando para rodar a main do compilador
make run

# Comando para criar a (AST) para um programa Goianinha de teste (tests/goianinha.g)
make printer

# Comando para imprimir a AST de um programa Goianinha de teste (tests/goianinha.g)
make print

# Comando para limpar os arquivos compilados
make clean
```

## Exemplo de código em Goianinha
```C
int fatorial(int n){
	se (n==0)
	entao
		retorne 1;
	senao
		retorne n * fatorial(n-1);
}

programa {
	int n;
	n = 1-0;
	
	enquanto (n<0) execute {
    	escreva "digite um numero";
    	novalinha;
    	leia n;    
	}	

	escreva "O fatorial de ";
	escreva n;
	escreva " e: ";
	escreva fatorial(n);
	novalinha;
}
```

###### Legenda:
- ⬜️: Ainda não implementado
- 🔁: Em progresso
- ✅: Implementado