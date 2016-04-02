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
	int i1, i2;
	int ikiri, ikanan;
	ikiri = ikanan = -1;
	int idxp = -1;
	float sum = 0;
	for (int i = 0; i < ukuran; i++) {
		if (arr[i] == -1) {
			get2min(i, &i1, &i2);
			sum = sum + mati[i][i1] + mati[i][i2];
		}
		else {
			if (i > 0) {
				//cek kiri
				if (arr[i - 1] != -1) {
					ikiri = arr[i - 1];
					sum += mati[i][ikiri];
				}
			}
			if (i + 1 < ukuran) {
				//cek kanan
				if (arr[i + 1] != -1) {
					ikanan = arr[i + 1];
					sum += mati[i][ikanan];
				}
			}
			if (!((ikanan != -1) && (ikiri != -1))) {
				get2min(i, &i1, &i2);
				if (ikanan != -1) {
					if (ikanan == i1)
						sum += mati[i][i2];
					else
						sum += mati[i][i1];
				}
				else if (ikiri != -1) {
					if (ikiri == i1)
						sum += mati[i][i2];
					else
						sum += mati[i][i1];
				}
				else {
					sum = sum + mati[i][i1] + mati[i][i2];
				}
				ikiri = ikanan = -1;
			}
		}
		cout << i << "   " << sum << endl;
	}
	sum /= 2;
	return sum;
}