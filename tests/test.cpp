#include <iostream>

int main() {
	int num = 10;
	int num5 = 10;
	int& num2 = num;
	std::cout << "num = " << num << " | num2 = " << num2 << '\n';

	num = 20;
	std::cout << "num = " << num << " | num2 = " << num2 << '\n';

	num2 = 30;
	std::cout << "num = " << num << " | num2 = " << num2 << '\n';

	int* num3 = &num2;
	std::cout << "num = " << num << " | num2 = " << num2 << " | num3 = " << *num3 << '\n';

	num = 40;
	std::cout << "num = " << num << " | num2 = " << num2 << " | num3 = " << *num3 << '\n';

	num2 = 50;
	std::cout << "num = " << num << " | num2 = " << num2 << " | num3 = " << *num3 << '\n';

	*num3 = 60;
	std::cout << "num = " << num << " | num2 = " << num2 << " | num3 = " << *num3 << '\n';

	return 0;
}