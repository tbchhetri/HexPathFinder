//
//  disjointset.cpp
//  HexPathfinderProject
//
//  Created by Saagar Chhetri on 5/5/20.
//  Copyright © 2020 Tek Chhetri. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include "DisjointSet.h"

 


/*
 create elements and rank arrays, each with n elements.
 Initialize elements[i]=i nd rank[i]=0 for all slots
*/
DisjointSet::DisjointSet(uint32_t n){
        elements = new uint32_t[n];
        rank = new uint32_t[n];
        
        for ( int i = 0 ; i < n ; i++){
            elements[i] = i;
            rank[i] = 0;
        }
    }

 

/* Delete the arrays */
DisjointSet::~DisjointSet(){
    delete[] elements;
    delete[] rank;
}

 

/* Performs Algorithm 3 to find the top of the intree containing a. */
uint32_t DisjointSet::find(uint32_t a){
    if (elements[a] != a){
        elements[a]= find(elements[a]);
    }
    return elements[a];
}

 

/*Performs Algorithm 2 to join a's and b's sets together. */
void DisjointSet::join(uint32_t a,uint32_t b){
    a = find(a);
    b = find(b);

    if ( a != b ){
        if (rank[a] < rank[b]){
            elements[a] = b;
        }
        else{
            if (rank[a] == rank[b]){
                rank[a] = rank[a]+1;
            }
            
                elements[b] = a;
            
        }
    }
}
