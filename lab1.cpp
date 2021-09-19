#include <math.h>
#include <iostream>
#include <sys/times.h>
#include <unistd.h>
#include <string>
int main(int argc, char** argv) {
	struct tms start, end;
	long clocks_per_sec = sysconf(_SC_CLK_TCK);
	long clocks;
	if (argc < 3) {
		std::cout << "Недостаточно аргументов!\n" <<
			"Введите X и N\n";
	} 
	
	double x = atof(argv[1]);
	long long int n = atoll(argv[2]);
	double sin = x;
	double elem = x;
	int degree = 1;
	long long int fact = 1;

	times(&start);

	for (long long int i = 1; i <= n; i++) {
		elem *= x;
		elem /= i*2;
		elem *= x;
		elem /= i * 2 + 1;
		elem *= -1;
		sin += elem;
	}

	times(&end);
	clocks = end.tms_utime - start.tms_utime;
	std::cout << "Time taken: "
   		<<(double)clocks / clocks_per_sec
		<< " sec. \n";
	

	std::cout << "Answer: " << sin << "\n";
	return 0;
}
