//
//  nqueen.h
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-16.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#ifndef ROBDD_nqueen_h
#define ROBDD_nqueen_h

#include "robdd.h"
#include "utilfunc.h"

class Nqueen
{
public:
    Nqueen(int asize)
    {
        Clear();
        size = asize;
        robdd = new Robdd(size*size);
    }
    
    ~Nqueen()
    {
        Clear();
    }
    
    int BuildQueen();
    Robdd* GetBdd()
    {
        return robdd;
    }
    
private:
    void Clear()
    {
        if(robdd == NULL)
        {
            delete robdd;
            robdd = NULL;
        }
        size = 0;
    }
    
private:
    int size;
    Robdd *robdd;
    
    
};

#endif
