//
//  utilfunc.h
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-15.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#ifndef ROBDD_utilfunc_h
#define ROBDD_utilfunc_h


#include <stdio.h>
#include "caution.h"
#include <limits.h>
//typedef int int;
//typedef int int;

struct bddNode
{
    bddNode():var(0),low(0),high(0)
    {
    }
    
    bddNode(int _var, int _low, int _high)
    {
        var = _var;
        low = _low;
        high = _high;
    }
    
    int var;//!! var stated from 1
    int low;
    int high;
};


class applyMem
{
public:
    applyMem():u1(0),u2(0),u12(0)
    {
    }
    
    applyMem(int _u1, int _u2, int _u12)
    {
        u1 = _u1; u2 = _u2; u12 = _u12;
    }

    int u1;
    int u2;
    int u12;
};


/* hash function */
/* uses pseudo-random number generation */
/* use unsigned int in C to guarantee modular arithmetic */
int hash(bddNode *k, int m);

/* key comparison = node comparison */
bool equal(bddNode *k1, bddNode *k2) ;

/* key equality compares inputs, ignore output */
bool apply_equal(applyMem *ap1, applyMem *ap2) ;

/* hash functions uses pseudorandom numbers */
int apply_hash(applyMem *ap, int m);

bool int_equal(int *k1, int *k2);

int int_hash(int *k, int m);

int safe_shiftl(int n, int k);

int safe_plus(int m, int n) ;
//-----------------------------------------------------------
/* 
 
 -----------------------
|  &  |   and   | andop |
|  |  |   or    | orop  |
|  ^  |   xor   | xorop |
|  -> |  imply  | impop |
| <-> |   iff   | iffop |
 -----------------------
*/

int andop(int b1, int b2);

int orop(int b1, int b2);

int xorop(int b1, int b2);

int impop(int b1, int b2);

int iffop(int b1, int b2);


#endif
