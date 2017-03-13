/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on February 21, 2017, 8:35 AM
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
void Luhn(int[],int);
void outAry(int[],int);

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    const int SIZE=12;
    int crdCard[SIZE];
    //Prepare for Luhn encoding
    cout<<"A random number created in Prep for Luhn Digit: "<<endl;
    prpLuhn(crdCard,SIZE-2);
    //Output the preLuhn credit card
    //cout<<crdCard<<endl;
    outAry(crdCard, SIZE-2);
    
    //Now create a function that fills the last digit
    //using the Luhn Algorithm
    Luhn(crdCard,SIZE-2);
    
    cout <<"Card number with Luhn Digit: " <<endl;
    outAry(crdCard,SIZE-1);
    
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
            //cout <<"Doubled: " <<cc[i] <<" to " <<temp <<endl;
            
            //Find the digits
            int d1 = temp%10;
            int d2 = (temp-d1)/10;
            
            //Sum the digits
            cardNum[i] = d1+d2;
            //cout <<"Digit sum: " <<cardNum[i] <<endl;
        }
        else{
            //Copy card contents
            cardNum[i] = cc[i];
        }
    }
    
    //Sum the digits
    int total = 0;
    for(int i = 0; i < n; i++){
        total += cardNum[i];
    }
    //cout <<"Total sum: " <<total <<endl;
    
    //Calculate check digit
    digit = (total*9)%10;
    
    //cout <<"Final digit: " <<digit <<endl;
    
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