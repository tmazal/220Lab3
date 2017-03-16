#include <iostream>
#include <stdlib.h>
#include "Node.hpp"
#include "LL.hpp"
using namespace std;

int main(){
  LL *LL1 = new LL();
  LL1->push(1);
  LL1->push(2);
  LL1->push(3);
  LL1->push(4);
  LL1->push(5);
  LL1->printList();
  LL1->removekth(4);
  LL1->removekth(0);
  LL1->removekth(2);
  LL1->removekth(0);
  LL1->printList();
}//end main