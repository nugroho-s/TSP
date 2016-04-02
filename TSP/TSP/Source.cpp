#define _CRT_SECURE_NO_WARNINGS
//file D:\repo\TSP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <iomanip>
#include <conio.h>
#include "tsp.h"

using namespace std;

int mati[maks][maks];

#define delim ',' //delimiter(pemisah) file input

int getdigit(int);

void printmatriks(int [maks][maks],int,int);

int main() {
	int ukuran;
	int solusi[5] = { 0,3,-1,-1,0 };
	int digit = 0;
	ifstream inf("graf.txt", std::ifstream::in);
	char matc[maks][maks];
	char* pch;
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
	ukuran = c;
	/*solusi = new int[ukuran+1];
	solusi[0] = 0;
	solusi[ukuran] = 0;
	for (int i = 1; i < ukuran; i++)
		solusi[i] = -1;*/
	for (int i = 0; i < c; i++) {
		pch = strtok(matc[i], ",");
		while (pch != NULL) {
			temp = stoi(pch);
			if (getdigit(temp) > digit)
				digit = getdigit(temp);
			mati[baris][kolom] = temp;
			kolom++;
			if (kolom >= c) {
				kolom = 0;
				baris++;
			}
			pch = strtok(NULL, ",");
		}
	}
	TSP tsp(c);
	printmatriks(mati, c,digit);
	inf.close();
	float bobot = tsp.getbobot(solusi);
	cout << endl << "bobot = " << bobot;
	_getch();
	return 0;
}

int getdigit(int x) {
	int d = 0;
	while (x != 0) {
		x /= 10;
		d++;
	}
	return d;
}

void printmatriks(int mat[maks][maks],int s,int d) {
	for (int i = 0; i < s; i++) {
		for (int j = 0; j < s; j++) {
			cout << std::setw(d) << std::setfill('0') << mat[i][j] << " ";
		}
		cout << endl;
	}
}