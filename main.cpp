#include <math.h>
#include <iostream>
#include <string>
int main(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "Недостаточно аргументов!\n" <<
			"Введите X и N\n";
	} 
	
	double x = atof(argv[1]);
	int n = atoi(argv[2]);
	double sin = x;
	double elem = x;
	int degree = 1;
	long long int fact = 1;
	for (int i = 1; i <= n; i++) {
		elem *= x;
		elem /= i*2;
		elem *= x;
		elem /= i * 2 + 1;
		elem *= -1;
		sin += elem;
	}
	std::cout << "Ответ: " << sin;
}