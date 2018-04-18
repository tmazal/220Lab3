/*
 * LL.cpp
 *
 *  Created on: Mar 15, 2017
 * Author: Bryan Mejia and Tobias Mazal
 */

#include <iostream>
#include <stdlib.h>
#include "Node.hpp"
#include "LL.hpp"
using namespace std;

LL::LL() {
//this is the constructor
first = NULL;
last = NULL;
currsize = 0;
}//LL

void LL::push(int x) {
//This function takes an integer as a parameter and creates a new Node that holds that integer.
//The function then adds the node to the end of the list and updates the first and/or last pointers as needed.
//The size of the list is then increased by one. Nothing is returned.
	Node *node = new Node(x);
	if(first == NULL){//if there are no nodes in the list, the new node becomes the first and last of that list
		first = node;
		last = node;
		currsize = 1;
	}//if
	else {//otherwise, adds the node to the end of the list and makes the "last" pointer point to that node
		last->next = node;
		last = node;
		currsize += 1;
	}//else
}//push

void LL::removekth(int i) {
//This function takes an integer i as an input parameter and deletes the node at that index from the linked list.
//Also, it points the previous node to the node after the deleted one, if it exists.  It then decreases
//the size of the list by one. Nothing is returned.
	if(currsize == 0){//if there are no nodes in the list, the method is exited and prints that the list is already empty, therefore, you cannot remove anything.
		cout << "List is already empty" << endl;
		return;
	}//if
	if(i >= currsize){//checks to see that the input parameter is within the scope of the list
		cout << "Out of scope" << endl;
		return;
	}//if
	Node *tmp = first;
	if(currsize == 1){//checks to see if the list only has one item
		delete first;
		first = NULL;
		last = NULL;
		currsize = 0;
		return;
	}//if
	else if(i == 0){//checks to see if the index to be removed is the first one
		first = first->next;
		delete tmp;
		currsize--;
		return;
	}//else if
	for(int j = 0; j < i-1; j++){//stops one index before the inputed one
		tmp = tmp->next;
	}//for
	Node *tmpDelete = tmp->next;//points to the index which is to be deleted
	tmp->next = tmp->next->next;//the pointer before the deleted one then points to the node after the deleted one if it exists
	delete tmpDelete;
	currsize--;
	if(i == currsize && tmp->next != NULL){//checks to see if the node after the removed node is the last one
		last = tmp->next;
	}//if
	else if(i == currsize && tmp->next == NULL){//checks to see if the node before the removed node is the last one
		last = tmp;
	}//else if
}//removekth

void LL::printList(){
//Prints out every node in the linked list. Nothing is input and nothing is returned.
	Node *node = first;
	while(node){//goes through every node in the list and stops when node = NULL
            node->printNode();
            node = node->next;
	}//while
	cout << endl;
}//printList