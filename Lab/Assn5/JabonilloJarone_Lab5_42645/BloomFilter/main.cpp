/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on April 26, 2017, 12:49 PM
 */

#include <iostream>
#include <fstream>
#include <cmath>

#include "GeneralHashFunctions.h"

using namespace std;

void bloomfilter1(string[], int);
void bloomfilter2(string[], int);
void cls();
void pause();

/*
 * 
 */
int main(int argc, char** argv) { 
    //File and array of words
    int wordsize = 200;
    string words[wordsize];
    ifstream fileWord;
    
    //Open and read file
    fileWord.open("words.txt");
    for(int i = 0 ; i < wordsize; i++){
        fileWord >> words[i];
    }
    
    //Prompt menu
    bool quit = false;
    while(!quit){
        string ans;
        cout <<"Bloom filter examples:\n"
                <<"===========================\n"
                <<"1] 750 bit vector & 10 hashes\n"
                <<"2] 800 bit vector & 2 hashes\n"
                <<"3] Exit\n"
                <<"===========================\n"
                <<"Enter: ";
        cin >> ans;

        if(ans[0] == '1'){   
            bloomfilter1(words, wordsize);
            cls();
        }
        else if(ans[0] == '2'){   
            bloomfilter2(words, wordsize);
            cls();
        }
        else if(ans[0] == '3'){   
            quit = true;
        }
    }     
    
    //Close file
    fileWord.close();
    
    //Exit
    return 0;
}

void bloomfilter1(string words[], int wordsize){
    //Declare a variable array
    int nBits=750;
    const int SIZE=nBits/8+1;
    char bitVec[SIZE]={};
    
    //Array and number of hashes
    int hashsize = 10;
    int hashes[hashsize]={};
     
    //Number of positive results
    int numResult = wordsize/2;
    
    //Hash the first 100 words
    for(int i = 0; i < numResult; i++){
        hashes[0] = RSHash(words[i])%nBits;
        hashes[1] = JSHash(words[i])%nBits;
        hashes[2] = PJWHash(words[i])%nBits;
        hashes[3] = ELFHash(words[i])%nBits;
        hashes[4] = BKDRHash(words[i])%nBits;
        hashes[5] = SDBMHash(words[i])%nBits; 
        hashes[6] = DJBHash(words[i])%nBits;
        hashes[7] = DEKHash(words[i])%nBits;
        hashes[8] = FNVHash(words[i])%nBits;
        hashes[9] = BPHash(words[i])%nBits;
        
        //Set all bits in array
        for(int j = 0; j < hashsize; j++){
            //What bit to set?
            int bitSet=hashes[j];

            //What element is that in the array?
            int byte=bitSet/8;
            int bit=bitSet%8;

            //Now set that bit
            bitVec[byte]|=1<<bit;
        }
    }
    
    //Hash and check all 200 words
    bool positive;
    int pos = 0;
    int neg = 0;
    
    for(int i = 0; i < wordsize; i++){
        positive = true;
        
        hashes[0] = RSHash(words[i])%nBits;
        hashes[1] = JSHash(words[i])%nBits;
        hashes[2] = PJWHash(words[i])%nBits;
        hashes[3] = ELFHash(words[i])%nBits;
        hashes[4] = BKDRHash(words[i])%nBits;
        hashes[5] = SDBMHash(words[i])%nBits; 
        hashes[6] = DJBHash(words[i])%nBits;
        hashes[7] = DEKHash(words[i])%nBits;
        hashes[8] = FNVHash(words[i])%nBits;
        hashes[9] = BPHash(words[i])%nBits;
        
        //Check each hash
        for(int j = 0; j < hashsize; j++){
            //What bit to set?
            int bitSet=hashes[j];

            //What element is that in the array?
            int byte=bitSet/8;
            int bit=bitSet%8;

            //Check and see if the bit got set
            bool set=(bitVec[byte]>>bit)&1;
            
            //If the bit was not set
            if(!set){
                //Flag negative
                positive = false;
            }
        }
 
        //Output result
        if(positive){
            cout <<"Word [" <<i <<"] = Positive!\n";
            pos++;
        }
        else{
            cout <<"Word [" <<i <<"] = Negative!\n";
            neg++;
        }      
    }
    
    cout <<"\nResult:\n"
            <<"Positives [" <<pos <<"/" <<wordsize <<"]\n"
            <<"Negatives [" <<neg <<"/" <<wordsize <<"]\n";
    
    pause();
}

void bloomfilter2(string words[], int wordsize){
    //Declare a variable array
    int nBits=800;
    const int SIZE=nBits/8+1;
    char bitVec[SIZE]={};
    
    //Array and number of hashes
    int hashsize = 2;
    int hashes[hashsize]={};
     
    //Number of positive results
    int numResult = wordsize/2;
    
    //Hash the first 100 words
    for(int i = 0; i < numResult; i++){
        hashes[0] = RSHash(words[i])%nBits;
        hashes[1] = FNVHash(words[i])%nBits;
        
        //Set all bits in array
        for(int j = 0; j < hashsize; j++){
            //What bit to set?
            int bitSet=hashes[j];

            //What element is that in the array?
            int byte=bitSet/8;
            int bit=bitSet%8;

            //Now set that bit
            bitVec[byte]|=1<<bit;
        }
    }
    
    //Hash and check all 200 words
    bool positive;
    int pos = 0;
    int neg = 0;
    
    for(int i = 0; i < wordsize; i++){
        positive = true;
        
        hashes[0] = RSHash(words[i])%nBits;
        hashes[1] = FNVHash(words[i])%nBits;
        
        //Check each hash
        for(int j = 0; j < hashsize; j++){
            //What bit to set?
            int bitSet=hashes[j];

            //What element is that in the array?
            int byte=bitSet/8;
            int bit=bitSet%8;

            //Check and see if the bit got set
            bool set=(bitVec[byte]>>bit)&1;
            
            //If the bit was not set
            if(!set){
                //Flag negative
                positive = false;
            }
        }
 
        //Output result
        if(positive){
            cout <<"Word [" <<i <<"] = Positive!\n";
            pos++;
        }
        else{
            cout <<"Word [" <<i <<"] = Negative!\n";
            neg++;
        }
    }
    
    cout <<"\nResult:\n"
            <<"Positives [" <<pos <<"/" <<wordsize <<"]\n"
            <<"Negatives [" <<neg <<"/" <<wordsize <<"]\n";
    
    pause();
}


void cls(){
    //Pseudo clear screen
    for(int i = 0 ; i < 20; i++){
        cout <<endl;
    }
}

void pause(){
    //Pauses screen and waits for response
    string ans;
    cout <<endl <<"Enter anything to return to menu: ";
    cin >> ans;
}