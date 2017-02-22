/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on February 22, 2017, 11:30 AM
 */
//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Global Constants

//Function Prototypes
char rndDgit();
void prpLuhn(int[],int);
bool Luhn(int[],int);
void outA(int[],int);

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    const int SIZE=12;
    int crdCard[SIZE];
    //Prepare for Luhn encoding
    cout<<"A random number created in Prep for Luhn Digit:"<<endl;
    prpLuhn(crdCard,SIZE-2);
    //Output the preLuhn credit card
    cout<<crdCard<<endl;
    //Now create a function that fills the last digit
    //using the Luhn Algorithm
    cout<<"The random number with Luhn Encoding: "<<endl;
    
    //Calculate Luhn digit
    if(Luhn(crdCard, SIZE-2)){   
        cout <<"Error: Invalid Card Number!\n"; 
    }
    else{
        cout <<crdCard <<endl;
    }
    
    //Exit Stage Right
    return 0;
}

void prpLuhn(int cc[],int n){
    //Create a random cc in prep for Luhn checksum
    for(int i=0;i<n;i++){
        cc[i]=rndDgit();
    }
    //Put null terminator at the end
    for(int i=n;i<=n+1;i++){
        cc[i]='\0';
    }
}

char rndDgit(){
    return rand()%10+48;
}

bool Luhn(int cc[], int size){
    int card[size];
    bool error = false;
    
    //Copy array contents
    for(int i = 0; i < size; i++){
        card[i]=cc[i];
    }
    
    //Calculate every other value
    for(int i = 0; i < size; i++){
        if(i%2!=0){
            int num = card[i];
            num *= 2;
            
            if(num >= 10){
                int d1, d2;
                d1 = num%10;
                d2 = num-(d1*10);
                num = d1+d2;
            }
            
            card[i]=num;
        }
    }
    
    //Sum digits
    int total = 0;
    for(int i = 0; i < size; i++){
        total += card[i];
    }
    
    //Multiply & mod
    total *=9;
    total %=10;
    
    //Check answer
    int ans = 0;
    int d1 = total%10;
    int d2 = total -(d1*10);
    ans = d2;
    
    //if(total !=0){
       // error = true;
    //}else{
        cc[size+1] = ans;
        cc[size+2] = '\0';
    //}
    
    return error;
}

