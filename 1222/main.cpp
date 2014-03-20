#include <fstream>
using namespace std;

#define MAX_SIZE 305000
#define MAX_COUNT 121

int Triangles[MAX_COUNT];
int Tetra[MAX_COUNT];

int MinArr[MAX_SIZE];

// Вычисляем массив, содержащий количества ядер во всевозможных тетраэдрах
void CalcTetra() {
	Triangles[0] = 1; Tetra[0] = 1;
	for (int i = 1; i < MAX_COUNT; ++i) {
		Triangles[i] = Triangles[i - 1] + i + 1;	
		Tetra[i] = Tetra[i - 1] + Triangles[i];
	}
}

// Находим максимальный размер тетраэдра, не превышающий заданное количество ядер
int CheckTetra(int cur_n) {
	int idx = 0;
	while (Tetra[idx] <= cur_n) ++idx;
	return --idx;
}

// Перебираем все варианты сумм, запоминая уже вычисленные минимальные значения в массив MinArr
int doAll(int cur_n) {
	if (MinArr[cur_n] != 0) return MinArr[cur_n];
	int max_idx = CheckTetra(cur_n);
	int cur_min_count = cur_n;	
	for (int i = max_idx; i >= 0; --i) {
		int cur_count = doAll(cur_n - Tetra[i]) + 1;
		if (cur_min_count > cur_count) cur_min_count = cur_count;		
	}
	MinArr[cur_n] = cur_min_count;
	return cur_min_count;
}



int main() {
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	int n;

	CalcTetra();
	fin >> n;
	fout << doAll(n) << endl;
		
	return 0;
}