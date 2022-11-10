#pragma once

#include <string>

template<typename Type>
class BinaryTree{
public:
	Type		key = {};
	BinaryTree* left = nullptr;
	BinaryTree* right = nullptr;

	BinaryTree( Type val){
		key = val;
	}

	void print();

	int size() {
		int sz = 1;
		if (left)
			sz += left->size();
		if (right)
			sz += right->size();
		return sz;
	};
	
	BinaryTree* remove(Type val) {
		auto tLeft = left;
		auto tRight = right;
		if(key == val){
			delete this;
			if (!tLeft && !tRight)
				return nullptr;
			else if (!tLeft)
				return tRight;
			else if(!tRight)
				return tLeft;
			else {
				while(tLeft){
					auto tKey = tLeft->key;
					tRight = tRight->insert(tKey);
					tLeft = tLeft->remove(tKey);
				}
				return tRight;
			}
		}
		else {
			if (val < key) {
				if (left)
					left = left->remove(val);
			}
			else {
				if (right)
					right = right->remove(val);
			}
			return this;
		}
	};

	BinaryTree* search(Type val) {
		if( val == key ){
			return this;
		}
		else if( val < key){
			if (!left)
				return nullptr;
			else
				return left->search(val);
		}
		else {
			if (!right)
				return nullptr;
			else
				return right->search(val);
		}
	};

	BinaryTree* insert(Type val) {
		if( val < key ){
			if( left )
				left = left->insert(val);
			else
				left = new BinaryTree(val);
		}
		else{
			if (right) 
				right = right->insert(val);
			else 
				right = new BinaryTree(val);
		}
		return this;
	};
};

template<>
void BinaryTree<std::string>::print() {
	if (left)
		left->print();
	std::cout << key << " ";
	if (right)
		right->print();
};

template<typename Type>
void BinaryTree<Type>::print() {
	if (left)
		left->print();
	std::cout << std::to_string(key) << " ";
	if (right)
		right->print();
};

template<typename Type>
class BinaryTreeController{
public:
	BinaryTree<Type>*	trunk = nullptr;
	BinaryTreeController() {

	};

	void insert(Type key) {
		if (trunk) {
			trunk->insert(key);
		}
		else
			trunk = new BinaryTree<Type>(key);
	};

	int size() {
		if (!trunk) return 0;
		else return trunk->size();
	};

	void print(){
		if (trunk) {
			trunk->print();
		}
		else
			std::cout << " [] ";
	}

	void remove(Type val) {
		if (!trunk)
			return;
		else
			trunk = trunk->remove(val);
	}
	
	BinaryTree<Type>* search(Type val) {
		if (!trunk)
			return {};
		else
			trunk = trunk->search(val);
	};
};