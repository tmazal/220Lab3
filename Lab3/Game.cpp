#include "Game.hpp"
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
        cout << endl << endl;
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
// This is the heart of the game.  I called this method directly from my Game constructor(s) as the very last thing.
//This method loops until the board is full.  
// In each loop, the next player either chooses where to place their character (if human) or the x,y coordinates are 
// randomly generated (and checked to make sure the player isn't overwriting a piece already on the board).
//It checks to see if the new piece completes a square, and, if so, that player's score goes up by 1 and that player
// takes another turn.  At the end of each round, the board is printed out and each player's name and score is printed.
    int loop = 0;
    int xco = -1;
    int yco = -1;
    int end;
    bool loopcond = true;       //continues placing
    bool firstplace = true;     //first placement condition 
    int playagain;
    while (loop < size*size){
        if ((*players[turn]).isComputer == true){
            while (loopcond == true){
                if (findMoves((*players[turn]).c) == true){
                    loop++;
                    if (loop == size*size){
                        loopcond = false;
                    }
                }
                else{  //turn incremented in findmoves already
                    loop++;
                    loopcond = false;
                    printPlayers();
                }       
            }
        }
        else{
            while (loopcond == true){
                while (firstplace == true || xco >= size || yco >= size || board[yco][xco] != '.' ){
                    cout << (*players[turn]).name << ", please choose x and y coordinates to play your piece in a new spot. Range is from 0 to " << (size-1) << " inclusive." << endl << "x coord?" << endl;
                    cin >> xco;
                    cout << "y coord?" << endl;
                    cin >> yco;
                    firstplace = false;
                }
                board[yco][xco] = (*players[turn]).c;
                if (checkFour(yco, xco) == true){
                    (*players[turn]).score++;
                    cout << endl << "Score +1 for Player " << (*players[turn]).name << endl;
                    printPlayers();
                    printBoard();
                    loop++;
                    if (loop == size*size){
                        loopcond = false;
                    }
                }
                else{
                    turn++;
                    if (turn == numPlayers){
                        turn = 0;
                    }
                    loop++;
                    loopcond = false;
                    printBoard();
                    printPlayers();
                }
                
            }
        }
        loopcond = true;
    }
    getWinner();
    
    cout << "Want to play again? Type '1' for regular version or '2' to view an epic AI game" << endl;
    cin >> playagain;
    if (playagain == 1){
        cout << endl;
        Game game;  //starts a new game (non-AI version)
    }
    if (playagain == 2){
        cout << endl;
        Game(1);
    }
    boardFull = true;
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
    //finds index of player playing by character
    for (int i = 0; i < numPlayers; i++){
        if ((*players[i]).c == v){
            playerIndex = i;
        }
    }
    int xcoord = rand()%size;
    int ycoord = rand()%size;
    for (int i = 0; i < 100; i++){
        if (board[ycoord][xcoord] == '.'){
            board[ycoord][xcoord] = v;
            placed = true;
            if (checkFour(ycoord, xcoord) == 1){
                (*players[playerIndex]).score++;
                printBoard();                
                cout << "Score +1 for Player " << (*players[turn]).name << endl << endl;
                printPlayers();
                return true;
            }
            else{
                turn++;
                if (turn == numPlayers){
                    turn = 0;
                }
                printBoard();
                return false;
            }
        }
    xcoord = rand()%size;
    ycoord = rand()%size;
    }
    //100 tries to randomly generate values and place on an empty space
    if (placed == false){   //if no empty spaces found we iterate through entire board sequentially
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (board[ycoord][xcoord] == '.'){
                    board[ycoord][xcoord] = v;
                    placed = true;
                    if (checkFour(ycoord, xcoord) == 1){
                        (*players[playerIndex]).score++;
                        printBoard();
                        cout << "Score +1 for Player " << (*players[turn]).name << endl << endl;
                        printPlayers();
                        return true;
                    }
                    else{
                        turn++;
                        if (turn == numPlayers){
                            turn = 0;
                        }
                        printBoard();
                        return false;
                    }
                }
            }
        }
    }
    return false; // no moves found
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

bool Game::checkFour(int y, int x) {
    string potChars = "";   //make list of characters in use
    string compChars[] = {"a","b","c","d","e"};
    for (int i = 0; i < compplayers; i++){
        potChars += (compChars[i]);
    }
    for (int i = compplayers; i < numPlayers; i++){
        potChars += (*players[i]).c;
    }
    //checks 8 specific case (4 edges and 4 corners) to prevent indexing out of range of the board and then general cases
    if (x == 0){
        if (y == 0){   //top left corner
            if ((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos)){
                return true;    
            }
            else{
                return false;
            }  
        }
        else if (y == size-1){    //bottom left corner
            //cout << "bl" << endl;
            if ((potChars.find(board[y][x+1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y-1][x+1]) != std::string::npos)){
                return true;    
            }
            else{
                return false;
            }
        }
        else{   //left edge case
            //cout << "le" << endl;
            if (((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos)) || ((potChars.find(board[y-1][x+1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos))){
                return true;
            }
            else{
                return false;
            }
        }
    }
    else if (x == size-1){
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
        else{   //right edge case
            //cout << "re" << endl;
            if (((potChars.find(board[y+1][x-1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos)) || ((potChars.find(board[y-1][x-1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos))){
                return true;
            }
            else {
                return false;
            }
        }
    }
    else if (y == 0){   //top edge
        if (((potChars.find(board[y+1][x-1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x-1]) != std::string::npos)) || ((potChars.find(board[y+1][x+1]) != std::string::npos) && (potChars.find(board[y+1][x]) != std::string::npos) && (potChars.find(board[y][x+1]) != std::string::npos))){
            return true;
        }
        else{
            return false;
        }
    }
    else if (y == size-1){   //bottom edge
        if (((potChars.find(board[y][x-1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y-1][x-1]) != std::string::npos)) || ((potChars.find(board[y][x+1]) != std::string::npos) && (potChars.find(board[y-1][x]) != std::string::npos) && (potChars.find(board[y-1][x+1]) != std::string::npos))){
            return true;
        }
        else{
            return false;
        }
    }
    else{   //general body cases
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
            cout << "Winner: " << (*players[i]).name << "!" << " Score: " << (*players[i]).score << endl;
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

