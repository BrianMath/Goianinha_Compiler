#include <iostream>
#include <string>

int main() {
	std::string text = "banana1\nfrita2\nsem3\nsal4";
	int linha = 1, l = 0;

	for (auto c : text) {
		if (c == '\n') {l++;}
	}

	linha = 4;

	std::cout << "Erro na linha " << linha-l << "\n";

	return 0;
}