#include "Game.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;

Game::Game() {  
// for non-automatized version - asks for board size, num players, num of computer players, and then initializes
 // everything
    cout << "What board size would you like to play on?" << endl;
    cin >> size;
    cout << "How many players will there be?" << endl;
    cin >> numPlayers;
    cout << "How many of those players are computers?" << endl;
    cin >> compplayers;
}//Game

Game::Game(bool b) {
//for the automated version - if b is true, randomly generate the size of the board, set the num of players and the
//num of compplayers to 2, and the, of course initialize everything
    srand(time(NULL));
    size = rand()%9+3;
    numPlayers = 2;
    compplayers = 2;
}//Game

void Game::makeBoard(){
// dynamically generates the board to be size by size, with each cell initially set to '.'
    board = new char*[size]; //x
    for (int i = 0; i < size; i++) {
        board[i] = new char[size];
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            board[i][j] = '.';
        }
    }
}//makeBoard

void Game::printBoard() {
//Note: I'm giving you this one
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << board[i][j]<<"\t";
        }
        cout << endl;
    }
}//printBoard

void Game::getPlayers() {
//This method dynamically generates an array of players, and then, for each element in the array, creates a new 
//player object with a name and a character.  For the number of players that are computers, I used an array of names
// and an array of characters, and then just selected the next name and character in the list for my player object.
// for humans I called the Player constructor with no input parameters (that one asked the user for their name and 
// their preferred character.
    string compNames[] = {"Adam", "Brittany", "Charles", "Danielle", "Edward"};
    char compChars[] = {'a','b','c','d','e'};
    players = NULL;
    int cp = compplayers;
    players = new Player*[numPlayers];   //made an array for pointers to Players
    for (int i = 0; i < numPlayers; i++){
        if (cp > 0){
            players[i] = new Player(compNames[i], compChars[i], 1);
            cp--;
        }
        else {
            players[i] = new Player();
        }
    }
}//getPlayers

void Game::printPlayers() {
    // this method is optional - I wrote it so I could test my getPlayers() method to make sure it generated all my Players
    // correctly.  If you choose not to include this method, that is fine.
    for (int i = 0; i < numPlayers; i++){
        cout << (*players[i]).name << endl;
    }
}//printPlayers

void Game::playGame() {
// This is the heart of the game.  I called this method directly from my Game constructor(s) as the very last thing.
//This method loops until the board is full.  
// In each loop, the next player either chooses where to place their character (if human) or the x,y coordinates are 
// randomly generated (and checked to make sure the player isn't overwriting a piece already on the board).
//It checks to see if the new piece completes a square, and, if so, that player's score goes up by 1 and that player
// takes another turn.  At the end of each round, the board is printed out and each player's name and score is printed.

//Your code goes here
    int loop = size^2;
    for (int i = 0; i < loop; i++){
        
    }
    
//Note: for the extra credit version, the findMoves method returns a dynamically created array of 3 different moveLists. 
// The first of the 3  contains the list of moves that would complete a square. The second of the 3 contains a list of 
// neutral moves, and the third of the 3 contains the list of moves that place a third corner on a square (which are bad 
// moves because the next player will then be able to complete a square.
// In this version, the next move is chosen by first trying to pick (randomly) among potential moves that would 
// complete a square, and then by trying to pick a move that is, in essence, neutral, and then last, it chooses from the
// list of bad moves as a last resort.
}//playGame

bool Game::findMoves(char v){
//    Regular version, this method continues to generate random x,y values until that cell on the
//    board is empty, then places the player's character v on the board, and checks to see if a 
//    square is completed using checkFour.  If so, true is returned and that player's score goes up by 1 in the
//    playGame method, and that player gets to take another turn (so turn does not increase by 1).  
    int playerIndex;
    bool placed = false;
    //finds index of player playing
    for (int i = 0; i < numPlayers; i++){
        if ((*players[i]).c == v){
            playerIndex = i;
        }
    }
    int xcoord = rand()%size;
    int ycoord = rand()%size;
    for (int i = 0; i < 100; i++){
        if (board[xcoord][ycoord] == '.'){
            board[xcoord][ycoord] = v;
            placed = true;
            if (checkFour(xcoord, ycoord) == 1){
                (*players[playerIndex]).score++;
                findMoves(v);
            }
            else{
                break;
            }
        }
    xcoord = rand()%size;
    ycoord = rand()%size;
    }
    //100 tries to randomly generate values and place on an empty space
    if (placed == false){   //if no empty spaces found we iterate through entire board sequentially
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (board[xcoord][ycoord] == '.'){
                    board[xcoord][ycoord] = v;
                    placed = true;
                    if (checkFour(xcoord, ycoord) == 1){
                        (*players[playerIndex]).score++;
                        findMoves(v);
                    }
                    else{
                        break;
                    }
                }
            }
        }
    }
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

bool Game::checkFour(int x, int y) {
    string potChars = "";   //make list of characters in use
    string compChars[] = {"a","b","c","d","e"};
    for (int i = 0; i < compplayers; i++){
        potChars += (compChars[i]);
    }
    for (int i = compplayers; i < numPlayers; i++){
        potChars += (*players[i]).c;
    }
    cout << (board[x][y] == '.');
    if ((potChars.find(board[x-1][y-1]) != std::string::npos) && (potChars.find(board[x][y-1]) != std::string::npos) && (potChars.find(board[x-1][y]) != std::string::npos)){
        return true;
    }
    else if ((potChars.find(board[x+1][y-1]) != std::string::npos) && (potChars.find(board[x][y-1]) != std::string::npos) && (potChars.find(board[x+1][y]) != std::string::npos)){
        return true;
    } 
    else if ((potChars.find(board[x+1][y+1]) != std::string::npos) && (potChars.find(board[x][y+1]) != std::string::npos) && (potChars.find(board[x+1][y]) != std::string::npos)){
        return true;    
    }
    else if ((potChars.find(board[x-1][y+1]) != std::string::npos) && (potChars.find(board[x][y+1]) != std::string::npos) && (potChars.find(board[x-1][y]) != std::string::npos)){
        return true;
    }
    else {
        return false;
    }
// this method checks to see if placing a piece at x and y on the board will complete a square, and, if so, it
// returns true.  Otherwise it returns false.
}//checkFour

void Game::getWinner() {
    int highestScore = -1;
    int indexOfWinner;
    for(int i = 0; i < numPlayers; i++){
	if((*players[i]).score > highestScore){
            highestScore = (*players[i]).score;
	}//if
    }//for
    for(int i = 0; i < numPlayers; i++){
        if ((*players[i]).score == highestScore){
            cout << "Winner: " << (*players[i]).name << "!" << endl;
        }
    }
    //multiple players printed in the case of a tie
// This method determines which of the players in the array of Players has the highest score, and prints out 
// that player's name and their score.
}//getWinner


bool Game::checkThree(int x, int y) {
// Only needed for Extra Credit
// This method determines whether placing a piece on the board at x and y will complete - of a square and, if so, it
// returns true.  Otherwise it returns false.
}//checkThree

