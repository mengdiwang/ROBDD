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
    Nqueen(int size)
    {
        robdd = new Robdd(size);
    }
    
    ~Nqueen()
    {
        if(robdd == NULL)
        {
            delete robdd;
            robdd = NULL;
        }
    }
    
private:
    Robdd *robdd;
    
};

#endif
