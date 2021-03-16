#ifndef DISJOINTSET_H
#define DISJOINTSET_H

 

#include <iostream>
#include <cstdlib>

 

class DisjointSet
{

 

    public:

 

        DisjointSet(uint32_t n);

 

        ~DisjointSet();

 

        uint32_t find(uint32_t a);

 

        void join(uint32_t a,uint32_t b);

 

    private:
        uint32_t *elements;
        uint32_t *rank;
    

 

};

 

#endif    // DISJOINTSET_H
