/*
 * Node.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: Bryan Mejia and Tobias Mazal
 */

#include "Node.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;
Node::Node(int x) {
    data = x;
    next = NULL;
}
void Node::printNode() {
    cout << "|D:"<< data << "|";
    return;
}
