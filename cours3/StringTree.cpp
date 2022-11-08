#include "StringTree.hpp"
#include <stdio.h>
#include <iostream>

StringTree* StringTree::insert(std::string &val){
	if (val < value){
		//insert to left
		if (left) 
			left = left->insert(val);
		else {
			left = new StringTree();
			left->value = val;
		}
	}
	else {
		//insert to right
		if (right)
			right = right->insert(val);
		else {
			right = new StringTree();
			right->value = val;
		}
	}
	return this;
}

StringTree* StringTree::remove(std::string &val){
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

void StringTree::print(){
	if (left)
		left->print();
	//printf("%s ",value.c_str());
	std::cout << value << " ";
	if (right)
		right->print();
}

void StringTreeController::print() {
	if (root) {
		root->print();
		std::cout << "\n";
	}
	else
		std::cout << "[]\n";
}

StringTree* StringTreeController::searchString(std::string& val) {
	if (root)
		return root->searchString(val);
	else
		return nullptr;
}

StringTree* StringTreeController::searchPattern(std::string& val){
	if (root)
		return root->searchPattern(val);
	else
		return nullptr;
}
StringTree* StringTree::searchString(std::string& val){
	if (val == value)
		return this;
	if(left)
	if(val<value){
		auto res = left->searchString(val);
		if (res)
			return res;
	}
	if (right)
		if (val > value) {
			auto res = right->searchString(val);
			if (res)
				return res;
		}
	return nullptr;
}

StringTree* StringTree::searchPattern(std::string& val){
	return nullptr;

}