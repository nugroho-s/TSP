#define _CRT_SECURE_NO_WARNINGS
//file D:\repo\TSP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <cstdio>
#include "tsp.h"

using namespace std;

#define delim ',' //delimiter(pemisah) file input

void printmatriks(int [maks][maks],int);

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
	printmatriks(mati, c);
	inf.close();
	getchar();
	return 0;
}

void printmatriks(int mat[maks][maks],int s) {
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}