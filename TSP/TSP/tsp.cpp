#include "tsp.h"
#include <iostream>

using namespace std;

elemen::elemen(int x) {
	node = x;
	anak = new int[ukuran];
	for (int i = 0; i < ukuran; i++) {
		anak[i] = mati[x][i];
	}
}