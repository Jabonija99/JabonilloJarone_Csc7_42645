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

#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    //Declare a variable array
    int nBits=1000;
    const int SIZE=nBits/8+1;
    char bitVec[SIZE]={};
    
    //What bit to set?
    int bitSet=302;
    
    //What element is that in the array?
    int byte=bitSet/8;
    int bit=bitSet%8;
    
    //Now set that bit
    bitVec[byte]|=1<<bit;
    
    //Check and see if the bit got set
    bool set=(bitVec[byte]>>bit)&1;
    
    //Print the result
    cout<<"The number of bits in the array = "<<nBits<<endl;
    cout<<"The size of the byte array = "<<SIZE<<endl;
    cout<<"The bit to set = "<<bitSet<<endl;
    cout<<"The byte = "<<byte<<endl;
    cout<<"The bit  = "<<bit<<endl;
    cout<<"The value of 2^"<<bit<<" = "<<pow(2,bit)<<endl;
    cout<<"The value of the bitVec = "
            <<static_cast<int>(bitVec[byte])<<endl;
    if(set)cout<<"The bit was set"<<endl;
    
    //Exit
    return 0;
}

