/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Kauru99
 *
 * Created on May 26, 2017, 11:04 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include "GeneralHashFunctions.h"

using namespace std;


void pause();
bool verify(string, unsigned int, unsigned int, unsigned int);
void outResult(bool, string);
/*
 * 
 */
const int MOD = 100000;
int main(int argc, char** argv) {
    srand(time(0));
    unsigned int hash00, hash01, hash10, hash11, hash0, hash1, hashtop, hashtop2;
    
    ostringstream convert;
    
    string line1 = "Then out spake brave Horatius, The Captain of the Gate:";
    string line2 = "\"To every man upon this earth Death cometh soon or late.";
    string line3 = "And how can man die better Than facing fearful odds,";
    string line4 = "For the ashes of his fathers, And the temples of his Gods.\"";
    string linehash0, linehash1, linehashtop;
    
    
    //Hash lines
    cout <<"Hashing lines:\n";
    hash00 = FNVHash(line1)%MOD;
    hash01 = FNVHash(line2)%MOD;
    hash10 = FNVHash(line3)%MOD;
    hash11 = FNVHash(line4)%MOD;
    
    //Output resulting hashes
    cout <<"Lower Branch =================\n";
    cout <<"Hash 0-0: " <<hash00 <<endl;
    cout <<"Hash 0-1: " <<hash01 <<endl;
    cout <<"Hash 1-0: " <<hash10 <<endl;
    cout <<"Hash 1-1: " <<hash11 <<endl;
    
    //Convert hashes to string
    convert << hash00+hash01;
    linehash0 = convert.str();
    convert << hash10+hash11;
    linehash1 = convert.str();
    
    //Hash second branch
    hash0 = FNVHash(linehash0)%MOD;
    hash1 = FNVHash(linehash1)%MOD;
    cout <<"Second Branch =================\n";
    cout <<"Hash 0: " <<hash0 <<endl;
    cout <<"Hash 1: " <<hash1 <<endl;
    
    //Convert and hash top branch
    convert <<hash0+hash1;
    linehashtop = convert.str();
    hashtop = FNVHash(linehashtop)%MOD;
    cout <<"Top Branch =================\n";
    cout <<"Hash top: " <<hashtop <<"= " <<hash0 <<"+" <<hash1 <<endl <<endl;
      
    pause();
    
    bool result;
    cout <<"Verifying Positive hashes: \n";
    
    //Check each line
    result = verify(line1, hash01, hash1, hashtop);
    outResult(result, "Line Positive 1");
    
    
    result = verify(line2, hash00, hash1, hashtop);
    outResult(result, "Line Positive 2");
    
    result = verify(line3, hash11, hash0, hashtop);
    outResult(result, "Line Positive 3");
    
    result = verify(line4, hash10, hash0, hashtop);
    outResult(result, "Line Positive 4");
    
    //False lines
    
    cout <<"\nVerifying False hashes:\n";
    result = verify("Random line 1", hash01, hash1, hashtop);
    outResult(result, "Line Negative 1");
    
    result = verify("Random line 2", hash00, hash1, hashtop);
    outResult(result, "Line Negative 2");
    
    result = verify("Random line 3", hash11, hash0, hashtop);
    outResult(result, "Line Negative 3");
    
    result = verify("Random line 4", hash10, hash0, hashtop);
    outResult(result, "Line Negative 4");

    return 0;
}

bool verify(string line,unsigned int hash1,unsigned int hash2,unsigned int hashtop){
    bool positive = true;
    ostringstream convert;
    string lineConvert1, lineConvert2;
    
    //Hash and convert line
    unsigned int hash = FNVHash(line)%MOD;
    cout <<"**Hashed line: " <<hash <<endl;
    
    convert << hash+hash1;
    lineConvert1 = convert.str();
    hash = FNVHash(lineConvert1)%MOD;
    cout <<"**Hash Branch: " <<hash <<" =+ " <<hash1 <<endl;
    
    convert <<hash+hash2;
    lineConvert1 = convert.str();
    hash = FNVHash(lineConvert1)%MOD;
    cout <<"**Hash Top: " <<hash <<" =+ " <<hash2 <<endl;
    cout <<"Should == " <<hashtop <<endl;

    if(hash != hashtop){
        positive = false;
    }
    
    return positive;
}

void outResult(bool positive, string line){
    if(positive){
        cout <<line <<" is positive.\n";
    }
    else{
        cout <<line <<" is false.\n";
    }
    cout <<endl;

}

void pause(){
    unsigned int timer = 100*100;
    for(int i = timer ; i > 0; i--){
    }
}