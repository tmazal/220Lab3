/*
 * LL.hpp
 *
 *  Created on: Mar 15, 2017
 *      Author: Bryan
 */

#ifndef LL_HPP_
#define LL_HPP_

#include "Node.hpp"
class LL {
 Node *first;
 Node *last;
 int currsize;
public:
 LL(); //constructor
 void push(int x); //adds new node to end of list
 void removekth(int k); // removes the kth node from the list
 void printList(); // prints out the entire list
};

#endif /* LL_HPP_ */

