/*
 * Node.hpp
 *
 *  Created on: Mar 15, 2017
 *      Author: Bryan
 */

#ifndef NODE_HPP_
#define NODE_HPP_

class Node {
friend class LL;
int data;
Node *next;
public:
Node(int x);
void printNode();
};

#endif /* NODE_HPP_ */

