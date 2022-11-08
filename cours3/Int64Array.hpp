#pragma once

#include <cstdint>
#include <cstdlib>
#include "Lib.hpp"
#include <corecrt_search.h>

class Int64Array{
public:
	int64_t*		data = nullptr;
	int				allocSize = 0;
	int				cursor = 0;

	Int64Array(int _allocSize) {
		if (_allocSize <= 0)
			_allocSize = 16;
		data = (int64_t*) malloc(_allocSize * sizeof(int64_t));
		//setZero(0, _allocSize);
		memset(data, 0, _allocSize * sizeof(int64_t));
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

	int64_t get_unsafe(int pos){
		return data[pos];
	}

	int64_t get(int pos) {
		if (pos < 0 || pos >= cursor) throw "out of bounds";
		return data[pos];
	}

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
		int _searchOrderedPosition(int64_t elem, int start = 0) { //renvoyer la position d’insertion ou -1 si pas trouvé
			if(start < 0)
				return -1;
			if (start >= cursor)
				return cursor;
			if (elem <= data[start])
				return start;
			return _searchOrderedPosition(elem, start + 1);
		};

		public:

	int searchOrderedPos(int64_t elem){
		return _searchOrderedPosition(elem);
	}

	void addElementsInASortedArray(int start, Int64Array& in) {
		if (start >= size())
			return;
		///prendre le premier element
		int64_t elem = get(start);
		// trouver ou on devrait l'inserer de facon trié
		int insertionPos = in.searchOrderedPos(elem);
		if (insertionPos == -1)
			return;
		// inserer
		in.insert(insertionPos, elem);
		in.print();
		addElementsInASortedArray(start + 1, in);
	};

	//returns a shallow array with ref content sorted
	static Int64Array* sort(Int64Array& ref) {

		//je m'alloue un tableau
		if (ref.size() == 0)
			return new Int64Array(1);
		auto res = new Int64Array(ref.size());

		//insert content of ref but in a sorted fashion
		ref.addElementsInASortedArray(0, *res);

		return res;
	};

	void swap(int idx0, int idx1){
		int64_t tmp = data[idx0];
		data[idx0] = data[idx1];
		data[idx1] = tmp;
	}

	static void insertionSort(Int64Array& t) {
		for (int i = 1; i < t.size(); ++i) {
			int j = i;
			while ((j > 0) && (t.get(j) < t.get(j - 1))) {
				t.swap(j, j - 1);
				j--;
			}
			//t.print();
		}
	};

	static int compare( const void* a0, const void* a1) {
		int64_t a640 = *((int64_t*)(a0));
		int64_t a641 = *((int64_t*)(a1));
		if (a641 < a640)
			return 1;
		else  if (a641 > a640)
			return -1;
		else return 0;
	};

	void stdQsort() {
		qsort(data, size(), sizeof(int64_t), compare);
	};

	int bsearchRec( int64_t key, int start, int end/*inclus*/ ) {
		if (start > end)
			return -1;
		if (data[start] == key)
			return  start;
		if (data[end] == key)
			return  end;
		int mid = (start + end) >> 1;
		if (data[mid] == key)
			return mid;
		if(data[mid] > key)
			return bsearchRec(key,start + 1, mid - 1);
		else 
			return bsearchRec(key, mid + 1, end);
	};
	
	int linearSearch( int64_t key, int start, int end/*inclus*/ ) {
		for(int i = start; i < end;++i)
			if (data[i] == key)
				return i;
		return -1;
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