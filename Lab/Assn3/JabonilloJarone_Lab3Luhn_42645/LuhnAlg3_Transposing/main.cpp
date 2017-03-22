/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on March 15, 2017, 12:57 PM
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
void flipDig(int[], int);           //Flip 2 rand digit
void transDig(int[],int);           //Transpose 2 rand digits
bool validCC(int[], int);           //Validate card
int rndDig();                       //Returns random digit
void outAry(int[],int);             //Outputs array

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    
    int card;
    int valid = 0, valid2 = 0;
    int invalid = 0, invalid2 =0;
    const int CAP = 20;
    bool flip = false;
    
    //Prompt
    cout <<left <<setw(30) <<"Credit Card"
            <<setw(30) <<"Number"
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
        
        //Flip every other number
        if(i%2==0){
            flipDig(cc, size);
            flip = true;
        }
        //Transpose others
        else{
            transDig(cc,size);
            flip = false;
        }
        
        outAry(cc,size);
        
        if(validCC(cc,size)){
            cout <<setw(30)<<"Valid" <<endl;
            if(flip){
                valid++;
            }
            else{
                valid2++;
            }
        }
        else{
            cout <<setw(30)<<"Invalid" <<endl;
            if(flip){
                invalid++;
            }
            else{
                invalid2++;
            }
        }
    }
    
    cout <<endl <<"[End results]" <<endl
            <<setw(11) <<"Flips: " 
            <<"Valid #s:" <<valid <<" Invalid #s:" <<invalid <<endl
            <<setw(10) <<"Transpose: " 
            <<"Valid #s:" <<valid2 <<" Invalid #s:" <<invalid2 <<endl;
    

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
    //Flip numbers function
    if(size>0){
        int temp[size];
        
        //Copy numbers backwards
        for(int i = 0; i <= size; i++){
            temp[i] = cc[size-i];
        }
        
        
        //Overwrite original array
        for(int i = 0; i < size; i++){
            cc[i] = temp[i+1];
        }
    }
}

void transDig(int cc[], int size){
    //Transpose digit function
    if(size>0){
        //Select 2 random digits
        int digit1 = rand()%(size-2);
        int digit2 = rand()%(size-2);
        
        //Transpose digits
        int temp = cc[digit1];
        cc[digit1] = cc[digit2];
        cc[digit2] = temp;
    }
}

bool validCC(int cc[], int size){
    bool valid = false;
    
    if(size>0){
        //Retrieve last digit
        int checkDig = cc[size-1];
        
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

        //Output both digits
        cout <<"Check#: " <<checkDig <<"; Result: " <<digit <<"; ";

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
