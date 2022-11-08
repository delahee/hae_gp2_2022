#include "FloatArray.hpp"

void FloatArray::push_first(float val) {
	//if necessary 
	if (current >= allocSize - 1)
		resize(allocSize + 1);

	//shift right
	for (int i = current; i > 0; --i)
		data[i] = data[i - 1];

	data[0] = val;
	current++;
}

FloatArray FloatArray::fromArray( float* data, int len) {
	FloatArray f;
	f.resize(len);
	for (int i = 0; i < len; ++i)
		f.push_back(data[i]);
	return f;
}
