/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Kauru99
 *
 * Created on March 14, 2017, 10:35 PM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

//Global Constants
enum CrdCard{
    AEXPRESS=0,
    VISA=1,
    MASTER=2,
    DISCOVER=3,
    ALL=4
};

//Function Prototypes
int genCC(CrdCard, int[]);          //Gen card function
void prpLuhn(int[],int);            //Gen credit number
void Luhn(int[],int);               //Gen Luhn number
void flipDig(int[], int);           //Flip rand digit
bool validCC(int[], int);           //Validate card
int rndDig();                       //Returns random digit
void outAry(int[],int);             //Outputs array

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    
    int card;
    const int CAP = 20;
    
    //Prompt
    cout <<left <<setw(30) <<"Credit Card"
            <<setw(24) <<"Number"
            <<setw(30) <<"Validation" <<endl;
    
    for(int i = 0; i < 10000; i ++){
        //Create array
        int cc[CAP];
        
        //Generate card type
        card = rand()%5;
        
        //Output card type
        switch(card){
            case 0:
                cout <<setw(30)<<"American Express";
                break;
                
            case 1:
                cout <<setw(30)<<"Visa";
                break;
                
            case 2:
                cout <<setw(30)<<"Master Card";
                break;
                
            case 3:
                cout <<setw(30)<<"Discover";
                break;
                
            default:
                cout <<setw(30)<<"All";
                break;
                       
        }
        
        
        
        //Generate numbers
        int size = genCC(static_cast<CrdCard>(card), cc);
        
        //Flip every other digit
        if(i%2==0){
            flipDig(cc, size);
        }
        
        outAry(cc,size);
        
        if(validCC(cc,size)){
            cout <<setw(30)<<"Valid" <<endl;
        }
        else{
            cout <<setw(30)<<"Invalid" <<endl;
        }
    }
    
    

    return 0;
}

int genCC(CrdCard cctype, int cc[]){
    int size = 0;
    if(cctype == AEXPRESS){
        size = 15;
    }
    else if(cctype == VISA){
        size = 16;
    }
    else if(cctype == MASTER){
        size = 16;
    }
    else if(cctype == DISCOVER){
        size = 16;
    }
    else if(cctype == ALL){
        size = 16;
    }
    
    
    //Create array
    int creditcard[size];
    prpLuhn(creditcard, size-1);
    Luhn(creditcard, size-1);
    
    //Copy contents
    for(int i = 0; i < size; i++){
        cc[i] = creditcard[i];
    }

    return size;
}

void prpLuhn(int cc[], int size){
    if(size>0){
        //Fill random credit card numbers
        for(int i = 0; i < size; i++){
            cc[i] = rndDig();
        }
    }
}

void Luhn(int cc[], int size){
    if(size>0){
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

        //Sum the digits
        int total = 0;
        for(int i = 0; i < size; i++){
            total += cardNum[i];
        }
        
        //Calculate check digit
        digit = (total*9)%10;

        //Insert final value to original array
        for(int i = size; i < size+1; i++){
            cc[size] = digit;
        }
    }
}

void flipDig(int cc[], int size){
    if(size>0){
        //Flip random digit
        int digit = rand()%(size-2);
        
        int temp = cc[digit];
        cc[digit] = cc[0];
        cc[0] = temp;
    }
}

bool validCC(int cc[], int size){
    bool valid = false;
    
    if(size>0){
        //Retrieve last digit
        int checkDig = cc[size];
        
        //Calc Luhn
        int cardNum[size];
        int digit=0;
        
        for(int i = 0; i < size-1; i++){
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

        //Sum the digits
        int total = 0;
        for(int i = 0; i < size-1; i++){
            total += cardNum[i];
        }

        //Calculate check digit
        digit = (total*9)%10;


        //Check digit
        if(checkDig == digit){
            valid = true;
        }
    }
    
    return valid;
}

int rndDig(){
    return rand()%10;
}

void outAry(int cc[], int size){
    if(size>0){
        for(int i = 0; i < size; i++){
            cout <<cc[i];
        }
        cout <<"\t\t";
    }
}


