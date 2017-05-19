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
#include "Game.h"
#include "GameAi.h"

using namespace std;

/*
 * 
 */

void cls(); //Clear screen


int main(int argc, char** argv) {
    bool quit = false;  //Flag for game end
    
    int size = 4;   //Board size
    Game gameplay(size); //Game object
    GameAi gameplayAi(size); //Ai game object
    
    
    do{
        //User prompt
        string ans;
        cls();
        cout << "Mastermind Menu\n"
                <<"=====================\n"
                <<"1] Start new game\n"
                <<"2] Play vs AI\n"
                <<"3] Quit\n"
                <<"=====================\n"
                <<"Enter Selection: ";
        cin >> ans;
        
        //Process user input
        if(ans[0] == '1'){
            //Start normal game
            gameplay.start();
        }
        else if(ans[0] == '2'){
            //Start ai game
            gameplayAi.start();
        }
        else if(ans[0] == '3'){
            //Quit game
            quit = true;
        }
        
        cls();
    }while(!quit);
    
    cls();
    cout <<"Thank you for playing!\n";
    
    //Program end.
    return 0;
}

void cls(){
    for(int i = 0 ; i < 10; i++){
        cout <<endl;
    }
}