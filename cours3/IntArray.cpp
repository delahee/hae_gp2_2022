#include "IntArray.hpp"

IntArray::IntArray(int maxSize) {
	//alloue data
	//change la taille reelle
	data = new int[maxSize];
	//data = (int*) malloc(maxSize*sizeof(int));
	size = maxSize;
	for (int i = 0; i < maxSize; ++i)
		data[i] = 0;
}

int IntArray::get(int idx) {
	if (idx < 0) throw "out of bound exception, bound cannot be inf to 0";
	if (idx >= size) throw "out of bound exception, bound cannot be sup to size";

	return data[idx];
}

void IntArray::set(int idx, int value) {
	if (idx < 0) throw "out of bound exception, bound cannot be inf to 0";
	if (idx >= size) throw "out of bound exception, bound cannot be sup to size";
	data[idx] = value;
}

int IntArray::cmp(const void* a0, const void* a1) {
	int* i0 = (int*)a0;
	int* i1 = (int*)a1;
	//(int) a0 <- addresse de a0 mais sous forme entiere 0xfzbuzv=> 501538687

	int i0Val = *i0;
	int i1Val = *i1;
	if (i0Val < i1Val) return -1;
	if (i0Val > i1Val) return 1;
	return 0;
};
