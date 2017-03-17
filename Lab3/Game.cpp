#include "Game.hpp"
#include "movesList.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;

Game::Game() {  
//Game constructor for non-automatized version - asks for board size, num players, num of computer players, and then initializes
//everything
    cout << "Welcome to Dots and Boxes!" << endl;
    cout << "What board size would you like to play on?" << endl;
    cin >> size;
    cout << "How many players will there be?" << endl;
    cin >> numPlayers;
    cout << "How many of those players are computers?" << endl;
    cin >> compplayers;
    boardFull = false;
    turn = 0;
    if (boardFull == false){ //should always be true
        makeBoard();    //board is made
        cout << "Empty board: " << endl;
        printBoard();   //empty board printed
        cout << endl;
        getPlayers();   //players selected
        printPlayers(); //players printed
        playGame();     //game is played
    } 
}//Game

Game::Game(bool b) {
//Game constructor for the automated game version - if b is true, randomly generate the size of the board, set the num of players and the
//num of compplayers to 2, and the, of course initialize everything
    if (b==1){  //as long as b is true we initialize appropriate values
        cout << "Welcome to Dots and Boxes! (AI Version)" << endl;
        srand(time(NULL));
        size = rand()%9+3;
        numPlayers = 2;
        compplayers = 2;
        boardFull = false;
        turn = 0;
    }
    if (boardFull == false){ //should always be true
        makeBoard();    //board is made
        cout << "Empty board: " << endl;
        printBoard();   //empty board printed
        cout << endl;
        getPlayers();   //players selected
        printPlayers(); //players printed
        playGame();     //game is played
    } 
}//Game

void Game::makeBoard(){
// This function dynamically generates the board to be size by size, with each cell initially set to '.'
// It takes no inputs and returns nothing.
    board = new char*[size];            //board dynamically generated to hold address of array of chars of size size for each index
    for (int i = 0; i < size; i++) {    //for loop places an array of characters of size size at each index
        board[i] = new char[size];      //subarrays dynamically generated
    }
    for (int i = 0; i < size; i++){     //double for loop used to 
        for (int j = 0; j < size; j++){ //set each character in the array to '.'
            board[i][j] = '.';      //board[y][x] made!! where (0,0) is the top left corner of the board and (size-1,size-1) is the bottom right corner. 
        }                           //note: coordinate order for the board indices is y,x NOT x,y! this is accounted for in all functions                  
    }
}//makeBoard

void Game::printBoard() {
//Note: I'm giving you this one. This function prints the board by iterating with a for loop. Nothing is input and nothing is returned.
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j]<<"\t";
        }
        cout << endl << endl;   //added another print line for better spacing
    }
}//printBoard

void Game::getPlayers() {
//This method dynamically generates an array of pointers to players, and then, for each element in the array, creates a new 
//player object with a name and a character.  For the number of players that are computers, an array of names
// and an array of characters was utilized, and the next name and character in the list was selected for the player object.
// for humans the Player constructor was called with no input parameters (that one asked the user for their name and 
// their preferred character.
// Nothing is input and nothing is returned.
    string compNames[] = {"Adam", "Brittany", "Charles", "Danielle", "Edward"}; //computer names array
    char compChars[] = {'a','b','c','d','e'};       //computer characters array
    players = NULL; //array of players initialized to null
    int cp = compplayers;   //iterator int initially set to number of computer players
    players = new Player*[numPlayers];   //dynamically generated an array of pointers to Players
    for (int i = 0; i < numPlayers; i++){   //iterates through the number of players to call the constructor appropriately
        if (cp > 0){    //if there are still computer players to create
            players[i] = new Player(compNames[i], compChars[i], 1); //we create them dynamically
            cp--;       //and decrement the iterator for computer players
        }
        else {          //otherwise if there are still non-computer players to make
            players[i] = new Player();  //human players are generated dynamically
        }
    }
}//getPlayers

void Game::printPlayers() {
    //This optional method prints out the players as well as their scores using a for loop.
    //It takes no input and returns nothing.
    for (int i = 0; i < numPlayers; i++){   //for loop iterates to print
        cout << (*players[i]).name << " | Score: " << (*players[i]).score << endl;  //All players and their respective scores
    }
    cout << endl;
}//printPlayers

void Game::playGame() {
// This is the heart of the game.  This method is called directly from the Game constructor(s) as the very last thing.
// This method loops until the board is full.  
// In each loop, the next player either chooses where to place their character (if human) or the x,y coordinates are 
// randomly generated (and checked to make sure the player isn't overwriting a piece already on the board).
// If extra credit is operational, the AI will make smart decisions about where to place their pieces.
//The function checks to see if the new piece completes a square, and, if so, that player's score goes up by 1 and that player
// takes another turn.  At the end of each round, the board is printed out and each player's name and score is printed.
//The chance to play another game is also offered.
    int loop = 0;   //number of loop iterations initialized to 0
    int xco = -1;   //coordinates initialized to -1
    int yco = -1;
    bool loopcond = true;       //boolean condition for continued placing
    bool firstplace = true;     //first placement condition for human players
    int playagain;  //int used to determine whether we want to keep playing
    movesList* moveslists = NULL;
    int randomchoice;
    while (loop < size*size){   //as long as we have not looped more than the number of available spaces...
        if ((*players[turn]).isComputer == true){   //if it is the computer's turn
            while (loopcond == true){   //as long as they are allowed to keep placing
                //The following codes works when not employing the AI from the extra credit version! (fully functional)
                /*
                if (findMoves((*players[turn]).c) == true){ //if computer played coordinates complete a square
                    loop++; //the loop count is incremented
                    if (loop == size*size){ //a check is done for whether we are out of moves
                        loopcond = false;   //in the case that the inner while loop and then outer while loop stop iterating
                    }
                }
                else{  //computer played coordinates do not complete a square
                    loop++; //loop counter incremented
                    loopcond = false;   //stop looping (inner while)
                    printPlayers();     //players printed; Note: turn incremented when findMoves is called
                }
                 */
                
                //Extra Credit Portion - submission pending
                cout << "test";
                moveslists = findMoves((*players[turn]).c);
                cout << "Good Moves" << endl;
                for (int i = 0; i < moveslists[0].numMoves; i++){
                    cout << "x: " << moveslists[0].potentialMoves[i].x << endl;
                    cout << "y: " << moveslists[0].potentialMoves[i].y << endl;
                }
                cout << "Neutral Moves" << endl;
                for (int i = 0; i < moveslists[1].numMoves; i++){
                    cout << "x: " << moveslists[1].potentialMoves[i].x << endl;
                    cout << "y: " << moveslists[1].potentialMoves[i].y << endl;
                }
                cout << "Bad Moves" << endl;
                for (int i = 0; i < moveslists[2].numMoves; i++){
                    cout << "x: " << moveslists[2].potentialMoves[i].x << endl;
                    cout << "y: " << moveslists[2].potentialMoves[i].y << endl;
                }
                if (moveslists[0].numMoves > 0){
                    randomchoice = rand()%moveslists[0].numMoves;
                    board[moveslists[0].potentialMoves[randomchoice].y][moveslists[0].potentialMoves[randomchoice].x] = (*players[turn]).c;
                    (*players[turn]).score++;    //if so, score increases
                    printBoard();                       //board is printed
                    cout << "Score +1 for Player " << (*players[turn]).name << endl << endl;    //score +1 printed
                    printPlayers();
                    loop++; //the loop count is incremented
                    if (loop == size*size){ //a check is done for whether we are out of moves
                        loopcond = false;   //in the case that the inner while loop and then outer while loop stop iterating
                    }
                }
                else if (moveslists[1].numMoves>0){
                    randomchoice = rand()%moveslists[1].numMoves;
                    board[moveslists[1].potentialMoves[randomchoice].y][moveslists[1].potentialMoves[randomchoice].x] = (*players[turn]).c;
                    printBoard();
                    printPlayers();
                    loop++;
                    loopcond = false;
                }
                else {
                    randomchoice = rand()%moveslists[2].numMoves;
                    board[moveslists[2].potentialMoves[randomchoice].y][moveslists[2].potentialMoves[randomchoice].x] = (*players[turn]).c;
                    printBoard();
                    printPlayers();
                    loop++;
                    loopcond = false;
                }
                 //
            }
        }
        else{   //if it is the player's turn
            while (loopcond == true){   //as long as they are allowed to start/continue placing
                while (firstplace == true || xco >= size || yco >= size || xco < 0 || yco < 0 || board[yco][xco] != '.' ){    //as long as they start placing or do not choose an appropriate placement; we ask for input coordinates
                    cout << (*players[turn]).name << ", please choose x and y coordinates to play your piece in a new spot. Range is from 0 to " << (size-1) << " inclusive." << endl << "x coord?" << endl;
                    cin >> xco; //x coordinate input
                    cout << "y coord?" << endl;
                    cin >> yco; //y coordinate input
                    firstplace = false; //first placement set to false so the other conditions will be checked instead (size constraints and occupied check)
                }
                board[yco][xco] = (*players[turn]).c;   //when appropriate placement found, the board is updated
                if (checkFour(yco, xco) == true){   //if player coordinates complete a square
                    (*players[turn]).score++;       //their score is incremented
                    cout << endl << "Score +1 for Player " << (*players[turn]).name << endl;    //score + 1 printed
                    printBoard();   //board printed
                    printPlayers(); //players printed
                    loop++;         //loop incremented
                    if (loop == size*size){ //check whether we are out of moves in the board
                        loopcond = false;   //if so, stop looping (inner and then outer while loop stop)
                    }
                }
                else{   //if player does not complete the square
                    turn++; //turn is incremented
                    if (turn == numPlayers){    //if all players have played their turn, rotation resets
                        turn = 0;
                    }
                    loop++; //loop counter incremented
                    loopcond = false;   //loop condition updated so inner while loop ends
                    printBoard();   //board printed
                    printPlayers(); //players printed
                }
            }
        }
        loopcond = true;    //inter while loop condition set to true so we can enter while loop after out loop iterates
    }
    getWinner();    //after all moves played; winner is found!
    //Player is asked whether they want to play again; calling appropriate constructor for the type of the game that will be played
    cout << "Want to play again? Type '1' for regular version or '2' to view an epic AI game. '0' to quit." << endl;
    cin >> playagain;
    if (playagain == 1){    //regular game started
        cout << endl;
        Game game;  //starts a new game (non-AI version)
    }
    if (playagain == 2){    //AI game started; useful for testing
        cout << endl;
        Game(1);
    }
    boardFull = true;   //boolean updated; not used within this code really
//Note: for the extra credit version, the findMoves method returns a dynamically created array of 3 different moveLists. 
// The first of the 3  contains the list of moves that would complete a square. The second of the 3 contains a list of 
// neutral moves, and the third of the 3 contains the list of moves that place a third corner on a square (which are bad 
// moves because the next player will then be able to complete a square.
// In this version, the next move is chosen by first trying to pick (randomly) among potential moves that would 
// complete a square, and then by trying to pick a move that is, in essence, neutral, and then last, it chooses from the
// list of bad moves as a last resort.
}//playGame

/*
bool Game::findMoves(char v){
//    Regular version (fully functional), this method continues to generate random x,y values until that cell on the
//    board is empty, then places the player's character v on the board, and checks to see if a 
//    square is completed using checkFour.  If so, true is returned and that player's score goes up by 1 in the
//    playGame method, and that player gets to take another turn (so turn does not increase by 1).  
//    As mentioned, this function takes in a character and returns 1 if a square is complete at a random x,y value.
    int playerIndex;    //int that will hold the index of the player with character v
    bool placed = false;    //boolean represents whether a char is placed
    //finds index of player playing by character
    for (int i = 0; i < numPlayers; i++){   //iterate through players
        if ((*players[i]).c == v){          //until we find who the character belongs to
            playerIndex = i;                //and set playerindex
        }
    }
    int xcoord = rand()%size;               //random x,y coords generated from 0 to size exclusive
    int ycoord = rand()%size;
    for (int i = 0; i < 100; i++){          //for loop has 100 tries to find an unoccupied spot on the board
        if (board[ycoord][xcoord] == '.'){  //if spot unoccupied
            board[ycoord][xcoord] = v;      //we place character these
            placed = true;
            if (checkFour(ycoord, xcoord) == 1){    //and check if a square is completed
                (*players[playerIndex]).score++;    //if so, score increases
                printBoard();                       //board is printed
                cout << "Score +1 for Player " << (*players[turn]).name << endl << endl;    //score +1 printed
                printPlayers();                     //players printed
                return true;    //true returned, square made
            }
            else{           //if a character is placed but the square is not completed
                turn++;     //turn is incremented
                if (turn == numPlayers){    //loop loops back to start of rotation if everyone has played their turn
                    turn = 0;               //by setting turn to 0
                }
                printBoard();               //board is printed
                return false;   //false returned, no square made
            }
        }
    xcoord = rand()%size;   //x,y coordinates randomized again
    ycoord = rand()%size;
    }
    //this point is reached if no x,y coordinates for unoccupied spaces are found within 100 attempts
    if (placed == false){   //if no empty spaces found we iterate through entire board sequentially
        for (int i = 0; i < size; i++){         //to find the first unoccupied space by iterating through x,y
            for (int j = 0; j < size; j++){
                if (board[ycoord][xcoord] == '.'){   //same as before, character is placed  
                    board[ycoord][xcoord] = v;       //if a blank spot is found
                    placed = true;                   //boolean updated
                    if (checkFour(ycoord, xcoord) == 1){    //and score incremented if square is completed
                        (*players[playerIndex]).score++;
                        printBoard();
                        cout << "Score +1 for Player " << (*players[turn]).name << endl << endl;
                        printPlayers();
                        return true;    //true returned for complete square
                    }
                    else{   //no square made
                        turn++;
                        if (turn == numPlayers){
                            turn = 0;
                        }
                        printBoard();
                        return false;   //false returned for no complete square
                    }
                }
            }
        }
    }
    return false; // no moves found; this shouldn't be reached if we keep good count in playGame()
// movesList * Game::findMoves(char v) {
// The extra credit version of this method - this method dynamically creates a list of 3 movesList objects.  It then goes
// through the entire board and classifies each possible move left on the board as being either good (will complete a 
// square, in which case it's added to the new list of movesLists at [0], neutral (doesn't do anything), in which it's
// added to the second of the movesLists, or bad (3/4 of a square), in which case it's added to the third of the
// movesLists.
// This method uses checkFour() method to determine whether a move is good, checkThree to determine if a move is
// bad, and if neither of those is true, then the move is considered neutral.
// This method returns the list of three movesList objects.
}//findMoves
*/

//
movesList *Game::findMoves(char v){
    int playerIndex;    //int that will hold the index of the player with character v
    int listsize0 = 0;  
    int listsize1 = 0;
    int listsize2 = 0;
    cell* cellarray0 = NULL;
    cell* cellarray1 = NULL;
    cell* cellarray2 = NULL;
    int totalmoves = 0;
    for (int i = 0; i < numPlayers; i++){   //iterate through players
        if ((*players[i]).c == v){          //until we find who the character belongs to
            playerIndex = i;                //and set playerindex
        }
    }
    for (int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            if (board[i][j] == '.'){
                totalmoves++;
                if (checkFour(i,j)){
                    listsize0++;
                }
                else if (checkThree(i,j)){
                    listsize2++;
                }
                else {
                    listsize1++;
                }
            }
        }
    }
    movesList* moveslistarray = NULL; //array of players initialized to null
    moveslistarray = new movesList[3];   //dynamically generated an array of pointers to Players
    cellarray0 = new cell[listsize0];
    cellarray1 = new cell[listsize1];
    cellarray2 = new cell[listsize2];
    int k0 = 0;
    int k1 = 0;
    int k2 = 0;
    for (int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            if (board[i][j] == '.'){
                totalmoves++;
                if (checkFour(j,i)){
                    moveslistarray[0].potentialMoves[k0] = cell(j,i);
                    k0++;
                }
                else if (checkThree(j,i)){
                    moveslistarray[2].potentialMoves[k2] = cell(j,i);
                    k2++;
                }
                else {
                    moveslistarray[1].potentialMoves[k1] = cell(j,i);
                    k1++;
                }
            }
        }
    }
    moveslistarray[0].numMoves = listsize0;
    moveslistarray[0].potentialMoves = cellarray0;
    moveslistarray[1].numMoves = listsize1;
    moveslistarray[1].potentialMoves = cellarray1;
    moveslistarray[2].numMoves = listsize2;
    moveslistarray[2].potentialMoves = cellarray2;
    return moveslistarray;
}//findMoves
//

bool Game::checkFour(int y, int x) {
    //This method checks to see if adding the character v to the cell x,y in the board will complete a square, and, if
    // so, returns true 
    //In the regular, this will result in the score of player[turn] going up by one and player[turn]'s character being 
    //added to the board at x,y
    //In the Extra Credit, (this will lead to findMoves adding this cell to the MovesList object (e.g., 
    //allMovesls[0].potentialMoves[allMovesls.numMoves].resetCell(x,y,v);
    //y and x coordinates are taking as input; boolean is returned corresponding to whether a square is made at those coordinates
    string potChars = "";   //will be used list of characters in use by players
    string compChars[] = {"a","b","c","d","e"}; //computer character array
    for (int i = 0; i < compplayers; i++){  //for all computer characters in play
        potChars += (compChars[i]);         //we add these characters to potential characters on the board
    }
    for (int i = compplayers; i < numPlayers; i++){ //for all human characters playing
        potChars += (*players[i]).c;    //their respective characters are also added to the potential board characters
    }
    //The way I coded checkfour essentially checked if 3 adjacent dots were occupied. This worked by checking the character at those cells; if they matched
    //the characters in potential characters then we know that they are occupied.
    //I first checked 8 specific case (4 edges and 4 corners) and then general cases to prevent indexing out of range
    //I commented the first few cases
    if (x == 0){    //left side
        if (y == 0){   //coordinates are at the top left corner
            if ((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos)){   //if all adjacent characters are found to belong to players (meaning they are occupied)
                return true;   //true is returned in the case that (0,1), (1,0), (0,0) are occupied 
            }
            else{
                return false;
            }  
        }
        else if (y == size-1){    //bottom left corner
            //cout << "bl" << endl;
            if ((potChars.find(board[y][x+1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y-1][x+1]) != std::string::npos)){
                return true;    //true is returned in the case that adjacent cells are occupied
            }
            else{
                return false;
            }
        }
        else{   //left edge cases
            //cout << "le" << endl;
            if (((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos)) || ((potChars.find(board[y-1][x+1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos))){
                return true;    //true is returned in the case that adjacent cells are occupied; in the edge case two possibilities are considered rather than one
            }
            else{
                return false;
            }
        }
    }
    else if (x == size-1){  //right side
        if (y == 0){   //top right corner
            //cout << "tr" << endl;
            if ((potChars.find(board[y+1][x-1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos)){
                return true;  
            }
            else{
                return false;
            }  
        }
        else if (y == size-1){    //bottom right corner
            //cout << "br" << endl;
            if ((potChars.find(board[y-1][x-1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos)){
                return true;    
            }
            else{
                return false;
            }
        }
        else{   //right edge cases
            //cout << "re" << endl;
            if (((potChars.find(board[y+1][x-1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos)) || ((potChars.find(board[y-1][x-1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos))){
                return true;
            }
            else {
                return false;
            }
        }
    }
    else if (y == 0){   //top edge cases
        if (((potChars.find(board[y+1][x-1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos)) || ((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos))){
            return true;
        }
        else{
            return false;
        }
    }
    else if (y == size-1){   //bottom edge cases
        if (((potChars.find(board[y][x-1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y-1][x-1]) != std::string::npos)) || ((potChars.find(board[y][x+1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y-1][x+1]) != std::string::npos))){
            return true;
        }
        else{
            return false;
        }
    }
    else{   //general body cases -- all cases that are not edge or corner are considered to return true in the case that a square is completed at given coordinates
        if ((potChars.find(board[y-1][x-1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos)){
            return true;
        }
        else if ((potChars.find(board[y-1][x+1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos)){
            return true;
        } 
        else if ((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos)){
            return true;    
        }
        else if ((potChars.find(board[y+1][x-1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos)){
            return true;
        }
        else {
            return false;
        }
    }
    return false; //should never actually get here, all cases considered.
// Again, this method checks to see if placing a piece at x and y on the board will complete a square, and, if so, it
// returns true.  Otherwise it returns false.
}//checkFour

void Game::getWinner() {
// This method determines which of the players in the array of Players has the highest score, and prints out 
// that player's name and their score. If multiple players have the highest score, they are all winners!
//Nothing is input and nothing is returned.
    int highestScore = -1;  //initialize highest score to -1
    for(int i = 0; i < numPlayers; i++){        //iterate through all players to find the highest score
	if((*players[i]).score > highestScore){ 
            highestScore = (*players[i]).score; //highest score found
	}//if
    }//for
    for(int i = 0; i < numPlayers; i++){            //iterate through all players to find which of them has the highest score
        if ((*players[i]).score == highestScore){   //if they have the highest score..
            cout << "Winner: " << (*players[i]).name << "!" << " Score: " << (*players[i]).score << endl;   //they are announced to be winners!
        }
    }
    //multiple players printed in the case of a tie!
}//getWinner


bool Game::checkThree(int y, int x) {
// Only needed for Extra Credit
// This method determines whether placing a piece on the board at x and y will complete 3/4 of a square, if so, it
// returns true.  Otherwise it returns false.
    string potChars = "";   //will be used list of characters in use by players
    string compChars[] = {"a","b","c","d","e"}; //computer character array
    int adjcount = 0;
    for (int i = 0; i < compplayers; i++){  //for all computer characters in play
        potChars += (compChars[i]);         //we add these characters to potential characters on the board
    }
    for (int i = compplayers; i < numPlayers; i++){ //for all human characters playing
        potChars += (*players[i]).c;    //their respective characters are also added to the potential board characters
    }
    if (x == 0){    //left side
        if (y == 0){   //coordinates are at the top left corner
            if (potChars.find(board[y+1][x+1]) != std::string::npos){
                adjcount++;
            }
            if (potChars.find(board[y+1][x]) != std::string::npos) {
                adjcount++;
            }
            if (potChars.find(board[y][x+1]) != std::string::npos){
                adjcount++;
            }
            if (adjcount == 2){
                return true;
            }
            else{
                return false;
            }  
        }
        else if (y == size-1){    //bottom left corner
            if (potChars.find(board[y][x+1]) != std::string::npos){
                adjcount++;
            }
            if (potChars.find(board[y-1][x]) != std::string::npos){
                adjcount++;
            }
            if (potChars.find(board[y-1][x+1]) != std::string::npos){
                adjcount++;
            }
            if (adjcount == 2){
                return true;
            }
            else{
                return false;
            }  
        }
        else{   //left edge cases
            //cout << "le" << endl;
            if (((potChars.find(board[y][x+1]) != std::string::npos) && (potChars.find(board[y-1][x])) != std::string::npos) || ((potChars.find(board[y-1][x+1]) != std::string::npos)) && ((potChars.find(board[y-1][x]) != std::string::npos)) || ((potChars.find(board[y-1][x+1]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos)) || ((potChars.find(board[y][x+1]) != std::string::npos) && (potChars.find(board[y+1][x])) != std::string::npos) || ((potChars.find(board[y+1][x+1]) != std::string::npos)) && ((potChars.find(board[y+1][x]) != std::string::npos)) || ((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos))){
                return true;    //true is returned in the case that adjacent cells are occupied; in the edge case two possibilities are considered rather than one
            }
            else{
                return false;
            }
        }
    }
    else if (x == size-1){  //right side
        if (y == 0){   //top right corner
            if (potChars.find(board[y+1][x-1]) != std::string::npos){
                adjcount++;
            }
            if (potChars.find(board[y+1][x]) != std::string::npos) {
                adjcount++;
            }
            if (potChars.find(board[y][x-1]) != std::string::npos){
                adjcount++;
            }
            if (adjcount == 2){
                return true;
            }
            else{
                return false;
            }  
        }
        else if (y == size-1){    //bottom right corner
            if (potChars.find(board[y][x-1]) != std::string::npos){
                adjcount++;
            }
            if (potChars.find(board[y-1][x]) != std::string::npos){
                adjcount++;
            }
            if (potChars.find(board[y-1][x-1]) != std::string::npos){
                adjcount++;
            }
            if (adjcount == 2){
                return true;
            }
            else{
                return false;
            }  
        }
        else{   //right edge cases
            //cout << "re" << endl;
            if (((potChars.find(board[y][x-1]) != std::string::npos) && (potChars.find(board[y-1][x])) != std::string::npos) || ((potChars.find(board[y-1][x-1]) != std::string::npos)) && ((potChars.find(board[y-1][x]) != std::string::npos)) || ((potChars.find(board[y-1][x-1]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos)) || ((potChars.find(board[y][x-1]) != std::string::npos) && (potChars.find(board[y+1][x])) != std::string::npos) || ((potChars.find(board[y+1][x-1]) != std::string::npos)) && ((potChars.find(board[y+1][x]) != std::string::npos)) || ((potChars.find(board[y+1][x-1]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos))){
                return true;    //true is returned in the case that adjacent cells are occupied; in the edge case two possibilities are considered rather than one
            }
            else{
                return false;
            }
        }
    }
    else if (y == 0){   //top edge cases
        if (((potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x+1])) != std::string::npos) || ((potChars.find(board[y][x+1]) != std::string::npos)) && ((potChars.find(board[y+1][x+1]) != std::string::npos)) || ((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos)) || ((potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x-1])) != std::string::npos) || ((potChars.find(board[y+1][x-1]) != std::string::npos)) && ((potChars.find(board[y][x-1]) != std::string::npos)) || ((potChars.find(board[y+1][x-1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos))){
                return true;    //true is returned in the case that adjacent cells are occupied; in the edge case two possibilities are considered rather than one
            }
            else{
                return false;
            }
        }
    else if (y == size-1){   //bottom edge cases
        if (((potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x-1])) != std::string::npos) || ((potChars.find(board[y][x-1]) != std::string::npos)) && ((potChars.find(board[y-1][x-1]) != std::string::npos)) || ((potChars.find(board[y-1][x-1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos)) || ((potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x+1])) != std::string::npos) || ((potChars.find(board[y-1][x+1]) != std::string::npos)) && ((potChars.find(board[y][x+1]) != std::string::npos)) || ((potChars.find(board[y-1][x+1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos))){
                return true;    //true is returned in the case that adjacent cells are occupied; in the edge case two possibilities are considered rather than one
            }
            else{
                return false;
            }
        }
    else{   //general body cases -- all cases that are not edge or corner are considered to return true in the case that a square is completed at given coordinates
        if (((potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x-1])) != std::string::npos) || ((potChars.find(board[y][x-1]) != std::string::npos)) && ((potChars.find(board[y-1][x-1]) != std::string::npos)) || ((potChars.find(board[y-1][x-1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos)) || ((potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x+1])) != std::string::npos) || ((potChars.find(board[y-1][x+1]) != std::string::npos)) && ((potChars.find(board[y][x+1]) != std::string::npos)) || ((potChars.find(board[y-1][x+1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) || (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x+1])) != std::string::npos) || ((potChars.find(board[y][x+1]) != std::string::npos)) && ((potChars.find(board[y+1][x+1]) != std::string::npos)) || ((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos)) || ((potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x-1])) != std::string::npos) || ((potChars.find(board[y+1][x-1]) != std::string::npos)) && ((potChars.find(board[y][x-1]) != std::string::npos)) || ((potChars.find(board[y+1][x-1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos))){             
                return true;    //true is returned in the case that adjacent cells are occupied; in the edge case two possibilities are considered rather than one
            }
            else{
                return false;
            }
        }
    return false; //should never actually get here, all cases considered.
// Again, this method checks to see if placing a piece at x and y on the board will complete a square, and, if so, it
// returns true.  Otherwise it returns false.
}//checkFour