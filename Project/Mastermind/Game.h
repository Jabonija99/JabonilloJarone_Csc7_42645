/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: Kauru99
 *
 * Created on April 19, 2017, 7:41 PM
 */

#ifndef GAME_H
#define GAME_H

class Game {
private:
    int size; //Array size
    int tries; //Tries
    char* ai; //Ai array
    char* player; //Player array
    char* result; //Array for results
    
    bool compare(char[], char[], int); //Compares arrays
    char* check(char[], char[], int); //Checks and returns result
    void output(char[], int); //Output array
    void cls(); //Clear screen
    
public:
    Game(int); //Constructor
    ~Game(); //Deconstructor
    void start(); //Start game
    

};

#endif /* GAME_H */

