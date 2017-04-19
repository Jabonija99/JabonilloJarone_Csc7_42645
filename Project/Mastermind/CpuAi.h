/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CpuAi.h
 * Author: rcc
 *
 * Created on April 19, 2017, 1:13 PM
 */

#ifndef CPUAI_H
#define CPUAI_H

class CpuAi {
private:
    char* code;
    char** guesses;
    int size;
    int tries;
    
    int correct;
    int almost;
    int wrong;
public:
    CpuAi(int);
    
    void setCode(char[]);
    bool compare();
    void dumpTable();
    
    

};

#endif /* CPUAI_H */

