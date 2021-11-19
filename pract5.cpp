#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
void multmatrix(float** M1, float** M2, float** Msum, int n) {
	float** res = new(float* [n]);
	for (int i = 0; i < n; i++) {
		res[i] = new(float[n]);
		for (int j = 0; j < n; j++) {
			res[i][j] = 0;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < n; k++) {
			for (int j = 0; j < n; j++) {
				res[i][j] += M1[i][k] * M2[k][j];
			}
		}
		if (Msum) {
			delete(Msum[i]);
		}
		Msum[i] = res[i];
	}

	delete[] res;
}

void plusmatrix(float** M1, float** M2, float** Msum, int n) {
	float** res = new(float* [n]);
	for (int i = 0; i < n; i++) {
		res[i] = new(float[n]);
		for (int j = 0; j < n; j++) {
			res[i][j] = M1[i][j] + M2[i][j];
		}
		if (Msum) {
			delete(Msum[i]);
		}
		Msum[i] = res[i];
	}

	delete[] res;
}

void minusmatrix(float** M1, float** M2, float** Msum, int n) {
	float** res = new(float* [n]);
	for (int i = 0; i < n; i++) {
		res[i] = new(float[n]);
		for (int j = 0; j < n; j++) {
			res[i][j] = M1[i][j] - M2[i][j];
		}
		if (Msum) {
			delete(Msum[i]);
		}
		Msum[i] = res[i];
	}
	
	delete[] res;
}


int main() {
	unsigned int time = 0;
	std::ifstream fin("file_in.txt");
	int n = 0;
	int m = 0;
	fin >> n;
	fin >> m;
	float** A = new(float* [n]);
	float** B = new(float* [n]);
	float** I = new(float* [n]);
	float** Arev = new(float* [n]);
	for (int i = 0; i < n; i++) {
		A[i] = new(float[n]);
		B[i] = new(float[n]);
		I[i] = new(float[n]);
		Arev[i] = new(float[n]);
		for (int j = 0; j < n; j++) {
			fin >> A[i][j];
			if (i == j) {
				I[i][j] = 1;
				Arev[i][j] = 1;
			}
			else {
				I[i][j] = 0;
				Arev[i][j] = 0;
			}
		}
	}

	time = clock();
	std::cout << "Time on input and initialisation: " << time << "\n";
	time = clock();
	float Ainf = -FLT_MAX;
	float A1 = -FLT_MAX;
	for (int i = 0; i < n; i++) {
		float sum = 0;
		for (int j = 0; j < n; j++) {
			sum += A[i][j];
		}
		if (sum > Ainf) {
			Ainf = sum;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[j][i] = A[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		float sum = 0;
		for (int j = 0; j < n; j++) {
			sum += B[i][j];
		}
		if (sum > A1) {
			A1 = sum;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[j][i] /= A1 * Ainf;
		}
	}

	float** R = new(float* [n]);
	for (int i = 0; i < n; i++) {
		R[i] = NULL;
	}
	multmatrix(B, A, R, n);
	minusmatrix(I, R, R, n);


	for (int i = 0; i < m - 1; i++) {
		multmatrix(I, R, I, n);
		plusmatrix(Arev, I, Arev, n);
	}

	multmatrix(Arev, B, Arev, n);

	time = clock() - time;
	std::cout << "Time on calculate: " << time << "\n";
	time = clock();
	std::ofstream fout("file_out.txt");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			fout << Arev[i][j] << " ";
		}
		fout << "\n";
	}
	time = clock() - time;
	std::cout << "Time on write: " << time << "\n";


}
