#include "IntTree.hpp"
#include <stdio.h>

IntTree* IntTree::insert(int val){
	if (val < value){
		//insert to left
		if (left) 
			left = left->insert(val);
		else {
			left = new IntTree();
			left->value = val;
		}
	}
	else {
		//insert to right
		if (right)
			right = right->insert(val);
		else {
			right = new IntTree();
			right->value = val;
		}
	}
	return this;
}

IntTree* IntTree::remove(int val){
	return nullptr;
}

void IntTree::print(){
	if (left)
		left->print();
	printf("%d ",value);
	if (right)
		right->print();
}
