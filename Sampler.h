#ifndef SAMPLER_H
#define SAMPLER_H

 


#include <iostream>
#include <cstdlib>

 

class Sampler
{

 

public:
    explicit Sampler(uint32_t n);
    ~Sampler();
    
    uint32_t getSample();

 

private:
    uint32_t
        *items,
        nItems;

 

};

 

#endif    //SAMPLER_H
