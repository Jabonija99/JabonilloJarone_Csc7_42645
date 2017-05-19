/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: Kauru99
 * 
 * Created on April 19, 2017, 7:41 PM
 */

#include "Game.h"
#include <cstdlib>
#include <iostream>

Game::Game(int size){
    this->size = size;              //Size for arrays
    tries = 10;                     //Attempts to guess
    ai = new char[this->size];      //Ai code
    player = new char[this->size];  //Player array
    result = new char[this->size];  //Result array
}

Game::~Game(){
    //Remove and delete objects
    ai = NULL;
    delete ai;
    player = NULL;
    delete player;
    result = NULL;
    delete result;
}

void Game::start(){
    std::string ans;
    
    bool quit = false;  //Flag for game end
    bool game = false;  //Flag for game success
    
    srand(static_cast<unsigned int>(time(0)));
    
    do{
        cls();
        std::cout << "Game start\n";
        game = true;
        tries = 10;
        
        //Generate random code
        for(int i = 0; i < size; i++){
            ai[i] = ((rand()%6)+1)+'0';
        }
        
        
        //Output Key table
        std::cout <<"========================================"
                <<std::endl <<"Key: "
                <<std::endl <<"[x]Incorrect color"
                <<std::endl <<"[o]Correct color "
                <<std::endl <<"[*]Correct color and spot"
                <<std::endl <<"========================================\n";
        
        do{
            do{
                //Prompt user guess
                std::string num;
                
                std::cout <<"[" <<tries <<" attempts] "
                        <<"Guess the 4 digit code(1-6):";
                std::cin >> num;

                //Assign input
                for(int i = 0; i < size; i++){
                    player[i] = num[i];
                }
                
                std::cout <<"Confirm (y/n)?";
                std::cin >> ans;
            
            }while(ans[0] != 'y' && ans[0] != 'Y');
            
            //If guess is wrong
            if(!compare(ai, player, size)){
                //Remove try & check result
                tries--;    
                result = check(ai, player, size); 
                
                //Output result
                std::cout <<"Result:";
                output(result, size);
            }
            else{
                game = false;
            }
            
            //When the game ends or player runs out of tries
        }while(tries > 0 && game == true);
        
        
        //Output answer
        std::cout <<"Answer: ";
        output(ai, size);
        
        //Output result
        if(game == true){
            std::cout <<"You lost!\n";
        }
        else{
            std::cout <<"You win!\n";
        }
        
        //Prompt restart
        std::cout <<"Restart (y/n)? ";
        std::cin >> ans;
        
        if(ans[0] == 'n' || ans[0] == 'N'){
            quit = true;
        }
        else{
            quit = false;
        }
    
    }while(!quit);
}

bool Game::compare(char code[], char guess[], int size){
    //Compares arrays and returns resulting bool
    bool success = true;
    for(int i = 0; i < size; i++){
        if(guess[i] != code[i]){
            success = false;
        }
    }
    return success;
}

char* Game::check(char code[], char guess[], int size){
    //Compares and returns the resulting array
    char* ans =  new char[size]; //Array for resulting answer
    int index = 0;              //Index for array
    bool correct = false;       //Flag for correct
    bool almost = false;        //Flag for correct but wrong spot
    
    int star = 0;               //Counter for correct
    int o = 0;                  //Counter for correct but wrong spot
    

    //Check through each line of the code
    for(int i = 0; i < size; i++){
        //Reset flags
        correct = false;
        almost = false;
        
        //Check through guess
        for(int j = 0; j < size; j++){
            //If the guess matches the code and spot
            if(j == i && code[i] == guess[j]){
                //Raise correct flag
                correct = true;
                almost = false;
            }
            //If the guess matches the code but not the spot
            else if(!correct && code[i] == guess[j]){
                //Raise almost flag
                almost = true;
            }
        }
        
        //Increment counter based on result
        if(correct){
            star++;
        }
        else if(almost){
            o++;
        }
    }
    
    //Insert results into the answer array
    for(int i = 0; i < size; i++){
        if(star > 0){
            ans[i] = '*';
            star--;
        }
        else if(star < 1 && o > 0){
            ans[i] = 'o';
            o--;
        }
        else{
            ans[i] = 'x';
        }
    }

    //Return answer
    return ans;
}

void Game::output(char array[], int size){
    //Output array
    for(int i = 0; i < size; i++){
        std::cout <<array[i];
    }
    std::cout <<std::endl;
}

void Game::cls(){
    //Clear screen
    for(int i = 0 ; i < 10; i++){
        std::cout <<std::endl;
    }
}
