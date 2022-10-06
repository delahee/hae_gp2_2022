// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include <string> //fichier systeme
//#include "string" // fichier du projet
#include <unordered_map>

#include "IntArray.hpp"
#include "Vec.hpp"
#include "LinkedListInt.hpp"
#include "IntTree.hpp"

using namespace std;

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

static void assert(bool test) {
	if (!test)
		throw "assert";
};

void testLinkedList(){
	{
		LinkedListInt toto;
		toto.insert(666);
		toto.insert(667);
		toto.insert(668);
		toto.print();
		toto.remove(666);
		toto.print();
		toto.remove(667);
		toto.remove(668);
		toto.print();
	}
}


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

static void testTree(){
	IntTreeController r;

	r.insert(2);
	r.insert(1);
	r.insert(13);
	r.insert(-5);

	r.print();
}

int main(){
	testVec4();
	testArray();
	testLinkedList();
	testTree();
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
