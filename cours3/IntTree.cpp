#include "IntTree.hpp"
#include <stdio.h>
#include <iostream>

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
	if( val == value ){
		auto oldLeft = left;
		auto oldRight = right;

		if( !oldRight && !oldLeft){
			delete this;
			return nullptr;
		}
		else if( !oldRight){
			delete this;
			return oldLeft;
		} 
		else if (!oldLeft) {
			delete this;
			return oldRight;
		}
		while( left ){
			auto lval = left->value;
			left = left->remove(lval);
			right->insert(lval);
		}
		return right;
	}
	if (left && (val <= value)) left = left->remove(val);
	if (right && (val >= value)) right = right->remove(val);
	return this;
}

void IntTree::print(){
	if (left)
		left->print();
	printf("%d ",value);
	if (right)
		right->print();
}

void IntTreeController::print() {
	if (root) {
		root->print();
		std::cout << "\n";
	}
	else
		std::cout << "[]\n";
}
