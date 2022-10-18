#pragma once
#include <string>

class StringTree {
public:
	std::string	value;
	
	StringTree*	left = nullptr;
	StringTree*	right = nullptr;
	
	StringTree*	insert(std::string &val);
	StringTree*	remove(std::string &val);
	void		print();
	StringTree* searchString(std::string& val);
	StringTree* searchPattern(std::string& val);
};

class StringTreeController{
public:
	StringTree* root = nullptr;
	
	void insert(std::string &val) {
		if( !root){
			root = new StringTree();
			root->value = val;
		}
		else 
			root = root->insert(val);
	};
	void remove(std::string &val) {
		root = root->remove(val);
	};
	void print();

	StringTree* searchString(std::string& val);
	StringTree* searchPattern(std::string& val);
	
};