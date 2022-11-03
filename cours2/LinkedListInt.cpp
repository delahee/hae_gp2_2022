#include "LinkedListInt.hpp"
#include <cstdio>

void LinkedListInt::insert(int val){
	//create en entryInt for the value
	EntryInt* nuVal = new EntryInt;
	nuVal->value = val;
	// else install the the root
	if(!root){
		root = nuVal;
	}
	//if there is a root link the root
	else{
		auto oldRoot = root;
		root = nuVal;
		oldRoot->prev = root;
		root->next = oldRoot;
	}
}

void LinkedListInt::remove(int val){
	auto cur = root;
	while (cur) {
		auto prev = cur->prev;
		auto next = cur->next;
		if( cur->value == val){
			if (prev) prev->next = next;
			if (next) next->prev = prev;
			if (root == cur)
				root = next;
			delete cur;
			cur = nullptr;
		}
		cur = next;
	}
}

void LinkedListInt::print(){
	printf("[");
	auto cur = root;
	while (cur) {
		printf("%d", cur->value);
		cur = cur->next;
		if (cur) printf(" ");
	}
	printf("]\n");
}
