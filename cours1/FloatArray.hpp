#pragma once

#include <cstdlib>

//array with an alloc_size and a 'current' last element
class FloatArray {
	// constructeur
public:
	FloatArray(int nb) {
		data =(float*) malloc(nb*sizeof(float));
		allocSize = nb;
		for (int i = 0; i < allocSize; ++i)
			data[i] = 0;
	}

	~FloatArray() {
		free(data);
	}

	void resize(int sz){
		if (sz < allocSize)
			return;
		data = (float*)realloc(data, sz * sizeof(float));
		for (int i = allocSize; i < sz; ++i)
			data[i] = 0;
		allocSize = sz;
	}

	void push_first(float val) {
		//
	};

	void push_back(float val) {
		//
		resize(allocSize + 1);
		data[current] = val;
		current++;
	};

	void set(int idx, float val) {
		if (idx < 0) throw "bound check failed";
		if (idx >= current) throw "bound check failed";
		data[idx] = val;
	};
	
	float get(int idx) {
		if (idx < 0) throw "bound check failed";
		if (idx >= current) throw "bound check failed";
		return data[idx];
	};

	int	size() {
		return current;
	};

protected:
	float*	data = nullptr;
	int		allocSize = 0;
	int		current = 0;
};
