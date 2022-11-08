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
#include "StringTree.hpp"
#include "FloatArray.hpp"

#include "Lib.hpp"
#include "Int64Array.hpp"

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

	cout << "*************\n";
	IntTreeController rm;
	rm.insert(2);
	rm.print();
	rm.remove(2); rm.print();

	rm.insert(2);
	rm.insert(3);
	rm.insert(4);

	rm.print();

	rm.remove(2); rm.print();
	rm.remove(3); rm.print();
	rm.remove(4); rm.print();

	cout << "*************\n";
	IntTreeController rm1;

	clock_t now = clock();
	srand(now);
	std::vector<int> data;
	for(int i = 0; i < 10;++i){
		data.push_back(rand() % 20 - 10);
	}
	rm1.print();
	for( auto v : data){
		rm1.insert(v);
	}
	rm1.print();
	for (auto v : data) {
		cout <<" removing "<< std::to_string(v)<<"\n";
		rm1.remove(v);
		rm1.print();
	}
	rm1.print();
}

void testStr(){
	char str[] = "sapin";//local => existe plus du tout a la fin de fonction
	//char* str = malloc();//global => existe tjrs a la fin de fonction
	char str2[] = "sapinatator";
	int len = Strlen(str);
	int len2 = Strlen2(str);
	int len3 = Strlen3(str);
	int cnt0 = Countc(str, 'a');
	int cnt1 = Countc(str2, 'a');

	char str256[256] = {};
	Strcpy3(str256, str);
	int here = 0;
}

void testC(){
	//creer un tableau de 150 éléments
	int tata[150] = {};
	//int* toto = new int[150];
	//int* tata = (int*) malloc(150 * sizeof(int));
	//new int[150] = > 
	//	new ((int*)malloc(150 * sizeof(int))) (int) (150);
	// le remplir des carré successif

	for (int i = 0; i < 150; ++i)
		tata[i] = i * i;
	//?

	//l'afficher a l'envers
	//delete[] toto;
	for (int i = 0; i < 150; ++i)
		printf("%d ", tata[i]);
	printf("\n");

	//stack pointer => pointeur sur le debut de la memoire locale
	//program pointer
	{
		int o = 0;//sp+=4; [sp] = 0;
		int* sapin = (int*)malloc(8); //sp+=sizeof(int*); [sp] = [malloc(8)]
	}

	{
		//int a = o;
	}

}

void testFloatArray(){
	FloatArray arr(16);
	arr.push_back(16);
	arr.push_back(15);
	arr.resize(150);
	arr.print();

	cout << "*****";

	FloatArray arr1;
	arr1.push_back(3);
	arr1.push_back(4);
	arr1.push_back(5);
	arr1.print();

	cout << "*****";
	FloatArray arr2;
	arr2.push_first(1);
	arr2.push_first(2);
	arr2.push_first(3);
	arr2.print();
	cout << "*****";

	//std::function<void(float val)> = ...
	auto maFonction = [](float val){
		//printf("%f ", val);
		cout << std::to_string(val) << " ";
	};
	arr2.iter(maFonction);
	//3 2 1 ?

	printf("\n***SUM***");
	float totalSum = 0;
	auto sumFunction = [&totalSum](float val) {
		//calculer la somme total
		totalSum += val;
	};
	arr2.iter(sumFunction);
	//afficher la somme total

	std::cout << std::to_string(totalSum);

	printf("\n***\n");
	float abc[3] = { 66,67,68.5 };
	FloatArray toto = FloatArray::fromArray(abc, 3);
	toto.print();

	FloatArray tata = toto; //?
}	

void testLib(){
	char sapin[6] = "sapin";
	char buffer[512] = {};
	Lib::Memcpy(buffer, sapin, 6);
	int here = 0;
}

void testStringTree() {

	char msg[] = "mais ou est donc or ni car";

	const char* findO = Lib::StrChr(msg, 'o');

	cout << findO << " ?";

	StringTreeController stc;
	std::string t0("toto");
	std::string t1("tata");
	std::string t2("TAta");
	std::string t3("taktak");

	stc.insert(t0);
	stc.insert(t1);
	stc.insert(t2);
	stc.insert(t3);
	stc.print();

	std::string tu("tata");

	auto res = stc.searchString(tu);

	if (res)
		res->print();
	else
		printf("not found!");

	assert(Lib::StrPrefix("pin", "sapin") == false);
	assert(Lib::StrPrefix("sapin", "sa") == true);
	auto s = Lib::StrStr("sapin", "pin");
	assert(strcmp("pin", s) == 0);

	int tabSrc[] = { 0,1,2,3,4,0,1,2,3,4 };
	int tabDst[256] = { };
	Lib::MemcpyRec((char*)tabDst, (char*)tabSrc, sizeof(tabSrc));
	int here = 0;


	const char lapin[] = "lapin";
	const char carotte[]="carotte";

	char dst[256] = "lapinlapin";

	assert(Lib::StrChrRec(lapin, 'n'));
	assert(Lib::StrChrRec(lapin, 'i'));
	assert(Lib::StrChrRec(lapin, 'l'));
	assert(! Lib::StrChrRec(lapin, 'z'));

	assert( Lib::StrStrRec(lapin,"la"));
	assert( Lib::StrStrRec(lapin,"pin"));
	assert(! Lib::StrStrRec(lapin,"toto"));
	assert(Lib::StrStrRec("",""));
	assert(!Lib::StrStrRec("","sapin"));
	assert(9 == Lib::StrLenRec("sapinator"));
	assert(0 == Lib::StrLenRec(""));


	Lib::StrCpy(dst, "toto");
	assert(Lib::StrLenRec(dst) == 4);
	assert(Lib::StrCmp("a","b") == -1);
	assert(Lib::StrCmp("c","b") == 1);
	assert(Lib::StrCmp("b","b") == 0);
	assert(Lib::StrCmp("","") == 0);
	assert(Lib::StrCmp("","a") == -1);
	printf("\n========== OK============\n");
}

void testArith(){
	assert( 9 == Lib::add(-1,10));
	assert( 4 == Lib::add(2,2));
	assert( -11 == Lib::sub(-1,10));
	assert( 4 == Lib::mul(2,2));
	assert( -4 == Lib::mul(2,-2));
	assert( -4 == Lib::mul(-2,2));
	assert( 4 == Lib::mul(-2,-2));
	assert( 0 == Lib::mul(0,-2));
	assert( 1 == Lib::mul(1,1));
	assert( 81 == Lib::mul(9,9));

	assert( 0 == Lib::div(3,9));
	assert( 3 == Lib::div(3,1));
	assert( 4 == Lib::div(16,4));
	assert( 3 == Lib::div(15,4));
	assert( -3 == Lib::div(-15,4));
	assert( -3 == Lib::div(15,-4));
	assert( 3 == Lib::div(-15,-4));
	assert( 1 == Lib::div(6,4));


	assert( 24 == Lib::mulTerminalRecursion(6,4));
	assert( 1 == Lib::divTR(6,4));
	assert( 3 == Lib::divTR(15,4));
	assert(3 == Lib::divTR(-15, -4));

	int there = 0;
}

void testInt64(){
	Int64Array t(2);

	t.push_back(1);
	t.push_back(2);
	t.push_back(3);
	t.push_back(4);

	t.print();
	cout <<"\n alloc size : "<< t.allocSize << "\n";

	Int64Array t1(1);
	t1.push_front(1);
	t1.push_front(2);
	t1.push_front(3);
	t1.push_front(4);
	t1.print();

	cout << "\n **** \n";


	Int64Array t2(1);
	t2.push_back(8);
	t2.push_back(8);
	t2.push_back(8);
	t2.push_back(8);

	t2.insert(2, 4);
	t2.insert(4, 3);

	cout << "searched " << t2.searchPosition(4) << endl;

	t2.print();

	cout << "\n **** \n";

	Int64Array t3(1);
	t3.fillWithRandom(16);
	t3.print();


	{
		Int64Array t4(1);
		t4.push_back(4);
		t4.push_back(5);
		t4.print();
		t4.shift_left(1, t4.size());
		t4.print();
	}

	{
		Int64Array t4(1);
		t4.push_back(3);
		t4.print();
		t4.shift_left(1, t4.size());
		t4.print();
	}

	{
		Int64Array t4(1);
		t4.push_back(3);
		t4.push_back(4);
		t4.push_back(5);
		t4.push_back(6);
		t4.print();
		t4.shift_left(0, t4.size());
		t4.print();
	}

	{
		Int64Array t5(1);
		t5.push_back(3);
		t5.push_back(4);
		t5.push_back(5);
		t5.print();
		t5.removeOne(3);
		t5.print();
	}

	{
		Int64Array t2(1);
		t2.push_back(8);
		t2.push_back(8);
		t2.push_back(8);
		t2.push_back(8);

		t2.print();
		t2.removeAll(8);
		t2.print();
	}

	cout << "\n sorting test \n";
	{
		Int64Array t2(1);
		t2.push_back(9);
		t2.push_back(66);
		t2.push_back(9);
		t2.push_back(77);
		auto other = Int64Array::sort(t2);
		t2.print();
		other->print();
	}

	cout << "\n sorting test algo \n";
	{
		Int64Array t2(1);
		t2.push_back(5);
		t2.push_back(4);
		t2.push_back(3);
		t2.push_back(2);
		t2.push_back(1);

		Int64Array::insertionSort(t2);
		t2.print();
	}
}

void testChrono() {
	auto t0 = Lib::getTimestamp();
	//for malloc(1)
	//2.5	00 000 0.31
	//5000 000 0.62

	//for sort
	//1024 0.099595s
	//2048 0.190546s
	//4096 0.280546s
	//9192 0.95000s
	Int64Array t2(1);
	t2.fillWithRandom(4096*2);
	Int64Array::insertionSort(t2);
	t2.print();

	Int64Array t3(1);
	t3.fillWithRandom(4096 * 2);
	Int64Array::stdQsort(t2);
	t3.print();

	auto t1 = Lib::getTimestamp();
	cout << to_string(t1 - t0) << "s \n";
}



int main(){
	clock_t init = clock();

	//testVec4();
	//testArray();
	//testLinkedList();
	//testTree();
	//testC();
	//testFloatArray();
	//testStringTree();
	//testLib();
	//testArith();
	//testInt64();
	testChrono();

}
