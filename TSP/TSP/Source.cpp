#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <cstdio>

using namespace std;

#define maks 100 //maksimum matriks dari file
#define delim ',' //delimiter(pemisah) file input

int main() {
	ifstream inf("graf.txt", std::ifstream::in);
	char matc[maks][maks];
	char* pch;
	int mati[maks][maks];
	int c = 0;
	if (!inf.good()) {
		cout << "error" << endl;
	}
	while (inf.good()) {
		inf.getline(matc[c], 100);
		c++;
	}
	int baris = 0;
	int kolom = 0;
	int temp;
	for (int i = 0; i < c; i++) {
		pch = strtok(matc[i], ",");
		while (pch != NULL) {
			temp = stoi(pch);
			mati[baris][kolom] = temp;
			kolom++;
			if (kolom >= c) {
				kolom = 0;
				baris++;
			}
			pch = strtok(NULL, ",");
		}
	}
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < c; j++) {
			cout << mati[i][j] << " ";
		}
		cout << endl;
	}
	inf.close();
	getchar();
	return 0;
}