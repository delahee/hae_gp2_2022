#pragma once

#include <cstdint>
#include <cstdlib>
#include "Lib.hpp"

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

	void ensure(int len);

	void set_unsafe(int pos, int64_t elem) {
		data[pos] = elem;
	};

	void set(int pos, int64_t elem) {
		if (pos < 0 || pos >= cursor) throw "out of bounds";
		set_unsafe(pos, elem);
	};

	void shift_right( int stop, int pos ){
		if (pos <= stop)
			return;
		// 0 1 2 3
		// 0 0 1 2 3
		data[pos] = data[pos-1];
		shift_right(stop, pos - 1);
	}

	void shift_left(int start, int stop) {
		if (start >= stop-1)
			return;
		int64_t p0 = data[start];
		int64_t p1 = data[start+1];
		//it's magical the rest is done
		shift_left(start+1, stop);// 0 1 2 => 0 2
		data[start] = p1;
	}

	void push_front(int64_t elem) {
		ensure(cursor + 1);
		shift_right( 0,cursor );
		set_unsafe(0, elem);
		cursor++;
	};

	void push_back(int64_t val) {
		ensure(cursor + 1);
		data[cursor] = val;
		cursor++;
	};

	void print(int start = 0);


	void insert( int pos, int64_t elem) {
		ensure(cursor + 1);
		shift_right(pos, cursor);
		set_unsafe(pos, elem);
		cursor++;
	};

	void fillWithRandom(int nbElem) {
		if (nbElem <= 0)
			return;
		push_front(Lib::rand() * Lib::rand() * Lib::rand() + Lib::rand());
		fillWithRandom(nbElem-1);
	};

protected:
	int _searchPosition(int64_t elem, int start = 0) { //renvoyer la position d’insertion ou -1 si pas trouvé
		if ((start < 0) || start >= cursor)
			return -1;
		if (data[start] == elem)
			return start;
		return _searchPosition(elem, start + 1);
	};
public:

	int searchPosition(int64_t elem) { //renvoyer la position d’insertion ou -1 si pas trouvé
		return _searchPosition(elem);
	};

	void removeAt(int idx) {
		shift_left(idx, cursor);
		cursor--;
	};

	bool removeOne(int64_t elem) {
		int pos = searchPosition(elem);
		if (pos < 0)
			return false;
		shift_left(pos, cursor);
		cursor--;
		return true;
	};

	void removeAll(int64_t elem) {
		bool one = removeOne(elem);
		if (!one)
			return;
		removeAll(elem);
	};


protected:
	//shift ?

	void setZero(int start, int end) {
		if (start >= end)
			return;
		data[start] = 0;
		setZero(start + 1, end);
	};
};