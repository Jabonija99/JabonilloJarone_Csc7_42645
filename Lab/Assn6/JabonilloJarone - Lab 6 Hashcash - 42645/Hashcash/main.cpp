/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on May 15, 2017, 12:46 PM
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <sstream>

#include "GeneralHashFunctions.h"

using namespace std;


unsigned int hashing(int, string);
string hashname(int);

void cls();
/*
 * 
 */
int main(int argc, char** argv) {
    //Set random seed
    srand(static_cast<unsigned int>(time(0)));
    //Create random number
    int originalNum = rand();
    //message to convert
    string msg = "Random sentence makes no difference.";
    //Number of loops
    int power = 8;
    unsigned int endLoop = pow(10, power);
    
    //Frequency of hashes and resulting value
    int freq, result;
    
    //Go through all hashes
    for(int i = 0; i < 11; i++){
    
        //Reset random number
        int randNum = originalNum;
        //Reset Frequency
        freq = 0;
        //Record start time
        int strTime = time(0);

        //Loop until desired value is reached
        do{
            //Create concatenation of original message
            ostringstream convert;
            convert << randNum++;
            string strRnd = convert.str();
            string newMsg = msg+strRnd;

            //Hash string
            result = hashing(i, newMsg);
            freq++;
        }while(result>endLoop);

        //Record end time
        int endTime = time(0);

        string hash = hashname(i);
        cout <<"======" <<hash <<"==================================\n";
        cout <<"Total time: " <<endTime-strTime <<" seconds\n";
        cout <<"Total hashes: " <<freq <<endl;
        cout <<"Total zeroes: " <<10 - power <<endl;
        cout <<"Resulting hash: " <<result <<endl;
    
    }
    
    return 0;
}

unsigned int hashing(int selection, string msg){
    unsigned int hash;
    switch(selection){
        case 0:
            hash = RSHash(msg);
            break;
            
        case 1:
            hash = JSHash(msg);
            break;
            
        case 2:
            hash = PJWHash(msg);
            break;
            
        case 3:
            hash = ELFHash(msg);
            break;
            
        case 4: 
            hash = BKDRHash(msg);
            break;
            
        case 5:
            hash = SDBMHash(msg);
            break;
            
        case 6:
            hash = DJBHash(msg);
            break;
            
        case 7:
            hash = DEKHash(msg);
            break;
            
        case 8:
            hash = BPHash(msg);
            break;
            
        case 9:
            hash = FNVHash(msg);
            break;
            
        default:
            hash = APHash(msg);
            break;
    }
    
    return hash;
}

string hashname(int selection){
    string hash;
    switch(selection){
        case 0:
            hash = "RSHash";
            break;
            
        case 1:
            hash = "JSHash";
            break;
            
        case 2:
            hash = "PJWHash";
            break;
            
        case 3:
            hash = "ELFHash";
            break;
            
        case 4: 
            hash = "BKDRHash";
            break;
            
        case 5:
            hash = "SDBMHash";
            break;
            
        case 6:
            hash = "DJBHash";
            break;
            
        case 7:
            hash = "DEKHash";
            break;
            
        case 8:
            hash = "BPHash";
            break;
            
        case 9:
            hash = "FNVHash";
            break;
            
        default:
            hash = "APHash";
            break;
    }
    
    return hash;

}

void cls(){
    for(int i = 10; i > 0; i--){
        cout <<endl;
    }
}