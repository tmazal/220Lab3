/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* CISC220 - Lab 3
 * File:   main.cpp
 * Author: Tobias Mazal and Bryan Mejia
 * 3/16/17
 * Created on March 3, 2017, 10:22 AM
 */

#include <cstdlib>
#include "Game.hpp"
using namespace std;

//game class - responsible for all general fields and methods
//necessary for playing the game
//player class - includes all properties and constructors for a player in
//the game (makes game its friend)
//cell class - responsible for holding the x and y coordinates of a cell, 
//cell constructors and methods for resetting a cell's value to x and y

//"Your main function should include, other than seeding the random number generator,
//and returning 0,1 line." Not sure what this means..
/*
 * initiate random!
 */

//left to do -- code playgame and finish up constructors
int main(int argc, char** argv) {
    Game game;
    game.makeBoard();
    game.getPlayers();
    game.printBoard();
    game.printPlayers();
    game.getWinner();
    return 0;
}

