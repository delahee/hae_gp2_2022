


template< typename T>
struct Node{
	T			key = {};
	Node*		next = nullptr;

	Node(T val) {
		key = val;
	};

	Node<T> * removeAll(T val) {
		if (val == key) {
			Node<T>* chain = next;
			delete this;
			return chain->removeAll(val);
		}
		else {
			if (next)
				next = next->removeAll(val);
		}
		return this;
	}; 
	
	Node<T>* removeOne(T val) {
		if (val == key) {
			Node<T>* chain = next;
			delete this;
			return chain;
		}
		else {
			if (next)
				next = next->removeOne(val);
		}
		return this;
	};
};

template< typename T>
class LinkedList{
public:
	Node<T> *	head = nullptr;

	void push_front(T val) {
		if (!head){
			head = new Node<T>(val);
			return;
		}
		auto nuHead = new Node<T>(val);
		nuHead->next = head;
		head = nuHead;
	};

	void removeAll(T val) {
		if (!head)
			return;

		head = head->removeAll(val);
	}; 
	
	void removeOne(T val) {
		if (!head)
			return;

		head = head->removeOne(val);
	};

	void print() {
		std::cout << ("[");
		auto cur = head;
		while (cur) {
			std::cout << std::to_string( cur->key );
			cur = cur->next;
			if (cur) std::cout << (" ");
		}
		std::cout << ("]\n");
	};
};

typedef LinkedList<int> IntList;
typedef LinkedList<float> FloatList;