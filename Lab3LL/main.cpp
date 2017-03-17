/* CISC220 - Lab 3 (Linked Lists)
 * File:   main.cpp
 * Author: Bryan Mejia and Tobias Mazal
 * 3/16/17
 * Created on March 3, 2017, 10:22 AM
 */

#include <iostream>
#include <stdlib.h>
#include "Node.hpp"
#include "LL.hpp"
using namespace std;

int main(){
    //testing
  LL *LL1 = new LL();
  LL1->push(1);
  LL1->push(2);
  LL1->push(3);
  LL1->push(4);
  LL1->push(5); //push nodes with data values 1 - 5 and proceed to delete them 
  LL1->printList();
  LL1->removekth(4);
  LL1->printList();
  LL1->removekth(0);
  LL1->printList();
  LL1->removekth(2);
  LL1->printList();
  LL1->removekth(0);
  LL1->printList();
  LL1->removekth(0);
  LL1->printList(); //prints blank linked list as all elements deleted
}//end main