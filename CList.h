#pragma once
#include <iostream>
#include <stack>

using namespace std;

template<class C>
struct Node {
	Node(C n_data, Node<C> *n_next = NULL);

	C data;
	Node<C> *next;
	Node<C> *down = NULL;
};

template<class C>
Node<C>::Node(C n_data, Node<C> *n_next) : data(n_data), next(n_next) {}

//******************************

template<class C>
struct CList_PTR2
{
	CList_PTR2();
	bool FindInMain(C n_data, Node<C> **&n_tnode);
	bool FindInSubList(C n_data, Node<C> **&n_tnode);
	bool FindElement(C n_data, Node<C> **&n_tnode);
	void AddNewNode(C n_ndata);
	void RemoveNode(C n_ndata);
	void NewLast();
	void Clear();
	bool IsEmpty();
	void PrintList();
	~CList_PTR2();

	Node<C> *head;
	Node<C> *last;
	Node<C> *Runner;
	bool main_node = true;
};

//*********************************************************************************

template<class C>
bool CList_PTR2<C>::IsEmpty() {
	return !head;
}

template<class C>
CList_PTR2<C>::CList_PTR2() {
	head = NULL;
	last = NULL;
}

template<class C>
void CList_PTR2<C>::NewLast() {
	for (last = head; last and last->next != NULL; last = last->next) {}
}

template<class C>
bool CList_PTR2<C>::FindInMain(C n_data, Node<C> **&n_tnode) {
	for (n_tnode = &head; *n_tnode and n_data > (*n_tnode)->data and (*n_tnode)->next != head; n_tnode = &((*n_tnode)->next)) { }
	return *n_tnode and (*n_tnode)->data == n_data;
}

template<class C>
bool CList_PTR2<C>::FindElement(C n_data, Node<C> **&n_tnode) {
	for (n_tnode = &head; *n_tnode and n_data > (*n_tnode)->data and (*n_tnode)->next != head; n_tnode = &((*n_tnode)->next)) {
		if (n_data % (*n_tnode)->data == 0) {
			main_node = false;
			Node<C> **sub_temp = n_tnode;
			while (*sub_temp and (*sub_temp)->data < n_data) {
				sub_temp = &((*sub_temp)->down);
			}
			if (*sub_temp and n_data != (*sub_temp)->data) {
				Node<C> *newsubnode = new Node<C>(n_data, NULL);
				newsubnode->down = (*sub_temp)->down;
				(*sub_temp)->down = newsubnode;
			}
			if ((*sub_temp) == NULL) {
				(*sub_temp) = new Node<C>(n_data);
			}
		}
	}
	return *n_tnode and (*n_tnode)->data == n_data;
}

template<class C>
bool CList_PTR2<C>::FindInSubList(C n_data, Node<C> **&n_tnode) {
	for (; *n_tnode and n_data > (*n_tnode)->data; n_tnode = &((*n_tnode)->down)) {}
	return *n_tnode and (*n_tnode)->data == n_data;
}

template<class C>
void CList_PTR2<C>::AddNewNode(C n_ndata) {
	stack<C> Pila1, Pila;
	Node<C> **temp_node;
	if (last) {
		last->next = NULL;
	}
	if (!FindElement(n_ndata, temp_node)) {
		if (main_node == true) {
			Node<C> *newnode = new Node<C>(n_ndata, *temp_node);
			*temp_node = newnode;
			if ((*temp_node)->next == NULL) last = *temp_node;
			Node<C> **temptemp = temp_node;

			temp_node = &((*temp_node)->next);
			while (*temp_node) {
				if ((*temp_node)->data % n_ndata == 0) {
					Pila1.push((*temp_node)->data);
				}
				Node<C> **sub_temp = temp_node;
				while (*sub_temp) {
					if ((*sub_temp)->data % n_ndata == 0)
						Pila.push((*sub_temp)->data);
					sub_temp = &((*sub_temp)->down);
				}
				temp_node = &((*temp_node)->next);
			}

			while (!Pila.empty()) {
				Node<C> **SUBtempnode = temptemp;
				if(!FindInSubList(Pila.top(), SUBtempnode)) {
					Node<C> *anewnode = new Node<C>(Pila.top(),NULL);
					anewnode->down = *SUBtempnode;
					(*SUBtempnode) = anewnode;
				}
				Pila.pop();
			}
		}
	}
	last->next = head;
	main_node = true;

	while (!Pila1.empty()) {
		RemoveNode(Pila1.top());
		Pila1.pop();
	}
}

template<class C>
void CList_PTR2<C>::RemoveNode(C n_ndata) {
	if (last) {
		last->next = NULL;
	}
	Node<C> **temp_node = &head;
	if (FindInMain(n_ndata, temp_node)) {
		Node<C> *t_ptr = (*temp_node)->next;
		if (*temp_node == last) last = NULL;
		delete *temp_node;
		*temp_node = t_ptr;
	}
	if (!last) NewLast();
	if (last) last->next = head;
}

template<class C>
void CList_PTR2<C>::PrintList() {
	if (IsEmpty()) {
		cout << "[ The list is empty! ]" << endl;
		return;
	}
	Runner = head->next;
	Node<C> *temp = head;
	while (temp) {
		cout << temp->data << "->";
		temp = temp->down;
	}
	cout << "NULL\n|\nV" << endl;
	while (Runner != head) {
		temp = Runner;
		while (temp) {
			cout << temp->data << "->";
			temp = temp->down;
		}
		cout << "NULL\n|\nV" << endl;
		Runner = Runner->next;
	}
	temp = Runner;
	while (temp) {
		cout << temp->data << "->";
		temp = temp->down;
	}
	cout << "NULL" << endl;
}

template<class C>
void CList_PTR2<C>::Clear() {
	while (head) {
		RemoveNode(head->data);
	}
}

template<class C>
CList_PTR2<C>::~CList_PTR2() {
	//Clear();
}
