#include "tsp.h"
#include <iostream>

using namespace std;

TSP::TSP(int s) {
	ukuran = s;
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