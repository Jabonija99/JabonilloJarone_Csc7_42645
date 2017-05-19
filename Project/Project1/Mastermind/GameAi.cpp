/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameAi.cpp
 * Author: Kauru99
 * 
 * Created on April 19, 2017, 8:16 PM
 */

#include "GameAi.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

GameAi::GameAi(int size){
    
    this->size = size;              //Size for array
    tries = 10;                     //Attempts to guess
    ai = new char[this->size];      //Ai code
    player = new char[this->size];  //Player array
    result = new char[this->size];  //Resulting array
}

GameAi::~GameAi(){
    //Remove and delete objects
    ai = NULL;
    delete ai;
    player = NULL;
    delete player;
    result = NULL;
    delete result;
}

void GameAi::start(){
    std::string ans;
    
    bool quit = false;  //Flag for game end
    bool game = false;  //Flag for game success
    
    srand(static_cast<unsigned int>(time(0)));
    
    do{
        cls();
        game = true;
        tries = 10;
        bool input;
        
        do{
            //Reset input flag
            input = true;
            
            //Prompt user input for code
            std::cout << "Enter a 4 digit code:";
            std::cin >> ans;
            
            //Validate code
            for(int i = 0; i < size; i++){
                if(ans[i] - '0' < 1 || ans[i]-'0' > 6 ){
                    input = false;
                }
            }
            
            cls();
            //If validation fails
            if(!input){
                //Output error
                std::cout <<"**********************\n"
                        <<"Invalid code!\n"
                        <<"**********************\n";
            }
            else{
                //Confirm player code
                for(int i = 0; i < size; i++){
                    player[i] = ans[i];
                }
                
                std::cout <<"Your code: ";
                output(player, size);
                std::cout <<"\nConfirm (y/n)?";
                std::cin >> ans;
                
                if(ans[0] != 'y' && ans[0] != 'Y'){
                    input = false;
                }
            }
        }while(!input);
        
       //Cpu guesses
        std::cout <<"Cpu's turn...\n=====================\n";
        std::cout <<std::left <<std::setw(15) <<"Guess" <<"Result\n";
        
        do{
            //Cpu makes a random guess
            for(int i = 0; i < size; i++){
                ai[i] = ((rand()%6)+1)+'0';
            }
            
            //Output ai guess
            output(ai, size);
            //Output result
            result = check(ai, player, size);
            std::cout <<"\t\t";
            output(result, size);
            std::cout <<std::endl;
            
            //Compare arrays
            if(!compare(ai, player, size)){
                //Reduce tries
                tries--;
            }
            else{
                //Raise game flag
                game = false;
            }
            
        }while(tries > 0 && game == true);
        
        //Output result
        if(game == true){
            std::cout <<"You win!\n";
        }
        else{
            std::cout <<"You lost!\n";
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

bool GameAi::compare(char code[], char guess[], int size){
    //Compares arrays and returns resulting bool
    bool success = true;
    for(int i = 0; i < size; i++){
        if(guess[i] != code[i]){
            success = false;
        }
    }
    return success;
}

char* GameAi::check(char code[], char guess[], int size){
    //Compares and returns the resulting array
    char* ans =  new char[size]; //Array for resulting answer
    int index = 0;              //Index for array
    bool correct = false;       //Flag for correct
    bool almost = false;        //Flag for correct but wrong spot
    
    int star = 0;               //Counter for correct
    int o = 0;                  //Counter for correct but wrong
    

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
            else if(!correct && code[i] == guess[j]){   
                //If the guess matches the code but not the spot
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

void GameAi::output(char array[], int size){
    //Output array
    for(int i = 0; i < size; i++){
        std::cout <<array[i];
    }
}

void GameAi::cls(){
    //Clear screen
    for(int i = 0 ; i < 10; i++){
        std::cout <<std::endl;
    }
}
