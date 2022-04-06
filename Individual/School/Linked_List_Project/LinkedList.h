#pragma once
#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class LinkedList
{

public://Declare shit
	struct Node {
		T data;
		Node* next;
		Node* prev;
		Node() {
			prev = nullptr;
			next = nullptr;
		}
		Node(const T& data) {
			next = nullptr;
			prev = nullptr;
			this->data = data;
		}
		Node(const Node* node) {
			next = node->next;
			prev = node->prev;
			data = node->data;
		}
		void setLast(Node* node) {
			prev = node;
		}
		void setNext(Node* node) {
			next = node;
		}
	};
private:
	Node* _tail = nullptr;
	Node* _head = nullptr;
	unsigned int _size = 0;
public:
	~LinkedList() {
		Clear();
	}
		//Define shit
		//operators
	const T& operator[](unsigned int index) const {
		Node* pointer = _head;
		if (index >= _size) {
			throw out_of_range("");
		}
		for (unsigned int i = 0; i < index; i++) {
			pointer = pointer->next;
		}
		return pointer->data;
	}
	T& operator[](unsigned int index){
		Node* pointer = _head;
		if (index >= _size) {
			throw out_of_range("");
		}
		for (unsigned int i = 0; i < index; i++) {
			pointer = pointer->next;
		}
		return pointer->data;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		Clear();
		Copy(rhs);
		return *this;
	}
	bool operator ==(const LinkedList<T>& rhs) {
		if (_size != rhs._size) {
			return false;
		}
		Node* pointer = _head;
		for (unsigned int i = 0; i < _size; i++) {
			if (pointer->data != rhs[i]) {
				return false;
			}
			pointer = pointer->next;
		}
		return true;
	}

	
		//Constructors
	LinkedList() {
		_tail = nullptr;
		_head = nullptr;
		_size = 0;
	}
	void Copy(const LinkedList<T>& list) {
		Node* pointer = list._head;
		while (pointer != nullptr) {
			AddTail(pointer->data);
			pointer = pointer->next;

		}
	}
	LinkedList(const LinkedList<T>& list) {
		Copy(list);
	}
		//insertion :o
	void AddHead(const T& data) {
		Node* temp = new Node(data);
		if (_head != nullptr) {
			_head->prev = temp;
			temp->setNext(_head);
		}
		temp->next = _head;
		_head = temp;
		_size++;
		if (_size == 1) {
			_tail = _head;
		}
	}
	void AddTail(const T& data) {
		Node* temp = new Node(data);
		if (_tail != nullptr) {
			_tail->next = temp;
			temp->setLast(_tail);
		}
		temp->prev = _tail;
		_tail = temp;
		_size++;
		if (_size == 1) {
			_head = _tail;
		}
	}
	void AddNodesHead(const T* data, unsigned int count) {
		for (unsigned int i = 0; i<count ; i++){
			AddHead(data[count - 1 - i]);
		}
	}
	void AddNodesTail(const T* data, unsigned int count) {
		for (unsigned int i = 0; i < count; i++) {
			AddTail(data[i]);
		}
	}
	void InsertAfter(Node* node, const T& data) {
		_size++;
		Node* temp = new Node(data);
		temp->next = node->next;
		
		if (node->next != nullptr) {
			node->next->prev = temp;
		}
		node->next = temp;
		temp->prev = node;
	}
	void InsertBefore(Node* node, const T& data) {
		_size++;
		Node* temp = new Node(data);
		temp->prev = node->prev;
		if (node->prev != nullptr) {
			node->prev->next = temp;
		}
		node->prev = temp;
		temp->next = node;
	}
	void InsertAt(const T& data, unsigned int index) {
		if (index == 0) {
			AddHead(data);
		}
		else {
			Node* pointer = GetNode(index-1);
			InsertAfter(pointer, data);
		}
	}
	
		//Getters
	unsigned int NodeCount() const {
		return _size;
	}
	void FindAll(vector<Node*>& outData, const T& value) const{
		Node* pointer = _head;
		for (unsigned int i = 0; i < _size; i++) {
			if (pointer != nullptr) {
				if (pointer->data == value) {
					outData.push_back(pointer);
				}
				pointer = pointer->next;
			}
		}
	}
	Node* Find(const T& data) {
		Node* pointer = _head;
		for (unsigned int i = 0; i < _size; i++) {
			if (pointer != nullptr) {
				if (pointer->data == data) {
					return pointer;
				}
				pointer = pointer->next;
			}
		}
		return nullptr;
	}
	const Node* Find(const T& data) const {
		Node* pointer = _head;
		for (unsigned int i = 0; i < _size; i++) {
			if (pointer != nullptr) {
				if (pointer->data == data) {
					return pointer;
				}
				pointer = pointer->next;
			}
		}
		return nullptr;
	}
	Node* GetNode(unsigned int index) {
		if (index >= _size) {
			throw out_of_range("");
		}
		Node* pointer = _head;
		for (unsigned int i = 0; i < index; i++) {
			pointer = pointer->next;
		}
		return pointer;
	}
	const Node* GetNode(unsigned int index) const {
		if (index >= _size) {
			throw out_of_range("");
		}
		Node* pointer = _head;
		for (unsigned int i = 0; i < index; i++) {
			pointer = pointer->next;
		}
		return pointer;
	}
	Node* Head() {
		return _head;
	}
	const Node* Head() const {
		return _head;
	}
	Node* Tail() {
		return _tail;
	}
	const Node* Tail() const {
		return _tail;
	}
	
		//output
	void PrintForward() const {
		Node* pointer = _head;
		while (pointer != nullptr) {
			cout << pointer->data << endl;
			pointer = pointer->next;
		}
	}
	void PrintReverse() const {
		Node* pointer = _tail;
		while (pointer != nullptr) {
			cout << pointer->data << endl;
			pointer = pointer->prev;
		}
	}
	void PrintForwardRecursive(const Node* node) const {
		if (node == nullptr) {
			return;
		}
		cout << node->data << endl;
		PrintForwardRecursive(node->next);
		
	}
	void PrintReverseRecursive(const Node* node) const {
		if (node == nullptr) {
			return;
		}
		cout << node->data << endl;
		PrintReverseRecursive(node->prev);


	}
		//removal
	bool RemoveHead() {
		if (_head == nullptr) {
			return false;
		}
		if (_size == 0) {
			return false;
		}
		if (_size == 1) {
			delete _head;
			_head = nullptr;
			_tail = nullptr;
			_size = 0;
			return true;
		}
		Node* temp = _head;
		_head = _head->next;
		if (temp != nullptr) {
			delete temp;
		}
		if (_head != nullptr) {
			_head->prev = nullptr;
		}
		_size--;
		return true;
	}
	bool RemoveTail() {
		if (_tail == nullptr) {
			return false;
		}
		if (_size == 0) {
			return false;
		}
		if (_size == 1) {
			delete _head;
			_head = nullptr;
			_tail = nullptr;
			_size = 0;
			return true;
		}
		Node* temp = _tail;
		_tail = _tail->prev;
		if (temp != nullptr) {
			delete temp;
		}
		if (_tail != nullptr) {
			_tail->next = nullptr;
		}
		_size--;
		return true;
	}
	void Clear() {
		Node* pointer = _head;
		Node* temp = pointer;
		while (pointer != nullptr) {
			pointer = pointer->next;
			if (temp != nullptr) {
				delete temp;
			}
			temp = pointer;
		}
		_size = 0;
		_head = nullptr;
		_tail = nullptr;
	}
	bool RemoveAt(unsigned int index) {
		if (index > _size) {
			return false;
		}
		Node* pointer = GetNode(index);
		if (pointer == nullptr) {
			return false;
		}
		//make temp's neighbors see each other
		if (pointer->next != nullptr) {
			pointer->next->prev = pointer->prev;
		}
		if (pointer->prev != nullptr) {
			pointer->prev->next = pointer->next;
		}
		delete pointer;
		_size--;
		return true;
	}
	unsigned int Remove(const T& data) {
		unsigned int count = 0;
		Node* pointer = Find(data);
		while (pointer != nullptr) {
			//make pointer's neighbors see each other
			if (pointer->next != nullptr) {
				pointer->next->prev = pointer->prev;
			}
			if (pointer->prev != nullptr) {
				pointer->prev->next = pointer->next;
			}
			delete pointer;
			_size--;
			pointer = Find(data);
			count++;
		}
		return count;
	}

	
};

