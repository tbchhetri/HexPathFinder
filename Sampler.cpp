#include <iostream>
#include <cstdlib>
#include "Sampler.h"

 

Sampler::Sampler(uint32_t n){
    items = new uint32_t[n];
    
    nItems = n;
    
    for (int i = 0 ; i < n ; i++ ){
        items[i] = i;
    }
}

 

Sampler::~Sampler(){
    delete[] items;
}

 

uint32_t Sampler::getSample(){
    
    uint32_t
        r,
        tmp;

 

    //select random position
    r = rand() % nItems;
    
    //remember element ar that position
    tmp = items[r];

 

    //decrement n
    nItems --;

 

    //move last element intp hole left by solution
    items[r] = items[nItems];
    
    return tmp;
}
 
