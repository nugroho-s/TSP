#pragma once

#define maks 100 //maksimum matriks dari file

extern int mati[maks][maks];

class TSP {
public:
	//!ctor dengan ukuran
	TSP(int);
	//!mencari bobot dari array best so far
	float getbobot(int[]);
	//!mencari dua indeks minimal dari baris idx
	void get2min(int idx, int*, int*);
private:
	int ukuran;
};