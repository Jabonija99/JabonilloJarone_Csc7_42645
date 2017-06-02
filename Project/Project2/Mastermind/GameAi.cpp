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
    tries = 100;                    //Attempts to guess
    attempts = 0;                   //Attempts made
    ai = new char[this->size];      //Ai code
    player = new char[this->size];  //Player array
    result = new char[this->size];  //Resulting array
    
    prevGuess = new char*[tries];
    for(int i = 0; i < tries; i++){
        prevGuess[i] = new char[this->size];
    }
    
    prevResult = new char*[tries];
    for(int i = 0; i < tries; i++){
        prevResult[i] = new char[this->size];
    }
}

GameAi::~GameAi(){
    //Remove and delete objects
    ai = NULL;
    delete ai;
    player = NULL;
    delete player;
    result = NULL;
    delete result;
    
    for(int i = 0; i < tries; i++){
        prevGuess[i] = NULL;
        delete [] prevGuess[i];
    }
    prevGuess = NULL;
    delete [] prevGuess;
    
    for(int i = 0; i < tries; i++){
        prevResult[i] = NULL;
        delete [] prevResult[i];
    }
    prevResult = NULL;
    delete [] prevResult;
}

void GameAi::start(){
    std::string ans;
    
    bool quit = false;  //Flag for game end
    bool game = false;  //Flag for game success
    
    srand(static_cast<unsigned int>(time(0)));
    
    do{
        //Reset values
        cls();
        game = true;
        attempts = 0;
        bool input;
        
        do{
            //Reset input flag
            input = true;
            
            //Prompt user input for code
            std::cout << "Enter a 4 digit code(0-9999):";
            std::cin >> ans;
            
            //Validate code
            for(int i = 0; i < size; i++){
                if(ans[i] - '0' < -1 || ans[i]-'0' > 10 ){
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
        std::cout <<std::left <<std::setw(10) <<"Attempts"
                <<std::setw(14) <<"Guess" <<"Result\n";
        
        do{
            //Generate guess
            ai = guess(prevGuess, prevResult, attempts);
            
            //Check result
            result = check(ai, player, size);
            
            //If ai guesses correct
            if(compare(ai, player, size)){
                //Raise game flag
                game = false;
            }
            else{
                //Store guess and result
                prevGuess[attempts] = ai;
                prevResult[attempts] = result;
            }
            
            //Output ai guess
            std::cout <<"[Attempt:" <<++attempts <<"]";
            output(ai, size);
            
            //Output result
            if(attempts < 10){
                std::cout <<"\t\t";
            }
            else{  
                std::cout <<"\t";
            }
            output(result, size);
            std::cout <<std::endl;
            
        }while(attempts < tries && game == true);
        
        /*
        std::cout <<"AI Guesses========\n";
        for(int i = 0 ; i < tries; i++){
            std::cout <<"Attempt" <<i <<": ";
            output(prevGuess[i], size);
            std::cout <<"\n";
        }*/
        
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
    int* flagCode = new int[size]; //Array for confirmed code checks{0,1,2}
    int index = 0;              //Index for array
    bool correct = false;       //Flag for correct
    bool almost = false;        //Flag for correct but wrong spot
    
    int star = 0;               //Counter for correct
    int o = 0;                  //Counter for correct but wrong spot
    
    //Set flags
    for(int i = 0; i < size; i++){
        flagCode[i]=0;
    }
    

    //Check through each line of the code
    for(int i = 0; i < size; i++){
        //Reset flags
        correct = false;
        almost = false;
        
        //Check through each line of the guess 
        for(int j = 0; j < size; j++){
            
            //If the spot has not been checked and confirmed
            if(flagCode[j] < 2){
                
                //If the guess matches the code and spot
                if(j == i && code[i] == guess[j]){
                    //Raise correct flag
                    correct = true;
                    almost = false;
                    flagCode[j]= 2;
                }
                //If the guess matches the code but not the spot
                else if(!correct && code[i] == guess[j]){
                    //Raise almost flag
                    almost = true;
                    flagCode[j] = 1;
                }
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
    
    delete flagCode;

    //Return answer
    return ans;
}

char* GameAi::guess(char** prevGuess , char** result , int attempt){
    //int for number of digits
    int nums = 10; 
    //Array for ai's guess
    char* aiGuess = new char[this->size];   
    //Flag for wrong(0)/maybe(1)/good(2)values
    int* potentials = new int[nums];
    
    //Set potential flags to default: maybe
    for(int i = 0; i < nums; i++){
        potentials[i] = 1;
    }
    
    
    //If its the first guess
    if(attempt < 1){
        //Output generic start
        for(int i = 0 ; i < size; i++){
            aiGuess[i]=i+'0';
        }
    }
    else{
        //Scan through results for wrong numbers
        for(int i = 0; i < size; i++){
            bool wrong = true;
            
            //Flag if all numbers are wrong
            for(int j = 0; j < size; j++){
                if(result[i][j] != 'x'){
                    wrong = false;
                }
            }
            //If all numbers are wrong
            if(wrong){
                //Go through the guess and flag wrong numbers
                for(int j = 0 ; j < size; i++){
                    int spot = prevGuess[i][j];
                    potentials[spot] = 0;
                }
            }
        }
        
        //Make random guesses based on incorrect results
        for(int i = 0; i < size; i++){
            int num = (rand()%10)+'0';
            
            if(potentials[num]!= 0){
                aiGuess[i] = num;
            }
        }
    }
    
    
    
    //Cpu makes a random guess
    /*
    for(int i = 0; i < size; i++){
        aiGuess[i] = (rand()%10)+'0';
    }*/
    
    delete potentials;
    
    return aiGuess;
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
