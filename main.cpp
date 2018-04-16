//
//  main.cpp
//  LinkedList
//
//  Created by Даниил Смирнов on 21.03.2018.
//  Copyright © 2018 Даниил Смирнов. All rights reserved.
//

#include <iostream>
using namespace std;

struct Node {
	int value;
	Node *next;
};

class List {
	
protected:
	int size;
	Node *root;
	Node *last;
	
	Node* lastNodePreviouslyGot;
	int lastIndexPreviouslyGot;
	bool isCached;
	
	Node* getNodeAt(int index);

public:
	
	List();
	~List();
	
	int getSize();
	
	void addToEnd(int value);
	
	void addAt(int index, int value);
	
	void setValueAt(int index, int value);
	
	int getNodeValueAt(int index);
	
	int removeAt(int index);
	
	int removeFirst();
	
	int pop();
	
	void addToStart(int value);
	
	void clear();
};

List::List() {
	
	root = NULL;
	last = NULL;
	size = 0;
	
	isCached = false;
	lastNodePreviouslyGot = NULL;
	lastIndexPreviouslyGot = 0;
}

List::~List() {
	
	Node *temp;
	
	while(root != NULL) {
		temp = root;
		root = root->next;
		delete temp;
	}
	
	isCached = false;
	last = NULL;
	size = 0;
}

int List::getSize() {
	return size;
}

int List::getNodeValueAt(int index) {
	
	Node* temp = getNodeAt(index);
	
	if (temp) {
		return temp->value;
	} else {
		cout << "Could not get node value at index - " << index << endl;
		return 0;
	}
}

Node* List::getNodeAt(int index) {
	
	int position = 0;
	Node* current = root;
	
	if(isCached && lastIndexPreviouslyGot <= index) {
		position = lastIndexPreviouslyGot;
		current = lastNodePreviouslyGot;
	}
	
	while(position < index && current) {
		current = current->next;
		position++;
	}
	
	if(position == index) {
		isCached = true;
		lastIndexPreviouslyGot = index;
		lastNodePreviouslyGot = current;
		
		return current;
	}
	
	return NULL;
}

void List::setValueAt(int index, int value) {
	
	if(index < 0 || index >= size) {
		cout << "Index out of range" << endl;
		return;
	}
	
	getNodeAt(index)->value = value;
}

void List::addToEnd(int value) {
	
	Node *temp = new Node();
	temp->value = value;
	temp->next = NULL;
	
	if (root) {
		last->next = temp;
		last = temp;
	} else {
		root = temp;
		last = temp;
	}
	size++;
	isCached = false;
}

void List::addToStart(int value) {
	
	if(size == 0) {
		addToEnd(value);
		return;
	}
	
	Node* temp = new Node();
	temp->next = root;
	temp->value = value;
	root = temp;
	
	isCached = false;
	size++;
}

void List::addAt(int index, int value) {
	
	if (index >= size) {
		addToEnd(value);
		return;
	}
	
	if (index == 0) {
		addToStart(value);
		return;
	}
	
	Node* temp = new Node();
	Node* prev = getNodeAt(index-1);
	
	temp->value = value;
	temp->next = prev->next;
	prev->next = temp;
	
	size++;
	isCached = false;
}

int List::pop() {
	
	if(size <= 0) {
		return 0;
	}
	
	isCached = false;
	
	if(size > 2) {
		
		Node* temp = getNodeAt(size - 2);
		int result = temp->next->value;
		delete(temp->next);
		temp->next = NULL;
		last = temp;
		size--;
		
		return result;
	} else {
		
		int result = root->value;
		delete(root);
		root = NULL;
		last = NULL;
		size = 0;
		
		return result;
	}
}

int List::removeFirst() {
	
	if (size <= 0) {
		cout << "Size of list less/equal zero" << endl;
		return 0;
	}
	
	if(size >= 1) {
		
		Node* next = root->next;
		int result = root->value;
		delete(root);
		root = next;
		size--;
		isCached = false;
		
		return result;
	} else {
		return pop();
	}
}

int List::removeAt(int index) {
	
	if (index < 0 || index >= size) {
		cout << "Invalid index" << endl;
		return 0;
	}
	
	if (index == 0) {
		return removeFirst();
	}
	
	if (index == size-1) {
		return pop();
	}
	
	Node* temp = getNodeAt(index - 1);
	Node* nodeToDelete = temp->next;
	int result = temp->value;
	temp->next = temp->next->next;
	delete(nodeToDelete);
	size--;
	isCached = false;
	
	return result;
}

void List::clear() {
	
	while (getSize() > 0) {
		removeFirst();
	}
}

//Нахождение суммы всех четных чисел списка;
//удаление чисел, в которых разряд сотен равен разряду единиц;

int main(int argc, const char * argv[]) {
	
	int countOfElements;
	int val;
	int i = 0;
	List list = List();
	
	cout << "Input count of items in list" << endl;
	cin >> countOfElements;
	cout << endl;
	
	while (i < countOfElements) {
		cout << "Input item" << endl;
		cin >> val;
		
		if (i == 0) {
			list.addToStart(val);
		} else {
			list.addToEnd(val);
		}
		i++;
	}

	int sumOfEvenValues = 0;
	//int rootNodeValue = list.getNodeValueAt(0);
	
	for(int j = 0; countOfElements >= j; j++) {

		int currentValue = list.getNodeValueAt(j);
		
		if( (currentValue > 999 ? currentValue % 1000 / 100 : currentValue / 100) == currentValue % 10) {
			list.removeAt(j);
		}
		
		if(currentValue % 2 == 0) {
			sumOfEvenValues += currentValue;
		}
	}
	
	for(int j = 0; list.getSize() > j; j++) {
		cout<< "Item [" << j << "] = " << list.getNodeValueAt(j) << endl;
	}

	return 0;
}

