#pragma once

#include <cstdlib>
#include <functional>

//array with an alloc_size and a 'current' last element
class FloatArray {
	// constructeur
public:
	FloatArray(int nb = 0) {
		data =(float*) malloc(nb*sizeof(float) + 1);
		allocSize = nb;
		for (int i = 0; i < allocSize; ++i)
			data[i] = 0.0f;
	}

	~FloatArray() {
		free(data);
	}

	void print(){
		for (int i = 0; i < size(); ++i) {
			printf("%d => %f ", i, get(i));
		}
		printf("\n");
	}

	void resize(int sz){
		if (sz < allocSize)
			return;
		data = (float*)realloc(data, sz * sizeof(float));
		for (int i = allocSize; i < sz; ++i)
			data[i] = 0;
		allocSize = sz;
	}

	void iter(std::function<void(float)> f) {
		int sz = size();
		for (int i = 0; i < sz; i++)
			f(data[i]);
	};

	void push_first(float val) {
		//if necessary 
		if( current >= allocSize-1)
			resize(allocSize + 1);

		//shift right
		for (int i = current; i > 0; --i)
			data[i] = data[i - 1];
		//

		data[0] = val;
		current ++;
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
