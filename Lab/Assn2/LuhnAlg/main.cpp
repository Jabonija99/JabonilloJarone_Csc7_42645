/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on March 13, 2017, 12:29 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>

enum CRDCARD{
    AEXPRESS=0,
    VISA=1,
    MASTERCRD=2,
    DISCOVER=3,
    ALL=4
};

using namespace std;


//Function prototypes
int *genCC(CRDCARD);
void flipDig(int[],int);
bool validCC(int[],int);

char rndDgit();
void prpLuhn(int[],int);
void Luhn(int[],int);
void outAry(int[],int);



int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
   
    int card = 0;
    
    cout <<"Credit Card\t\t"
            <<"Number\t\t"
            <<"Validation\n";
    
    //Loop 10,000 times
    for(int i = 0; i < 10; i++){
        card = rand()%5;
        
        cout <<"Error1\n";
        int *crdCard = genCC(static_cast<CRDCARD>(card));
        cout <<"Error2\n";
        
        int size = 0;
        if(card == AEXPRESS){
            cout<<"American Express\t\t";
            size = 15;
        }
        else if(card == VISA){
            cout <<"Visa\t\t";
            size = 16;
        }
        else if(card == MASTERCRD){
            cout <<"MasterCard\t\t";
            size = 16;
        }
        else if(card == DISCOVER){
            cout <<"Discover\t\t";
            size = 16;
        }
        else if(card == ALL){
            cout <<"ALL\t\t";
            size = 16;
        }
        cout <<"Error3\n";
        
        //Flip every other card number for varied results
        if(i%2==0){
            flipDig(crdCard, size);
        }
        cout <<"Error4\n";
        
        outAry(crdCard,size);
        cout <<"Error7\n";
        
        if(validCC(crdCard,size)){
            cout <<"Valid\n";
        }
        else{
            cout <<"Invalid\n";
        }
    }
    

    return 0;
}

int *genCC(CRDCARD card){
    int size = 0;
    if(card == AEXPRESS){
        size = 15;
    }
    else if(card == VISA){
        size = 16;
    }
    else if(card == MASTERCRD){
        size = 16;
    }
    else if(card == DISCOVER){
        size = 16;
    }
    else if(card == ALL){
        size = 16;
    }
    
    int creditcard[size];
    prpLuhn(creditcard, size-1);
    Luhn(creditcard, size-1);
    
    return creditcard;
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
    return rand()%10;
}

void Luhn(int cc[], int n){
    int cardNum[n];
    int digit=0;
    for(int i = 0; i < n; i++){
        //For every other element
        if(i%2 != 0){
            //Double the value
            int temp = cc[i]*2;
            
            //Find the digits
            int d1 = temp%10;
            int d2 = (temp-d1)/10;
            
            //Sum the digits
            cardNum[i] = d1+d2;
        }
        else{
            //Copy card contents
            cardNum[i] = cc[i];
        }
    }
    
    //Sum the values
    int total = 0;
    for(int i = 0; i < n; i++){
        total += cardNum[i];
    }
    
    //Calculate check digit
    digit = (total*9)%10;
    
    //Insert final value to original array
    for(int i = n; i < n+1; i++){
        cc[n] = digit;
    }
    
}

void outAry(int cc[], int size){
    //Output array
    for(int i = 0; i < size; i++){
        cout <<cc[i];
    }
    cout <<endl;
    
}

void flipDig(int cc[], int size){
    //Flip random digit
    int digit = rand()%size-1;
    
    cout <<"Error5\n";
    //Flip digit with first slot
    //int temp = cc[digit];
    //cc[digit] = cc[0];
    //cc[0] = temp;
    cout <<"Error6\n";
}

bool validCC(int cc[], int size){
    bool valid = false;
    
    //Retrieve last digit
    int checkdig = cc[size-1];
    
    //Calculate Luhn
    int cardNum[size];
    int digit=0;
    for(int i = 0; i < size; i++){
        //For every other element
        if(i%2 != 0){
            //Double the value
            int temp = cc[i]*2;
            
            //Find the digits
            int d1 = temp%10;
            int d2 = (temp-d1)/10;
            
            //Sum the digits
            cardNum[i] = d1+d2;
        }
        else{
            //Copy card contents
            cardNum[i] = cc[i];
        }
    }
    
    //Sum the values
    int total = 0;
    for(int i = 0; i < size; i++){
        total += cardNum[i];
    }
    
    //Calculate check digit
    digit = (total*9)%10;
    
    //Verify final digit
    if(digit == checkdig){
        valid = true;
    }

    return valid;
}