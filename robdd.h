//
//  robdd.h
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-14.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#ifndef ROBDD_robdd__h
#define ROBDD_robdd__h

#include <stdlib.h>
#include <limits.h>
#include "bddhtable.h"
#include "caution.h"
#include "utilfunc.h"
#include "assert.h"
#include <stdio.h>

#define BDD_LIMIT (1<<20)
#define BDD_HASHTABLE_SIZE (1<<18)
#define APPLY_HASHTABLE_SIZE (1<<16)
#define SATCOUNT_HASHTABLE_SIZE (1<<10)

template class Thtable<applyMem, applyMem>;

class Robdd
{
public:
    Robdd(int k);
    
    ~Robdd();
    
    int SatCount(int u);
    int Mk(int var, int low, int high);
    int Apply(int (*op)(int t1, int t2), int u1, int u2);
    bool IsValid();
    void AnySat(int u);
    void AllSat(int u);
    int Build();
    int Restrict(int u, int j, int b);
    int Getsize();
    int GetNumVars();
private:
    int Build_rec();
    int Restrict_rec(int u, int j, int b);
    int Apply_rec(int (*op)(int t1, int t2), int u1, int u2, Thtable<applyMem, applyMem> *s);
    int Sat_rec(int u, Thtable<int, int> *st);
    void AllSat_rec(int *arr, int level, int u);
    
private:
    int size;
    int limit;
    int num_vars;
    bddNode **T;
    Thtable<bddNode, int> *H;
};




#endif /* defined(ROBDD_robdd_h) */
