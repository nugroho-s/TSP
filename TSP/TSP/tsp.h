#pragma once
#include "tree.hh"

#define maks 30 //maksimum matriks dari file

extern int mati[maks][maks];
extern int ukuran;

typedef struct {
	int* sol;
	float bobot;
	bool hidup;
}simpul;

class TSP {
public:
	//!ctor dengan ukuran
	TSP(int);
	//!mencari bobot dari array best so far
	float getbobot(int[]);
	//!mencari dua indeks minimal dari baris idx
	void get2min(int idx, int*, int*);
	//!membuat pohon
	simpul carisolusi();
};