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
#include <stdio.h>
#include <assert.h>

#include "bddhtable.h"
#include "caution.h"
#include "utilfunc.h"
#include "CNFExp.h"

#define BDD_LIMIT (1<<20)
#define BDD_HASHTABLE_SIZE (1<<18)
#define APPLY_HASHTABLE_SIZE (1<<16)
#define SATCOUNT_HASHTABLE_SIZE (1<<10)
#define OPERATOR_NUM    11

//buddy, to make mark cout for print table
#define MARKON   0x200000    /* Bit used to mark a node (1) */
#define MARKOFF  0x1FFFFF    /* - unmark */
#define UNMARKp(p)  (node->mark &= MARKOFF)
#define MARKEDp(p)  (node->mark & MARKON)

//template class Thtable<applyMem, applyMem>;
enum Operator
{
    AND     = 0,
    XOR     = 1,
    OR      = 2,
    NAND    = 3,
    NOR     = 4,
    IMPL    = 5,
    BiImpl  = 6,
    GT      = 7,
    LT      = 8,
    InvIMPL = 9,
    NOT     = 10,
};


static int oprres[OPERATOR_NUM][4] =
{
    {0,0,0,1},  /* and                       ( & )         */
    {0,1,1,0},  /* xor                       ( ^ )         */
    {0,1,1,1},  /* or                        ( | )         */
    {1,1,1,0},  /* nand                                    */
    {1,0,0,0},  /* nor                                     */
    {1,1,0,1},  /* implication               ( >> )        */
    {1,0,0,1},  /* bi-implication                          */
    {0,0,1,0},  /* difference /greater than  ( - ) ( > )   */
    {0,1,0,0},  /* less than                 ( < )         */
    {1,0,1,1},  /* inverse implication       ( << )        */
    {1,1,0,0}   /* not                       ( ! )         */
};

class Robdd
{
public:
    Robdd(int k);
    Robdd(int nodesize, int cachesize);
    
    ~Robdd();
    
    int SatCount(int u);
    int Mk(int var, int low, int high);
    int Apply(int (*op)(int t1, int t2), int u1, int u2);
    bool IsValid();
    void AnySat(int u);
    void AllSat(int u);
    void Build(CNFExp *exp);
    int Restrict(int u, int j, int b);
    int Getsize();
    int GetNumVars();
    int Apply(int u1, int u2, Operator op);
    int Not(int u1);
    void InitVars(int num);

    
    int bdd_and(int u1, int u2);
    int bdd_xor(int u1, int u2);
    int bdd_or(int u1, int u2);
    int bdd_nand(int u1, int u2);
    int bdd_nor(int u1, int u2);
    int bdd_impl(int u1, int u2);
    int bdd_bimpl(int u1, int u2);
    int bdd_gt(int u1, int u2);
    int bdd_lt(int u1, int u2);
    int bdd_inimpl(int u1, int u2);
    int bdd_not(int u1, int u2);
    
    int GetIthVar(int var)
    {
        if(1<=var && var<=num_vars)
            return varset[var<<1];
        return -1;
    }
    
    int GetIthVarNeg(int var)
    {
        if(1<=var && var<=num_vars)
            return varset[(var<<1)+1];
        return -1;
    }

    void Clear()
    {
        for(int i=0; i<size; i++)
        {
            if(T!=NULL && T[i]!=NULL)
            {
                delete T[i];
                T[i] = NULL;
            }
            delete []T; T = NULL;
            delete H; H = NULL;
        }
        
        if(varset !=NULL)
        {
            delete[] varset; varset = NULL;
        }
    }
    
    void PrintNodes();
    void PrintNodes(int idx);
private:
    int Build_rec(CNFExp *exp, int i);
    int Restrict_rec(int u, int j, int b);
    int Apply_rec(int (*op)(int t1, int t2), int u1, int u2, Thtable<applyMem, applyMem> *s);
    int Apply_rec(int u1, int u2, Operator op, Thtable<applyMem, applyMem> &s);
    int Sat_rec(int u, Thtable<int, int> *st);
    void AllSat_rec(int *arr, int level, int u);
    int Not_rec(int u1, Thtable<int, int> &s);
    void MarkNodes(int idx);
    void UnmarkNodes(int idx);
    
private:
    int size;
    int limit;
    int num_vars;
    int *varset;
    bddNode **T;
    Thtable<bddNode, int> *H;
};

#endif /* defined(ROBDD_robdd_h) */
