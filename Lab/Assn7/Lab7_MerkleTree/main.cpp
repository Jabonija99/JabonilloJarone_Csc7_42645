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
int main(int argc, char** argv) {
    unsigned int hash00, hash01, hash10, hash11, hash0, hash1, hashtop;
    
    ostringstream convert;
    
    string line1 = "Then out spake brave Horatius, The Captain of the Gate:";
    string line2 = "\"To every man upon this earth Death cometh soon or late.";
    string line3 = "And how can man die better Than facing fearful odds,";
    string line4 = "For the ashes of his fathers, And the temples of his Gods.\"";
    string linehash0, linehash1, linehashtop;
    
    //Hash lines
    cout <<"Hashing lines:\n";
    hash00 = JSHash(line1);
    hash01 = JSHash(line2);
    hash10 = JSHash(line3);
    hash11 = JSHash(line4);
    
    //Output resulting hashes
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
    hash0 = JSHash(linehash0);
    hash1 = JSHash(linehash1);
    cout <<"Hash 0: " <<hash0 <<endl;
    cout <<"Hash 1: " <<hash1 <<endl;
    
    //Convert and hash top branch
    convert <<hash1+hash0;
    linehashtop = convert.str();
    hashtop = JSHash(linehashtop);
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
    string lineConvert;
    
    //Hash and convert line
    unsigned int hash = JSHash(line);
    cout <<"**Hashed line: " <<hash <<endl;
    
    convert << hash+hash1;
    lineConvert = convert.str();
    hash = JSHash(lineConvert);
    cout <<"**Hash Branch: " <<hash <<" =+ " <<hash1 <<endl;

    
    convert <<hash+hash2;
    lineConvert = convert.str();
    hash = JSHash(lineConvert);
    cout <<"**Hash Top: " <<hash <<" =+ " <<hash2 <<endl;

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

}

void pause(){
    unsigned int timer = 100*100;
    for(int i = timer ; i > 0; i--){
    }
}