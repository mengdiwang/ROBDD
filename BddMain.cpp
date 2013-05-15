//
//  BddMain.cpp
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-15.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include <iostream>
#include "bddhtable.h"
#include "bddlist.h"
#include "robdd.h"
#include <string.h>
#include <assert.h>

int andop(int b1, int b2)
{
    return b1 * b2;
}

int orop(int b1, int b2)
{
    return (b1 >= b2) ? b1 : b2;
}

int xorop(int b1, int b2)
{
    return (b1 + b2) % 2;
}

int main()
{
    int SIZE = 37;
    int *u = new int[SIZE];
    Robdd *bdd = new Robdd(2);
    u[1] = bdd->Mk(2, 0, 1);
    u[2] = bdd->Mk(1, 0, u[1]);
    bdd->AnySat(u[2]);
    
    return 0;
}
