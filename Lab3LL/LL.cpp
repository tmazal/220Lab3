/*
 * LL.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: Bryan
 */

#include <iostream>
#include <stdlib.h>
#include "Node.hpp"
#include "LL.hpp"
using namespace std;

LL::LL() {
first = NULL;
last = NULL;
currsize = 0;
}//LL

void LL::push( int x) {
// this function creates a new Node, then adds the node to the end of the list and updates //the last pointer.
//Note: you�fll want to check to see if this is the very first node being added to the list, //in which case you�fll want to
//create the new node, and then make sure that both the first //and the last pointer point to it.
	Node *node = new Node(x);
	if(first == NULL){
		first = node;
		last = node;
		currsize = 1;
	}//if
	else {
		last->next = node;
		last = node;
		currsize += 1;
	}//else
}//push

void LL::removekth(int i) {
// this method starts at the first node in the list and counts to i-1. It then deletes the //node at location i. Note that
//you must make node at i-1 point to node at i+1, and you //must decrease the size of the list. If you are deleting the
//0th element, you must first //set first to the node at 2 before deleting node 1. Equally, if you are deleting the last
//node, you must make the new last node be the node at i-1.
//You must delete your node at i.
	if(currsize == 0){
		cout << "List is already empty" << endl;
		return;
	}//if
	if(i >= currsize){
		cout << "Out of scope" << endl;
		return;
	}//if
	Node *tmp = first;
	if(i == 0 && currsize == 1){
		delete first;
		first = NULL;
		last = NULL;
		currsize = 0;
		return;
	}//if
	else if(i == 0){
		first = first->next;
		delete tmp;
		currsize--;
		return;
	}//else if
	for(int j = 0; j < i-1; j++){
		tmp = tmp->next;
	}//for
	Node *tmpDelete = tmp->next;
	tmp->next = tmp->next->next;
	delete tmpDelete;
	currsize--;
	if(i == currsize && tmp->next != NULL){
		last = tmp->next;
	}//if
	else if(i == currsize && tmp->next == NULL){
		last = tmp;
	}//else if
}//removekth

void LL::printList(){
// Make sure you can write a method that prints out every node in the linked list
	Node *node = first;
	while(node){
	  node->printNode();
		node = node->next;
	}//while
	cout << endl;
}//printList

