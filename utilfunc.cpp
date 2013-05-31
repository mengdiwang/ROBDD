//
//  utilfunc.cpp
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-16.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include "utilfunc.h"
#include "stdlib.h"

/* hash function */
/* uses pseudo-random number generation */
/* use unsigned int in C to guarantee modular arithmetic */
int hash(bddNode *k, int m)
{
    REQUIRES(m > 1);
    unsigned int x = 1664525;
    unsigned int y = 1013904223;	/* inlined random number generator */
    unsigned int r = 0xdeadbeef;	/* initial seed */
    unsigned int h = (unsigned)k->var;
    r = r*x + y;		 /* mod 2^32, linear congruential random num */
    h = r*h + (unsigned)k->low;
    r = r*x + y;		 /* mod 2^32, linear congruential random num */
    h = r*h + (unsigned)k->high;
    h = h % (unsigned)m;		/* reduce to range */
    ENSURES(0 <= (int)h && (int)h < m);
    return (int)h;
}

/* key comparison = node comparison */
bool equal(bddNode *k1, bddNode *k2)
{
    return k1->var == k2->var
    && k1->low == k2->low
    && k1->high == k2->high;
}

/* key equality compares inputs, ignore output */
bool apply_equal(applyMem *ap1, applyMem *ap2)
{
    return ap1->u1 == ap2->u1 && ap1->u2 == ap2->u2;
}

/* hash functions uses pseudorandom numbers */
int apply_hash(applyMem *ap, int m)
{
    REQUIRES(m > 0);
    unsigned int x = 1664525;
    unsigned int y = 1013904223;
    unsigned int r = 0xdeadbeef;
    unsigned int h = (unsigned) ap->u1;
    r = r*x + y;
    h = r*h + (unsigned) ap->u2;
    h = h % (unsigned)m;
    return (int)h;
}

bool int_equal(int *k1, int *k2)
{
    return *k1 == *k2;
}

int int_hash(int *k, int m)
{
    REQUIRES(*k >=0 && m>0);
    return *(int *)k % m;
}

int safe_shiftl(int n, int k)
{
    REQUIRES(n >= 0 && k >= 0);
    if ((n > 0 && k >= (int)sizeof(int)*8)
        || n > (INT_MAX>>k))
    {
        fprintf(stderr, "integer overflow %d << %d\n", n, k);
        abort();
    }
    return n<<k;
}

int safe_plus(int m, int n)
{
    REQUIRES(m >= 0 && n >= 0);
    if (n > INT_MAX-m)
    {
        fprintf(stderr, "integer overflow %d + %d\n", m, n);
        abort();
    }
    return m+n;
}
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

int impop(int b1, int b2)
{
    return b1 == 1 ? b2 : 1;
}

int iffop(int b1, int b2)
{
    return (b1==b2)?1:0;
}