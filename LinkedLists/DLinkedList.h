#pragma once

//forward declaration for the Linked List Iterator
template <class T>
class IteratorDLL;


// Node class
// A node store a value and a pointer to the next node
template <class T>
class NodeC {
	T e;
	NodeC* next;
	NodeC* prev;
public:
	//constuctor that create an empty node
	NodeC() : e{ T{} }, next{ nullptr }, prev{ nullptr } {}
	//constructor that create a node with a specific value
	NodeC(T e) :e{ e }, next{ nullptr }, prev{ nullptr } {}

	//copy constructor
	NodeC(NodeC& n) {
		e = n.e;
		next = n.next;
		prev = n.prev;
	}

	//copy assignment operator
	NodeC& operator=(NodeC& n) {
		e = n.e;
		next = n.next;
		prev = n.prev;
		return *this;
	}

	//move constructor
	NodeC(NodeC&& n) {
		e = n.e;
		next = n.next;
		prev = n.prev;
	}

	//move assignment operator
	NodeC& operator=(NodeC&& n) {
		e = n.e;
		next = n.next;
		prev = n.prev;
		return *this;
	}

	//setting the next node 
	void setNext(NodeC<T>* n) {
		next = n;
	}

	//setting the previous node
	void setPrev(NodeC<T>* n) {
		prev = n;
	}

	//returning a pointer to the next node
	NodeC<T>* getNext() {
		return next;
	}

	//returning a pointer to the previous node
	NodeC<T>* getPrev() {
		return prev;
	}

	//returning the value from the node
	T elem() {
		return e;
	}

	//setting the value for the node
	void setElem(T e) {
		this->e = e;
	}
};

//Linked List class
//The linked List containts a pointer to the first element and an integer to store the size of the list
template <class T>
class DLinkedList
{
	NodeC<T>* first;
	NodeC<T>* last;
	int nr;
public:
	//constructor for an empty list
	DLinkedList();
	//constructor that create a list with one element 
	DLinkedList(T e);
	//copy constructor
	DLinkedList(DLinkedList & ot);
	//copy assignment operator
	DLinkedList& operator=(DLinkedList& ot);
	//move constructor
	DLinkedList(DLinkedList && ot);
	//move constructor operator
	DLinkedList& operator=(DLinkedList&& ot);

	//return size of the list
	int size() { return nr; }

	//add a new node with value e at the "pos" position
	void addPos(T e, int pos);

	//add a new node with value e at the end of the list
	void add(T e);

	//add a new node with value e at the begining of the list
	void addFront(T e);

	//update an element from the P position in list , the new value for the node will be e
	void update(int poz, T e);

	//remove an element from a position(index)
	T remove(int poz);

	//acessing an element at a position
	T operator [](int pos);

	//find an element and return a the position of the node or -1 if the element is not in the list
	int find(T e, bool(*eq)(T e1, T e2) = [](T e1, T e2) {return e1 == e2; });

	//return an iterator at the start of the list
	IteratorDLL<T> begin();

	//return an iterator after the last element of the list
	IteratorDLL<T> end();

	//destructor
	virtual ~DLinkedList();

};

//the iterator class
// li is a reference to the Linked list
// current is a pointer to the curent node 
template <class T>
class IteratorDLL {
	DLinkedList<T>& li;
	NodeC<T>* current;
public:
	//the constructor for iterator
	IteratorDLL(DLinkedList<T>& li, NodeC<T>* current) :li{ li }, current{ current } {}

	//not equal operator
	// two iterators are not equal when the current variable differ 
	bool operator!=(IteratorDLL<T> ot) {
		return ot.current != current;
	}

	//the operator that return the value of the curent node
	T operator*() {
		return current->elem();
	}

	//the increment operator , set the curent variabile to point to the next node in thelist
	void operator++() {
		current = current->getNext();
	}
};
//constructor for a linked list (no elements in list)
template<class T>
DLinkedList<T>::DLinkedList() {
	last = nullptr;
	first = nullptr;
	nr = 0;
}
//constructor for a linked list ( that set the first node with element e )
template<class T>
DLinkedList<T>::DLinkedList(T e) {
	first = new NodeC<T>(e);
	last = first;
	nr = 1;
}
//returning the element at the pos position
//if the position is invalid then return the zero/null value
//c - the current node pointer, used to reach position pos
template<class T>
T DLinkedList<T>::operator[](int pos) {
	if (pos < 0 || pos >= nr) {
		return T{};
	}
	if (pos == 0) {
		return first->elem();
	}
	if (pos == nr - 1) {
		return last->elem();
	}
	else {
		NodeC<T>* c = first;
		int i = 0;
		if (pos <= nr / 2) {
			while (i != pos) {
				c = c->getNext();
				i++;
			}
		}
		else {
			c = last;
			i = nr - 1;
			while (i != pos) {
				c = c->getprev();
				i--;
			}
		}
		return c.elem();
	}
}


/* finding the postion of the node vith value el
 * if the element is not in the list the function returns -1
 * el - the search element
 * eq - a function that defines the equality between 2 values from nodes
 *      the default is simple equality
 *      can be canged in case of pair or other types of value that requires other types of equality
 * c  - the curent node pointer , used to reach the node with value el
 */
template<class T>
int DLinkedList<T>::find(T el, bool(*eq)(T e1, T e2)) {
	NodeC<T>* c = first;
	int i = 0;
	while (c != nullptr && !(eq(c->elem(), el))) {
		c = c->getNext();
		i++;
		//just to be safe
		if (c == nullptr) {
			return -1;
		}
	}
	if (eq(c->elem(), el)) {
		return i;
	}
	else
		return -1;
}

/* updating the value of the node at the pos position , the new value will be 3
 * if the position is after the middle then reach pos from the end otherwise reach pos from begin
 * c - the curent node pointer , used to reach the pos position
 * i - a counter
 */
template<class T>
void DLinkedList<T>::update(int pos, T e) {
	int i = 0;
	NodeC<T>* c =first;
	if (pos <= nr / 2) {
		while (i < pos) {
			c = c->getNext();
			i++;
		}
		c->setElem(e);
	}
	else {
		c = last;
		i = nr - 1;
		while (i > pos) {
			c = c->getPrev();
			i--;
		}
		c->setElem(e);
	}
}

/* adding a new node with value e at the pos position
 *	if the position is invalid the function simply returns
 *	c  - the curent node pointer , used to reach the pos position
 *  n  - the new node
 */
template<class T>
void DLinkedList<T>::addPos(T el, int pos) {

	//if the position is 0 then is a simple add at the begining
	if (pos == 0) {
		addFront(el);
		return;
	}
	//if the position is at the end of the list is a simple add
	if (pos == nr) {
		add(el);
		return;
	}
	// if the position is invalid then do nothing
	if (pos < 0 || pos >nr) {
		return;
	}
	NodeC<T>* n = new NodeC<T>(el);
	int i = 0;
	NodeC<T>* c = first;
	
	if (pos <= nr / 2) {
		while (i < pos) {
			c = c->getNext();
			i++;
		}
	}
	else {
		c = last;
		i = nr - 1;
		while (i > pos) {
			c = c->getPrev();
			i--;
		}
	}
	NodeC<T>* ant = c->getPrev();
	n->setPrev(ant);
	ant->setNext(n);
	n->setNext(c);
	c->setPrev(n);

}

/* adding a new node with value e at the begining of the list
*  n  - the new node
*/
template<class T>
void DLinkedList<T>::addFront(T el) {
	NodeC<T>* n = new NodeC<T>(el);
	first->setPrev(n);
	n->setNext(first);
	first = n;
	nr++;
}

/* adding a new node with value e at the pos position
*	c  - the curent node pointer , used to reach the last node
*   n  - the new node
*/
template<class T>
void DLinkedList<T>::add(T e) {
	NodeC<T>* n = new NodeC<T>(e);
	//if the element to be add is the first in the list , then set the first to point to the new node
	if (first == nullptr) {
		first = n;
		last = first;
	}
	else {
		last->setNext(n);
		n->setPrev(last);
		last = n;
	}
	nr++;
}

/* removing an element at the poz position
 * if the position is invalid then return  null/zero value
 * c  - the curent node pointer , used to reach the pos position
 */
template<class T>
T DLinkedList<T>::remove(int poz) {
	//invalid index
	if (poz >= nr || poz < 0) {
		return T{};
	}
	T el;
	int i = 0;
	NodeC<T>* c = first;
	if (poz <= nr / 2) {
		while (i != poz) {
			c = c->getNext();
			i++;
		}
	}
	else {
		c = last;
		i = nr - 1;
		while (i != poz) {
			c = c->getPrev();
			i--;
		}
	}
	
	NodeC<T>* ant = c->getPrev();

	if (poz == 0) {
		first->getNext()->setPrev(nullptr);
		first = first->getNext();
	}
	else if (poz == nr - 1) {
		ant->setNext(nullptr);
		last = ant;
	}
	else {
		ant->setNext(c->getNext());
		c->getNext()->setPrev(ant);
	}
	el = c->elem();
	delete c;

	nr--;
	return el;
}

/* The copy constructor
 * c  - the curent node pointer , used to move to all elements from the list
 * first is added by creating a new node and the other are simply added with add method
 */
template<class T>
DLinkedList<T>::DLinkedList(DLinkedList & ot) {
	NodeC<T>* c = ot.first;
	first = new NodeC<T>(c->elem());
	last = first;
	while (c->getNext() != nullptr) {
		c = c->getNext();
		add(c->elem());
	}
}

/* The copy assignment operator
 * c  - the curent node pointer , used to move to all elements from the list
 * first is added by creating a new node and the other are simply added with add method
 */
template<class T>
DLinkedList<T>& DLinkedList<T>::operator=(DLinkedList& ot) {
	NodeC<T>* c = ot.first;
	first = new NodeC<T>(c->elem());
	last = first;
	while (c->getNext() != nullptr) {
		c = c->getNext();
		add(c->elem());
	}
	return *this;
}

/* The move constructor
 * c  - the curent node pointer , used to move to all elements from the list
 * first is added by creating a new node and the other are simply added with add method
 */
template<class T>
DLinkedList<T>::DLinkedList(DLinkedList && ot) {
	NodeC<T>* c = ot.first;
	first = new NodeC<T>(c->elem());
	last = first;
	while (c->getNext() != nullptr) {
		c = c->getNext();
		add(c->elem());
	}
}

/* The move assignment operator
 * c  - the curent node pointer , used to move to all elements from the list
 * first is added by creating a new node and the other are simply added with add method
 */
template<class T>
DLinkedList<T>& DLinkedList<T>::operator=(DLinkedList&& ot) {
	NodeC<T>* c = ot.first;
	first = new NodeC<T>(c->elem());
	last = first;
	while (c->getNext() != nullptr) {
		c = c->getNext();
		add(c->elem());
	}
	return *this;
}

//returning an iterator at the first element of the list
template<class T>
IteratorDLL<T> DLinkedList<T>::begin() {
	return IteratorDLL<T>(*this, first);
}


//returning an iterator after the last element of the list
template<class T>
IteratorDLL<T> DLinkedList<T>::end() {
	return IteratorDLL<T>(*this, nullptr);
}

/* The desctructor is recursively
 * deleting the first element , setting first to point to the second element , and call the destructor
 * the condition to stop is if the first is null pointer
 */
template<class T>
DLinkedList<T>::~DLinkedList() {
	while (first != nullptr) {
		auto x = first->getNext();
		delete first;
		first = x;
	}
}
