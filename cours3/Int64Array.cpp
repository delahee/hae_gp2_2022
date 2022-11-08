#include "Int64Array.hpp"
#include <algorithm>

void Int64Array::ensure(int len) {
	if (allocSize <= len) {
		int toAlloc = std::max<int>(allocSize * 1.5f, len);
		data = (int64_t*)realloc(data, toAlloc * sizeof(int64_t));
		allocSize = toAlloc;
		setZero(cursor, allocSize);
	}
}

void Int64Array::print(int start) {
	if (start == 0 && cursor == 0) {
		printf("[]\n");
		return;
	}
	if (start >= cursor) {
		printf("\n");
		return;
	}
	printf("%lld ", data[start]);
	print(start + 1);
};