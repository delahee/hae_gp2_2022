#pragma once

#include <cstdlib>
class IntArray {
public:

	IntArray(int maxSize);

	int get(int idx);

	void set(int idx, int value);

	void resize(int nuSize) {
		if (nuSize == size)
			return;

		bool grow = nuSize > size;

		auto nuData = new int[nuSize];
		for (int i = 0; i < nuSize; ++i)
			nuData[i] = 0;

		int targetSize = (grow) ? size : nuSize;
		for (int i = 0; i < targetSize; ++i)
			nuData[i] = data[i];

		int* oldData = data;
		data = nuData;
		size = nuSize;
		delete[]oldData;
	};

	static int cmp(const void* a0, const void* a1);

	void sort() {
		//use sort(data, function);
		qsort(data, size, sizeof(int), cmp);
	};

	~IntArray() {
		delete[] data;
		size = 0;
	};

	//renvoie la position d'insertion, cad la derniere position valable ou mettre cet élément dans un
	//tablau trié
	int searchOrderInferior(int val) {
		int idx = 0;
		while ((data[idx] < val) && (idx < size))
			idx++;
		return idx;
	}


	//warning this function breaks the invariant by inserting a sentient
	void shiftRight(int idx) {
		if ((idx < 0) || (idx >= size))
			return;
		for (int i = size - 1; i > idx; --i)
			data[i] = data[i - 1];
		data[idx] = 0;
	};

	//invariant : mon tableau est trié
	bool isSorted() {
		for (int i = 0; i < size - 1; ++i)
			if (data[i] > data[i + 1])
				return false;
		return true;
	};

	void insertOrderInferior(int val) {
		//trouver l'endroit d'insertion
		// 
		int pos = searchOrderInferior(val);
		resize(getSize() + 1);
		//decaller de 1 vers la droite a l'endroit d'insertion
		shiftRight(pos);
		//inserer la nouvelle valeur
		set(pos, val);
	};

	int getSize() {
		return size;
	};

protected:
	int* data = nullptr;
	int		size = 0;
};