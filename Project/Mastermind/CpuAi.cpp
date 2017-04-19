/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CpuAi.cpp
 * Author: rcc
 * 
 * Created on April 19, 2017, 1:13 PM
 */

#include "CpuAi.h"

CpuAi::CpuAi(int size) {
    correct = 0;
    almost = 0;
    wrong = 0;
    
    tries = 10;
    this->size = size;
    
    guesses = new char*[tries];
    
    for(int i = 0; i < tries; i++){
        guesses[i] = new char[this->size];
    }
    
    code = new char[this->size];
}

void CpuAi::setCode(char code[]){
    for(int i = 0 ; i < size; i++){
        this->code[i] = code[i];
    }
}





