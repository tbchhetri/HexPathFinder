#include <iostream>
#include <cstdlib>
#include "DisjointSet.h"
#include "Sampler.h"
#include "hexpathfinder.h"
#include "stack.h"

 


using namespace std;

 

//Algorithm 1//
//==> Sampler.h

 


//Algorithm 2
//    &
//Algorithm 3
//==> DisjointSet.h

 

 

//encoder

 

int32_t encode(int32_t r, int32_t c, int32_t d, int32_t nR, int32_t nC){
    return c + nC * (r + nR * d);
}

 

/*
//decoder

 

    c = e % nC;
    e /= nC;
    r = e % nR;
    d = e / nR;

 

 /Volumes/GHDL-0.24-2006Jul06/GHDL-0.24-2006Jul06.pkg
*/

 


int32_t
    dC[] = {0,1,1,0,-1,-1},
    dReven[] = {-1,-1,0,1,0,-1},
    dRodd[] = {-1,0,1,1,1,0};

 

int32_t
    *dR;

 

//Algorith 4//
void GenerateMaze(uint8_t maze[][MAX_COLS],uint32_t nR, uint32_t nC){
    
    uint32_t i = 0;
    
    uint32_t
        r,
        c,
        e,
        d;
    int32_t
        r2,
        c2;
    int32_t
        cell1,
        cell2;

 

    
     
    for ( r = 0 ; r < nR ; r++ ){
        for (c = 0 ; c < nC ; c++ ){
            maze[r][c] = 63;
        }
    }
    
    DisjointSet ds(nR*nC);
    Sampler sample(3*nR*nC);
    
    
    bool setFlag = true;
    while(i < ((nR*nC)-1)){
         
        do{
            
            do{
                e = sample.getSample();
                cout << e;
    
                c = e % nC;
                e /= nC;
                r = e % nR;
                d = e / nR;
                
                if ((c & 1) != 0){
                    dR = dRodd;
                }
                else{
                    dR = dReven;
                }
                
                
                
                r2 = r + dR[d];
                c2 = c + dC[d];
                
                cell1 = encode(r,c,0,nR,nC);
                cell2 = encode(r2,c2,0,nR,nC);

 


                if (((r2 >= 0) and (r2 < nR)) and ((c2 >= 0) and (c2 < nC)))
                    setFlag = false;
                else
                    setFlag = true;
            }while(setFlag);    //whiile e references an exterior or nonexixtent wall
            
        }while(ds.find(cell1) == ds.find(cell2));

 

        ds.join(cell1,cell2);
        
        i = i + 1;
        
        //Remove wall between (r1,c1) and (r2,c2)
        // 0,1,2,3,4,5   <= d
        //  (1 << d)    <= masking
        //  for (r2,c2),  d = d + 3
     
        if ((d == 0) or (d == 1) or (d == 2)){
            maze[r][c] &= ~(1 << d);
            maze[r2][c2] &= ~(1 << (d+3));
        }
    }
    
    

 

}

 

 


//Algorithm 5//
void FindPath (uint8_t maze[][MAX_COLS],uint32_t nR,uint32_t nC){
    
    Stack<int32_t> S;

 

    S.push(encode(0,0,0,nR,nC));
    maze[0][0] |= VISITED;        //Mark (0,0) as visited
    
    uint32_t e,
        r,
        c,
        d;
    
    int32_t
        r_prime,
        c_prime;
        
    
    while (true){
    
        // (r,c,d) = decode(S.peek());
        e = S.peek();

 

        //decode
        c = e % nC;
        e /= nC;
        r = e % nR;
        d = e / nR;
        
        
        if ((r == (nR - 1)) and (c == (nC - 1))){
            break;
        }

 

 

 

 

        if (d == 6){
            // Mark (r,c) as a dead end
            maze[r][c] |= DEAD_END;
            S.pop();
        }
        else{
            //Let (r',c') be the next cell direction d
            if ((c & 1) != 0){
                    dR = dRodd;
            }
            else{
                    dR = dReven;
            }
                
                    
            r_prime = r + dR[d];
            c_prime = c + dC[d];

 

            //replace encoder(r, c, d) with encoder(r, c, d+1) on top of stack
            
            S.pop();
            S.push(encode(r,c,(d+1),nR,nC));
                 
            
            //if (( no walls exists in direcction d ) and (  (r',c') is not marked as visited  )){
            if (!(maze[r][c] & (1 << d)) and !(maze[r_prime][c_prime] & VISITED)){
            
                //    S.push(encode(r',c',0));
                S.push(encode(r_prime,c_prime,0,nR,nC));
        
                //    Mark (r',c') as visited
                maze[r_prime][c_prime] |= VISITED;
            
            }
            
        }
        
    }

 

}

 

 


int main(int argc,char *argv[]){

 

 

    //initialize nR, nC
    int32_t
        nR,
        nC;
    uint8_t maze[MAX_ROWS][MAX_COLS];    //single byte integer

 

    
    

 


    
    
    // input form the command line
    if (argc != 3){
        cout << "Usage: " << argv[0] << "nRows nColumns: "<< endl;
        return 1;
    }

 

    nR = atoi(argv[1]);
    nC = atoi(argv[2]);

 

    GenerateMaze(maze,nR,nC);
    
    FindPath(maze,nR,nC);

 

    printMaze(maze,nR,nC);

 

}

 


 
