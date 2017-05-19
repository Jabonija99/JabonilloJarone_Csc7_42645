/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameAi.h
 * Author: Kauru99
 *
 * Created on April 19, 2017, 8:16 PM
 */

#ifndef GAMEAI_H
#define GAMEAI_H

class GameAi {
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
    GameAi(int); //Constructor
    ~GameAi();  //Deconstructor
    void start(); //Start game
};

#endif /* GAMEAI_H */

