//
//  robdd.h
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-14.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#ifndef __ROBDD__robdd__
#define __ROBDD__robdd__

#include <stdlib.h>
#include <limits.h>
#include "bddhtable.h"
#include "caution.h"
#include "utilfunc.h"

#define BDD_LIMIT (1<<20)
#define BDD_HASHTABLE_SIZE (1<<18)
#define APPLY_HASHTABLE_SIZE (1<<16)
#define SATCOUNT_HASHTABLE_SIZE (1<<10)

class Robdd
{
public:
    Robdd(int k)
    {
        num_vars = k;
        limit = BDD_LIMIT;
        size = 2;
        
        T = new bddNode*[limit];
        T[0] = new bddNode(k+1, 0, 0);
        T[1] = new bddNode(k+1, 0, 0);
    
        H = new Thtable<bddNode, int>(BDD_HASHTABLE_SIZE, &equal, &hash);
        REQUIRES(H->IsValid());
    }
    
    ~Robdd()
    {
        for(int i=0; i<size; i++)
        {
            if(T[i]!=NULL)
            {
                delete T[i];
                T[i] = NULL;
            }
            delete []T;
            delete H;
        }
    }
    
    int SatCount(int u);
    int Mk(int var, int low, int high);
    int Apply(int (*op)(int t1, int t2), int u1, int u2);
    bool IsValid();
    void AnySat(int u);
    void AllSat(int u);
    int Getsize()
    {
        return size;
    }
    
private:
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

bool Robdd::IsValid()
{
    if(size<0 || size >= limit) return false;
    if(num_vars>INT_MAX-1) return false;
    for(int i=0; i<size; i++)
    {
        bddNode *a = T[i];
        int v = a->var;
        int k = num_vars;
        if (!((i == 0 && v == k+1)    /* represents 0; var field is k+1 */
              || (i == 1 && v == k+1) /* represents 1; var field is k+1 */
              || (i >= 2 && 1 <= v && v <= k))) /* other vars in [1..k] */
            return false;
        if(i>=2)
        {
            if(!(0<=a->low && a->low<size
                 && 0<=a->high && a->high <size
                 && T[a->low] != NULL && T[a->high]!=NULL
                 && T[a->low]->var>v && T[a->high]->var > v))
                return false;
            
            int *e = H->search(a);
            if(!(e!=NULL && T[*e]==a))
                return false;
        }
    }
    return true;
}

int Robdd::Mk(int var, int low, int high)
{
    REQUIRES(IsValid());
    assert(1 <= var && var <= num_vars);
    assert(0 <= low && low < size);
    assert(0 <= high && high < size);
    
    if(low == high) return low;
    
    //new node
    bddNode *tmp = new bddNode(var, low, high);
    int *e = H->search(tmp);
    //search node in the table T
    if(e != NULL)
    {
        delete tmp; tmp = NULL;
        return *e;
    }
    //out of limit
    if(size >= limit)
    {
        fprintf(stderr, "ran out of space in BDD array of size %d\n", limit);
        abort();
    }
    //insert new node into bdd
    int u = size;
    T[u] = tmp;
    size ++;
    //e == NULL insert into hash table
    e = new int;
    *e = u;
    H->insert(tmp, e);
    
    ENSURES(IsValid());
    ENSURES(0 <= u && u < size);
    
    return u;
}

int Robdd::Apply(int (*op)(int t1, int t2), int u1, int u2)
{
    REQUIRES(IsValid());
    assert(0 <= u1 && u1 < size);
    assert(0 <= u2 && u2 < size);
    Thtable<applyMem, applyMem> *s = new Thtable<applyMem, applyMem>(APPLY_HASHTABLE_SIZE, &apply_equal, &apply_hash);
    int u = Apply_rec(op, u1, u2, s);
    delete s;
    return u;
}

//in the hash table <<u1,u2,u12>, <u1,u2,u12>>
//also it can be <<u1, u2>, u12>
int Robdd::Apply_rec(int (*op)(int t1, int t2), int u1, int u2, Thtable<applyMem, applyMem> *s)
{
    REQUIRES(0 <= u1 && u1 < size);
    REQUIRES(0 <= u2 && u2 < size);
    REQUIRES(op != NULL);
    
    if(u1 <= 1 && u2 <= 1)
    {
        return (*op) (u1, u2);
    }
    else
    {
        //G(u1, u2);
        applyMem *ap = new applyMem(u1, u2, 0);
        applyMem *aps = s->search(ap);
        if(aps != NULL) //already computed
        {
            delete ap; ap = NULL;
            return aps->u12;
        }
        
        int u;
        int v1 = T[u1]->var;
        int v2 = T[u2]->var;
        if(v1 == v2)
        {
            u = Mk(v1,
                   Apply_rec(op, T[u1]->low, T[u2]->low, s),
                   Apply_rec(op, T[u1]->high, T[u2]->high, s));
        }
        else if(v1 < v2)
        {
            u = Mk(v1,
                   Apply_rec(op, T[u1]->low, u2, s),
                   Apply_rec(op, T[u1]->high, u2, s));
        }
        else
        {
            u = Mk(v1,
                   Apply_rec(op, u1, T[u2]->low, s),
                   Apply_rec(op, u1, T[u2]->high, s));
        }
        
        ap->u12 = u;
        s->insert(ap, ap);
        
        REQUIRES(IsValid());
        REQUIRES(0 <= u && u < size);
        return u;
    }
}

int Robdd::Sat_rec(int u, Thtable<int, int> *st)
{
    assert(0<=u && u<size);
    
    if(u==0) return 0;
    if(u==1) return 1;
    
    int *sc = st->search(&u);
    if(sc != NULL) return *sc;
    bddNode *node = T[u];
    int v = node->var;
    int low = node->low;
    int high = node->high;
    
    int count_low = safe_shiftl(Sat_rec(low, st), T[low]->var-v-1);
    int count_high = safe_shiftl(Sat_rec(high, st), T[high]->var-v-1);
    
    int count = safe_plus(count_low, count_high);
    
    int *cptr = new int;
    int *uptr = new int;
    *uptr = u;
    *cptr = count;
    st->insert(uptr, cptr);
    return count;
}

int Robdd::SatCount(int u)
{
    REQUIRES(IsValid());
    assert(0 <=u && u<size);
    
    Thtable<int, int> *ST = new Thtable<int, int>(
                                                  SATCOUNT_HASHTABLE_SIZE, &sat_equal, &sat_hash);
    
    int num = Sat_rec(u, ST);
    delete ST;
    return num;
}

void Robdd::AnySat(int u)
{
    REQUIRES(IsValid());
    assert(0<=u && u<size);
    assert(u != 0);
    
    if(u==0)
    {
        printf("Cannot solve\n");
        return;
    }
    
    bddNode *node = T[u];
    int v = node ->var;
    while(v<=num_vars)
    {
        printf("x[%d]=", v);
        if(node->low ==0)
        {
            printf("1\n");
            u = node->high;
        }
        else
        {
            printf("0\n");
            u = node->low;
        }
        node = T[u];
        v = node->var;
    }
    return;
}

void Robdd::AllSat_rec(int *arr, int level, int u)
{
    assert(0<=u && u<size);
    bddNode *node = T[u];
    int v = node->var;
    while(level < v)
    {
        arr[level] = -1;
        level ++;
    }
    
    REQUIRES(level == v);
    
    if(u==1)
    {
        for (int i = 1; i < level; i++)
            if (arr[i] < 0) printf(".");
            else printf("%d", arr[i]);
        printf("=1\n");
        return;
    }
    if(node->low != 0)
    {
        arr[v] = 0;
        AllSat_rec(arr, v+1, node->low);
    }
    if(node->high != 0)
    {
        arr[v] = 1;
        AllSat_rec(arr, v+1, node->high);
    }
    
    return;
    
}

void Robdd::AllSat(int u)
{
    REQUIRES(IsValid());
    assert(0<=u && u<size);
    if(u==0)
    {
        printf("Cannot solve\n");
        return;
    }
    
    int *arr = new int[num_vars+1];
    AllSat_rec(arr, 1, u);
    delete []arr;
}


#endif /* defined(__ROBDD__robdd__) */
