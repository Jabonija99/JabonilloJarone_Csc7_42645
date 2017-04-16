/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Kauru99
 *
 * Created on April 11, 2017, 6:53 PM
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/*
 * 
 */
bool compare(char[],char[], int);
char* check(char[],char[], int);
void output(char[], int);
void cls();

int main(int argc, char** argv) {
    int size = 4;
    int tries;
    char ai[size];
    char player[size];
    char *result;
    string ans;
    
    bool quit = false;
    bool game = false;
    
    srand(static_cast<unsigned int>(time(0)));
    
    do{
        cls();
        cout << "Game start\n";
        game = true;
        tries = 10;
        
        for(int i = 0; i < size; i++){
            ai[i] = ((rand()%6)+1)+'0';
        }
        
        
        cout <<"========================================"
                <<endl <<"Key: "
                <<endl <<"[x]Incorrect color"
                <<endl <<"[o]Correct color "
                <<endl <<"[*]Correct color and spot"
                <<endl <<"========================================\n";
        
        do{
            do{

                string num;
                
                cout <<"[" <<tries <<" attempts] "
                        <<"Guess the 4 digit code(1-6):";
                cin >> num;

                for(int i = 0; i < size; i++){
                    player[i] = num[i];
                }
                
                cout <<"Confirm (y/n)?";
                cin >> ans;
            
            }while(ans[0] != 'y' && ans[0] != 'Y');
            
            if(!compare(ai, player, size)){
                tries--;
                result = check(ai, player, size);
                
                cout <<"Result:";
                output(result, size);
            }
            else{
                game = false;
            }
            
        }while(tries > 0 && game == true);
        
        
        cout <<"Answer: ";
        output(ai, size);
        
        if(game == true){
            cout <<"You lost!\n";
        }
        else{
            cout <<"You win!\n";
        }
        
        cout <<"Restart (y/n)? ";
        cin >> ans;
        
        if(ans[0] == 'n' || ans[0] == 'N'){
            quit = true;
        }
        else{
            quit = false;
        }
    
    }while(!quit);
    

    result = NULL;
    delete result;
    
    return 0;
}

void cls(){
    for(int i = 0 ; i < 10; i++){
        cout <<endl;
    }
}

bool compare(char code[], char guess[], int size){
    bool success = true;
    for(int i = 0; i < size; i++){
        if(guess[i] != code[i]){
            success = false;
        }
    }
    return success;
}

char* check(char code[], char guess[], int size){
    char* result =  new char[size]; //
    int index = 0;
    bool correct = false;
    bool almost = false;
    
    int star = 0;
    int o = 0;
    

    
    for(int i = 0; i < size; i++){
        correct = false;
        almost = false;
        
        for(int j = 0; j < size; j++){
            if(j == i && code[i] == guess[j]){
                correct = true;
                almost = false;
            }
            else if(!correct && code[i] == guess[j]){
                almost = true;
            }
        }
        
        if(correct){
            star++;
        }
        else if(almost){
            o++;
        }
    }
    
    
    for(int i = 0; i < size; i++){
        if(star > 0){
            result[i] = '*';
            star--;
        }
        else if(star < 1 && o > 0){
            result[i] = 'o';
            o--;
        }
        else{
            result[i] = 'x';
        }
    }
    
    /*
    int star = 0;  //Flag for correct
    int o = 0;     //Flag for correct but wrong
    int x = 0;     //Flag for wrong
    
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(j == i && code[i] == guess[j]){
                star++;
                j=size;
            }
            else if(j != i && code[i] == guess[j]){
                o++;
                j=size;
            }
            else if(j == 3 && code[i] != guess[j]){
                x++;
                j=size;
            }
        }
    }
    
    
    
    for(int i = 0; i < size; i++){
        if(star > 0){
            result[i] = '*';
            star--;
        }
        else if(star <=0 && o > 0){
            result[i] = 'o';
            o--;
        }
        else{
            result[i] = 'x';
        }  
    }
    */

    return result;
}

void output(char array[], int size){
    for(int i = 0; i < size; i++){
        cout <<array[i];
    }
    cout <<endl;
}