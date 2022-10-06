// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include <string> //fichier systeme
//#include "string" // fichier du projet
#include <unordered_map>

using namespace std;

struct Toto{
    float x = 0.777f;
};

struct Vec2{
    float x = 0;
    float y = 0;
    Vec2(){}
    Vec2(float _x, float _y) {
		x = _x;
        y = _y;
    };
	void add(Vec2 v) {
		x += v.x;
		y += v.y;
	};

	void addRef(Vec2& v) {
		x += v.x;
		y += v.y;
	};

	void addPtr(Vec2* v) {
		//??

       // x += v->x;
        x += (*v).x;
        //y += v->y;
	};
};

struct Vec3 : public Vec2{
	float z = 0;

    Vec3(){}

    Vec3(float _x, float _y, float _z) : Vec2(_x, _y) {
        z = _z;
    };

    void add(Vec3 v) {
        Vec2::add(v);
        z += v.z;
    };

	void addRef(Vec3& v) {
		Vec2::addRef(v);
		z += v.z;
	}; 

    void addPtr(Vec3*v) {
		Vec2::addPtr(v);
        z += v->z;
    };

};

struct Vec4{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;

    Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    //
    Vec4 add(const Vec4& v) {
        return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
    };

	Vec4 sub(const Vec4& v) {
		return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	Vec4 mul(const Vec4& v) {
        return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	Vec4 div(const Vec4& v) {
        return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	void incr(const Vec4& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}

    static Vec4 ZERO;
};

Vec4 Vec4::ZERO = Vec4();

void testVec4(){
	{
		Vec3 sapin;

		Vec3 v0(6, 7, 8);
		Vec3 v1(1, 2, 3);

		//v1.add(v0);
		v1.addRef(v0);
		int here = 0;


	}

	{
		Vec3 v0(6, 7, 8);
		Vec3 v1(1, 2, 3);

		v0.addPtr(&v1);
		int here = 0;
	}

	{
		Vec4 a(0, 1, 0, 1);
		Vec4 b(0, 1);

		{
			Vec4 res = a.add(b);
			if (res.x != 0) throw "assert";
			if (res.y != 2) throw "assert";
			int here = 0;
		}

		{
			Vec4 res = a.sub(b);
			if (res.x != 0) throw "assert";
			if (res.y != 0) throw "assert";
			auto v = Vec4::ZERO;
			int here = 0;
		}

		{
			Vec4* r0 = new Vec4();
			//int here = 0;
			Vec4* r1 = new Vec4;
			Vec4* r2 = nullptr;

			Vec4* r3 = new Vec4[16];
			r3[4].incr(Vec4(666, 0, 0, 0));

			auto r34 = r3[4];
			auto r34bis = *(r3 + 4);

			int here = 0;

		}
	}
}


class IntArray{
public:

	IntArray(int maxSize) {//
		//alloue data
		//change la taille reelle
		data = new int[maxSize];
		//data = (int*) malloc(maxSize*sizeof(int));
		size = maxSize;
		for (int i = 0; i < maxSize; ++i)
			data[i] = 0;
	};

	int get(int idx) {
		if (idx < 0) throw "out of bound exception, bound cannot be inf to 0";
		if (idx >= size) throw "out of bound exception, bound cannot be sup to size";

		return data[idx];
	};

	void set(int idx, int value) {
		if (idx < 0) throw "out of bound exception, bound cannot be inf to 0";
		if (idx >= size) throw "out of bound exception, bound cannot be sup to size";
		data[idx] = value;
	};

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

	
	static int cmp(const void* a0, const void* a1) {
		int* i0 = (int*)a0;
		int* i1 = (int*)a1;
		//(int) a0 <- addresse de a0 mais sous forme entiere 0xfzbuzv=> 501538687

		int i0Val = *i0;
		int i1Val = *i1;
		if (i0Val < i1Val) return -1;
		if (i0Val > i1Val) return 1;
		return 0;
	};

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
	int searchOrderInferior(int val){
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
	int*	data = nullptr;
	int		size = 0;
};

static void assert(bool test) {
	if (!test)
		throw "assert";
};

void testArray(){


	{
		IntArray a(16);
		a.set(0, 3);
		a.set(15, 4);
		if (a.get(4) != 0)throw "assert";
		int here = 0;
	}
	{
		IntArray a(8);
		if (a.get(0) != 0)throw "assert";
		a.set(2, 666);
		a.set(a.getSize() - 1, 777);

		a.resize(5);
		if (a.getSize() != 5)throw "assert";
		if (a.get(2) != 666)throw "assert";

		a.resize(1024);
		assert(a.get(256) == 0);
		assert(a.get(2) == 666);
		assert(a.get(512) == 0);

		int here = 0;
	}

	{
		IntArray a(8);
		for(int i = 0; i < 8;++i)
			a.set(i, i*i);
		a.insertOrderInferior( 8 ); // order sur A par le predicat f : a[i] < a[i+1]
		int here = 0;
	}

	{
		IntArray a(0);
		a.insertOrderInferior(18); // order sur A par le predicat f : a[i] < a[i+1]
		a.insertOrderInferior(-45618); // order sur A par le predicat f : a[i] < a[i+1]
		a.insertOrderInferior(81456); // order sur A par le predicat f : a[i] < a[i+1]
		a.insertOrderInferior(358); // order sur A par le predicat f : a[i] < a[i+1]
		a.insertOrderInferior(18); // order sur A par le predicat f : a[i] < a[i+1]
		a.insertOrderInferior(-18); // order sur A par le predicat f : a[i] < a[i+1]
		a.insertOrderInferior(8); // order sur A par le predicat f : a[i] < a[i+1]
		assert(a.isSorted());
		int here = 0;
	}

	{
		IntArray a(5);
		a.set(0,18); // order sur A par le predicat f : a[i] < a[i+1]
		a.set(1,-45618); // order sur A par le predicat f : a[i] < a[i+1]
		a.set(2,81456); // order sur A par le predicat f : a[i] < a[i+1]
		a.set(3,358); // order sur A par le predicat f : a[i] < a[i+1]
		a.set(4,18); // order sur A par le predicat f : a[i] < a[i+1]
		a.sort();
		assert(a.isSorted());
		int here = 0;
	}

	{
		IntArray a(5);
		for (int i = 0; i < 5; ++i) {
			a.set(i, i * i);
			printf("%d ", a.get(i));
		}
		printf("\n");
		int here = 0;
		printf("%d\n", a.searchOrderInferior(-1));
		printf("%d\n", a.searchOrderInferior(8));
		printf("%d\n", a.searchOrderInferior(22));
	}
	{
		IntArray a(5);
		for (int i = 0; i < 5; ++i) {
			a.set(i, i * i);
			printf("%d ", a.get(i));
		}

		a.shiftRight(4);
		printf("%d\n", a.searchOrderInferior(22));
	}

	int here = 0;
}

/**
 * ['s'][][][][][0] <- fin de chaine de caracter
 * \0 ~= '0'
 * 0
 * char => int sur 8 bit
 * 
 */
int Strlen(const char* str){
	int idx = 0;
	while (str[idx] != 0)
		idx++;
	return idx;
}

int Strlen2(const char* str) {
	const char* start = str;
	while (*str != 0)
		str++;
	return str - start;
}

int Strlen3(const char* str) {
	const char* start = str;
	while(*str) str++;
	return str - start;
}

int Countc(const char* str, char c){
	int cnt = 0;
	while (*str) {
		if (*str == c)
			cnt++;
		str++;
	}
	return cnt;
}


void Strcpy(char*dst, const char*src){
	while(*src){
		*dst = *src;
		dst++;
		src++;
	}
}

void Strcpy2(char* dst, const char* src) {
	int idx = 0;
	while(src[idx]) {
		dst[idx] = src[idx];
		idx++;
	}
}

void Strcpy3(char* dst, const char* src) {
	int len = Strlen(src);
	for(int i = 0; i < len; i++)
		dst[i] = src[i];
}
/*
void Strncpy(char*, const char*, int nchars){

}*/

int main()
{
	testVec4();
	testArray();

	{
		char str[] = "sapin";
		char str2[] = "sapinatator";
		int len = Strlen(str);
		int len2 = Strlen2(str);
		int len3 = Strlen3(str);
		int cnt0 = Countc(str,'a');
		int cnt1 = Countc(str2,'a');

		char str256[256] = {};
		Strcpy3(str256, str);
		int here = 0;
	}

}
