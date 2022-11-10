#pragma once

template<typename Type>
class BinaryTree{
public:
	Type		key;
	BinaryTree* left = nullptr;
	BinaryTree* right = nullptr;

	BinaryTree( Type val){
		key = val;
	}

	void print();
	
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

	void print(){
		if (trunk) {
			trunk->print();
		}
		else
			std::cout << " [] ";
	}
};