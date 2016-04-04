#include "tsp.h"
#include <iostream>

using namespace std;

simpul::simpul() {
	sol = new int[usimpul];
	for (int i = 0; i < usimpul; i++)
		sol[i] = -1;
	hidup = true;
	bobot = -1;
}

int simpul::getfirstundef() {
	for (int i = 0; i < usimpul; i++) {
		if (sol[i] == -1)
			return i;
	}
	return -1;
}

bool simpul::gethidup() { return hidup; }

void simpul::sethidup(bool x) { hidup = x; }

void simpul::setbobot() {
	TSP t;
	bobot = t.getbobot(sol);
}

bool simpul::is_daun() {
	if (getfirstundef() == -1)
		return true;
	return false;
}

bool simpul::kosong() {
	for (int i = 1; i < ukuran; i++) {
		if (sol[i] != -1)
			return false;
	}
	return true;
}
bool simpul::insol(int x) {
	for (int i = 0; i < usimpul; i++) {
		if (sol[i] == x)
			return true;
	}
	return false;
}

TSP::TSP() {
	//do nothing
}

void TSP::get2min(int idx, int* imin1, int* imin2) {
	*imin1 = *imin2 = 0;
	if (idx == 0) {
		*imin1 = *imin2 = 1;
	}
	for (int i = 0; i < ukuran; i++) {
		if(idx != i)
			if (mati[idx][*imin1]>mati[idx][i]) {
				*imin1 = i;
			}
	}
	if (*imin1 == *imin2)
		(*imin2)++;
	for (int i = 0; i < ukuran; i++) {
		if (idx != i)
			if (mati[idx][*imin2]>mati[idx][i]) {
				if (i != *imin1) {
					*imin2 = i;
				}
			}
	}
}

float TSP::getbobot(int arr[]) {
	//harusnya sudah benar
	int i1, i2;
	int ikiri, ikanan;
	ikiri = ikanan = -1;
	int idxp = -1; //indeks di array solusi
	float sum = 0;
	for (int i = 0; i < ukuran; i++) {
		//cari di solusi
		for (int j = 0; j <= ukuran; j++) {
			if (arr[j] == i) {
				idxp = j;
				break;
			}
		}
		if (idxp == -1) {
			//kasus tidak ada di solusi
			get2min(i, &i1, &i2);
			sum = sum + mati[i][i1] + mati[i][i2];
		}
		else {
			//kasus ada di solusi
			if (idxp == 0) {
				//adalah simpul awal
				//cek kanan
				if (arr[idxp + 1] != -1) {
					ikanan = arr[idxp + 1];
					sum += mati[i][ikanan];
				}
				//cek belakang
				if (arr[ukuran - 1] != -1) {
					ikiri = arr[ukuran - 1];
					sum += mati[i][ikiri];
				}
			}
			else {
				//bukan simpul awal
				//cek kiri
				if (arr[idxp - 1] != -1) {
					ikiri = arr[idxp - 1];
					sum += mati[i][ikiri];
				}
				//cek kanan
				if (arr[idxp + 1] != -1) {
					ikanan = arr[idxp + 1];
					sum += mati[i][ikanan];
				}
			}
			if (!((ikanan != -1) && (ikiri != -1))) {
				//kasus jika tidak keduanya (kanan dan kiri) ada
				get2min(i, &i1, &i2);
				if (ikanan != -1) {
					//jika kanan ada
					if (ikanan == i1)
						sum += mati[i][i2];
					else
						sum += mati[i][i1];
				}
				else if (ikiri != -1) {
					//jika kiri ada
					if (ikiri == i1)
						sum += mati[i][i2];
					else
						sum += mati[i][i1];
				}
				else {
					//jika keduanya tidak ada
					sum = sum + mati[i][i1] + mati[i][i2];
				}
			}
		}
		cout << i << "   " << sum << endl;
		idxp = -1;
		ikiri = ikanan = -1;
	}
	sum /= 2;
	return sum;
}

int* TSP::carisolusi() {
	tree<simpul> tr;
	tree<simpul>::iterator top,root,now;
	top = tr.begin();
	simpul S;
	S.sol[0] = 0;
	S.sol[1] = 1;
	S.sol[ukuran] = 0;
	float bobot = getbobot(S.sol);
	cout << endl << "bobot = " << bobot;
	S.bobot = bobot;
	root = tr.insert(top, S);
	now = tr.begin();
	cout << endl << "bobot = " << now->bobot;
	return NULL;
}

void TSP::buatpohon(tree<simpul> t) {
	tree<simpul>::iterator root,p;
	root = t.begin();
	if (root->gethidup()) {
		if (root->is_daun()) {
			//kasus 1: simpul adalah daun
			if (best_sol_so_far.kosong()) {
				best_sol_so_far = *root;
			}
		}
		else {
			//kasus 2: simpul bukan daun
			//hidupkan anak-anaknya
			simpul temp;
			for (int i = 0; i < usimpul; i++)
				temp.sol[i] = root->sol[i];
			int idx = root->getfirstundef();
			for (int i = 0; i < ukuran; i++) {
				if (!(root->insol(i))) {
					//tambahkan simpul baru ke anak
					temp.sol[idx] = i;
					temp.setbobot();
					t.append_child(t.begin(), temp);
				}
			}
			//lakukan rekursif
			tree<simpul>::sibling_iterator s;
			s = t.begin(t.begin());
			while (s != t.end(t.begin())) {
				buatpohon(s);
				++s;
			}
		}
	}
	else {
		return;
	}
}