#include "moveslist.hpp"
#include <cstdlib>
using namespace std;
movesList::movesList() {
// constructor sets potentialMoves to NULL and numMoves to 0
    potentialMoves = NULL;
    numMoves = 0;
}
void movesList::makeList(int s) {
//dynamically creates a new list of cells that is s long, and sets numMoves to 0
    potentialMoves = new cell[s];   //dynamically generated an array of cells
    numMoves = 0;
}
