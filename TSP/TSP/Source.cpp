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
#include <chrono>
#include "tsp.h"

using namespace std;

//extern declaration
int mati[maks][maks];
int ukuran;
int usimpul;
simpul best_sol_so_far;
float bobot_awal;
int jsimpul = 0;

#define delim ',' //delimiter(pemisah) file input

int getdigit(int);

void printmatriks(int [maks][maks],int,int);

int main() {
	int digit = 0;
	ifstream inf("graf.txt", std::ifstream::in);
	char matc[maks][maks];
	char* pch;
	int c = 0;
	//mulai baca file
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
	usimpul = c + 1;
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
	//akhir baca file
	//inisialisasi best so far
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;
	best_sol_so_far.bobot = maksbssf;
	TSP tsp;
	printmatriks(mati, c,digit);
	inf.close();
	auto t0 = Time::now();
	tsp.carisolusi();
	auto t1 = Time::now();
	fsec fs = t1 - t0;
	ms d = std::chrono::duration_cast<ms>(fs);
	cout << endl;
	//well, karena simpul sudah terlanjur mulai dari nol, tinggal tambah 1
	for (int i = 0; i < usimpul; i++) {
		cout << best_sol_so_far.sol[i]+1 << " ";
		if (i < usimpul - 1)
			cout << "-> ";
	}
	cout << endl;
	cout << "bobot = " << best_sol_so_far.bobot << endl;
	cout << "jumlah simpul yang dibangkitkan = " << jsimpul << endl;
	cout << "waktu eksekusi = " << d.count() << "ms\n";
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