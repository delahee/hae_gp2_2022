#pragma once

struct EntryInt{
	int			value = 0;

	EntryInt*	prev = nullptr;
	EntryInt*	next = nullptr;
};

class LinkedListInt{
public:
	EntryInt*	root = nullptr;

	void		insert(int val);
	void		remove(int val);
	void		print();// prints the list with printf
};