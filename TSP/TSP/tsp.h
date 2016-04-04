#pragma once
#include "tree.hh"

#define maks 30 //maksimum matriks dari file

extern int mati[maks][maks];
extern int ukuran;
extern int usimpul;

class simpul {
public:
	simpul();
	//mengembalikan simpul pertama yang bernilai -1
	int getfirstundef();
	bool gethidup();
	void sethidup(bool);
	//mencari bobot simpul
	void setbobot();
	bool is_daun();
	//mengembalikan true jika hanya sol[0] dan sol[ukuran] yang bernilai bukan -1
	bool kosong();
	//mengembalikan apakah int ada di sol
	bool insol(int);
	friend class TSP;
private:
	int* sol;
	float bobot;
	bool hidup;
};

extern simpul best_sol_so_far;

class TSP {
public:
	//!ctor dengan ukuran
	TSP();
	//!mencari bobot dari array best so far
	float getbobot(int[]);
	//!mencari dua indeks minimal dari baris idx
	void get2min(int idx, int*, int*);
	//!membuat pohon
	int* carisolusi();
	//!buat pohon
	void buatpohon(tree<simpul>);
};