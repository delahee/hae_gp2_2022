#pragma once

#include <cstdint>
#include <cstdlib>

class Int64Array{
public:
	int64_t*		data = nullptr;
	int				allocSize = 0;
	int				cursor = 0;

	Int64Array(int _allocSize) {
		if (_allocSize <= 0)
			_allocSize = 16;
		data = (int64_t*) malloc(_allocSize * sizeof(int64_t));
		setZero(0, _allocSize);
		cursor = 0;
		allocSize = _allocSize;
	};

	~Int64Array() {
		free(data);
		data = nullptr;
	};

	int size(){
		return cursor;
	}

	void ensure(int len) {
		if (allocSize <= len) {
			int toAlloc = std::max<int>(allocSize * 1.5f, len);
			data = (int64_t*)realloc(data, toAlloc * sizeof(int64_t));
			allocSize = toAlloc;
			setZero(cursor, allocSize);
		}
	};

	void set_unsafe(int pos, int64_t elem) {
		data[pos] = elem;
	};

	void set(int pos, int64_t elem) {
		if (pos < 0 || pos >= cursor) throw "out of bounds";
		set_unsafe(pos, elem);
	};


	void offset(int idx0, int idx1){

	}

	void shift_right( int pos ){
		if (pos <= 0)
			return;

		// 0 1 2 3
		// 0 0 1 2 3
		data[pos] = data[pos-1];
		shift_right(pos - 1);
	}

	void push_front(int64_t elem) {
		ensure(cursor + 1);
		shift_right( cursor );
		set_unsafe(0, elem);
		cursor++;
	};

	void push_back(int64_t val) {
		ensure(cursor + 1);
		data[cursor] = val;
		cursor++;
	};
	void print( int start = 0){
		if (start >= cursor)
			return;
		printf("%lld ",data[start]);
		if (start >= cursor)
			printf("\n");
		else
			print(start + 1);
	}

protected:
	//shift ?

	void setZero(int start, int end) {
		if (start >= end)
			return;
		data[start] = 0;
		setZero(start + 1, end);
	};
};