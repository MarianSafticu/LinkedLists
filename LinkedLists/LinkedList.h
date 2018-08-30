#pragma once

//forward declaration for the Linked List Iterator
template <class T>
class IteratorLL;


// Node class
// A node store a value and a pointer to the next node
template <class T>
class Node {
	T e;
	Node* next;
public:
	//constuctor that create an empty node
	Node() {
		e = T{};
		next = nullptr;
	}
	//constructor that create a node with a specific value
	Node(T e) :e{ e } { next = nullptr; }

	//copy constructor
	Node(Node& n) {
		e = n.e;
		next = n.next;
	}

	//copy assignment operator
	Node& operator=(Node& n) {
		e = n.e;
		next = n.next;
		return *this;
	}

	//move constructor
	Node(Node&& n) {
		e = n.e;
		next = n.next;
	}

	//move assignment operator
	Node& operator=(Node&& n) {
		e = n.e;
		next = n.next;
		return *this;
	}

	//setting the next node 
	void setNext(Node<T>* n) {
		next = n;
	}

	//returning a pointer to the next node
	Node<T>* getNext() {
		return next;
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
class LinkedList
{
	Node<T>* first;
	int nr;
public:
	//constructor for an empty list
	LinkedList();
	//constructor that create a list with one element 
	LinkedList(T e);
	//copy constructor
	LinkedList(LinkedList & ot);
	//copy assignment operator
	LinkedList& operator=(LinkedList& ot);
	//move constructor
	LinkedList(LinkedList && ot);
	//move constructor operator
	LinkedList& operator=(LinkedList&& ot);

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
	IteratorLL<T> begin();

	//return an iterator after the last element of the list
	IteratorLL<T> end();

	//destructor
	virtual ~LinkedList();

};

//the iterator class
// li is a reference to the Linked list
// current is a pointer to the curent node 
template <class T>
class IteratorLL {
	LinkedList<T>& li;
	Node<T>* current;
public:
	//the constructor for iterator
	IteratorLL(LinkedList<T>& li, Node<T>* current) :li{ li }, current{ current } {}

	//not equal operator
	// two iterators are not equal when the current variable differ 
	bool operator!=(IteratorLL<T> ot) {
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
LinkedList<T>::LinkedList() {
	first = nullptr;
	nr = 0;
}
//constructor for a linked list ( that set the first node with element e )
template<class T>
LinkedList<T>::LinkedList(T e) {
	first = new Node<T>(e);
	nr = 1;
}
//returning the element at the pos position
//if the position is invalid then return the zero/null value
//c - the current node pointer, used to reach position pos
template<class T>
T LinkedList<T>::operator[](int pos) {
	if (pos < 0 || pos >= nr) {
		return T{};
	}
	if (pos == 0) {
		return first->elem();
	}
	else {
		Node<T>* c = first;
		int i = 0;
		while (i != pos) {
			c = c->getNext();
			i++;
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
int LinkedList<T>::find(T el, bool(*eq)(T e1, T e2)) {
	Node<T>* c = first;
	int i = 0;
	while (c != nullptr && !(eq(c->elem(), el))) {
		c = c->getNext();
		i++;
	}
	if (eq(c->elem(), el)) {
		return i;
	}
	else
		return -1;
}

/* updating the value of the node at the pos position , the new value will be 3
 *
 * c - the curent node pointer , used to reach the pos position
 * i - a counter
 */
template<class T>
void LinkedList<T>::update(int pos, T e) {
	int i = 0;
	Node<T>* c = first;
	while (i < pos) {
		c = c->getNext();
		i++;
	}
	c->setElem(e);
}

/* adding a new node with value e at the pos position
 *	if the position is invalid the function simply returns
 *	c  - the curent node pointer , used to reach the pos position
 *	ant- a pointer to the element begin the postion that we add the node
 *	     used to connect the new node to the list
 *  n  - the new node
 */
template<class T>
void LinkedList<T>::addPos(T el, int pos) {

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
	Node<T>* n = new Node<T>(el);
	int i = 0;
	Node<T>* ant = nullptr;
	Node<T>* c = first;
	while (i != pos) {
		if (i == pos - 1) {
			ant = c;
		}
		c = c->getNext();
		i++;
	}
	if (ant != nullptr) {
		ant->setNext(n);
	}
	n->setNext(c);

}

/* adding a new node with value e at the begining of the list
*  n  - the new node
*/
template<class T>
void LinkedList<T>::addFront(T el) {
	Node<T>* n = new Node<T>(el);
	n->setNext(first);
	first = n;
	nr++;
}

/* adding a new node with value e at the pos position
*	c  - the curent node pointer , used to reach the last node
*   n  - the new node
*/
template<class T>
void LinkedList<T>::add(T e) {
	Node<T>* n = new Node<T>(e);
	//if the element to be add is the first in the list , then set the first to point to the new node
	if (first == nullptr) {
		first = n;
	}
	else {
		Node<T>* c = first;
		while (c->getNext() != nullptr) {
			c = c->getNext();
		}
		c->setNext(n);
	}
	nr++;
}

/* removing an element at the poz position
 * if the position is invalid then return  null/zero value
 * c  - the curent node pointer , used to reach the pos position
 */
template<class T>
T LinkedList<T>::remove(int poz) {
	//invalid index
	if (poz >= nr || poz < 0) {
		return T{};
	}
	T el;
	int i = 0;
	Node<T>* ant = nullptr;
	Node<T>* c = first;
	while (i != poz) {
		if (i == poz - 1) {
			ant = c;
		}
		c = c->getNext();
		i++;
	}
	if (poz == 0) {
		first = first->getNext();
	}
	if (ant != nullptr) {
		ant->setNext(c->getNext());
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
LinkedList<T>::LinkedList(LinkedList & ot) {
	Node<T>* c = ot.first;
	first = new Node<T>(c->elem());
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
LinkedList<T>& LinkedList<T>::operator=(LinkedList& ot) {
	Node<T>* c = ot.first;
	first = new Node<T>(c->elem());
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
LinkedList<T>::LinkedList(LinkedList && ot) {
	Node<T>* c = ot.first;
	first = new Node<T>(c->elem());
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
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& ot) {
	Node<T>* c = ot.first;
	first = new Node<T>(c->elem());
	while (c->getNext() != nullptr) {
		c = c->getNext();
		add(c->elem());
	}
	return *this;
}

//returning an iterator at the first element of the list
template<class T>
IteratorLL<T> LinkedList<T>::begin() {
	return IteratorLL<T>(*this, first);
}


//returning an iterator after the last element of the list
template<class T>
IteratorLL<T> LinkedList<T>::end() {
	return IteratorLL<T>(*this, nullptr);
}

/* The desctructor is recursively
 * deleting the first element , setting first to point to the second element , and call the destructor
 * the condition to stop is if the first is null pointer
 */
template<class T>
LinkedList<T>::~LinkedList() {
	while (first != nullptr) {
		auto x = first->getNext();
		delete first;
		first = x;
	}
}
