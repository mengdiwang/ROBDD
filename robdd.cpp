//
//  robdd.cpp
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-16.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include "robdd.h"

Robdd::Robdd(int k)
{
    //Clear();
    
    num_vars = k;
    limit = BDD_LIMIT;
    size = 2;
    
    T = new bddNode*[limit];
	memset(T, 0, sizeof(limit)*sizeof(bddNode*));
    T[0] = new bddNode(k+1, 0, 0);
    T[1] = new bddNode(k+1, 0, 0);
    
    H = new Thtable<bddNode, int>(BDD_HASHTABLE_SIZE, &equal, &hash);
    REQUIRES(H->IsValid());
}

Robdd::~Robdd()
{
    Clear();
}

int Robdd::Getsize()
{
    return size;
}

int Robdd::GetNumVars()
{
    return num_vars;
}

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
#ifdef DD2
        printf("MK found %d\n", *e);
#endif
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
#ifdef DD2
    printf("MK insert @%d\n", u);
#endif
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
    delete s; s = NULL;
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
            u = Mk(v2,
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
    
    Thtable<int, int> *ST =
    new Thtable<int, int>(SATCOUNT_HASHTABLE_SIZE, &sat_equal, &sat_hash);
    
    int num = Sat_rec(u, ST);
    delete ST; ST=NULL;
    return num;
}

void Robdd::AnySat(int u)
{
    REQUIRES(IsValid());
    assert(0<=u && u<size);
    assert(u != 0);
    
    if(u==0)
    {
        puts("Cannot solve");
        return;
    }
    
    bddNode *node = T[u];
    int v = node ->var;
    while(v<=num_vars)
    {
        printf("x[%d]=", v);
        if(node->low ==0)
        {
            puts("1");
            u = node->high;
        }
        else
        {
            puts("0");
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
        puts("=1");
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
        puts("Cannot solve");
        return;
    }
    
    int *arr = new int[num_vars+1];
    AllSat_rec(arr, 1, u);
    delete []arr;
    arr = NULL;
}

int Robdd::Restrict_rec(int u, int j, int b)
{
    assert(0<=u && u<size);
    
    bddNode *node = T[u];
    int v    = node->var;
    int low  = node->low;
    int high = node->high;
    if(v >  j)
        return u;
    if(v < j)
        return Mk(v, Restrict_rec(low, j, b), Restrict_rec(high, j, b));
    if(b == 0)//v==j
        return Restrict_rec(low, j, b);
    //v==j && b==1
    return Restrict_rec(high, j, b);
}

int Robdd::Restrict(int u, int j, int b)
{
    REQUIRES(IsValid());
    assert(0<=u && u<size);
    assert(0<=j && j<num_vars);//?
    
    return Restrict_rec(u, j, b);
}

void Robdd::Build(CNFExp *exp)
{
    REQUIRES(IsValid());
    assert(exp != NULL);
    
    Build_rec(exp, 1);
}

int Robdd::Build_rec(CNFExp *exp, int i)
{
#ifdef DD3
    printf("%s\n", exp->ex);
#endif
    assert(1 <= i);
    //assert((i>num_vars == exp->AllApply()));
    
    if(i > num_vars)
    {
#ifdef DD3
        printf("value:%d\n",exp->GetValue());
#endif
        return exp->GetValue();
    }
    
    CNFExp *exp0 = new CNFExp(exp->GetSize());
    exp0->CpyVal(exp->ex, exp->mystack, exp->position);
    exp0->Setvbyn(i, 0);
    
    int v0 = Build_rec(exp0, i+1);
    
    CNFExp *exp1 = new CNFExp(exp->GetSize());
    exp1->CpyVal(exp->ex, exp->mystack, exp->position);
    exp1->Setvbyn(i, 1); 
    
    int v1 = Build_rec(exp1, i+1);
    
    if(exp != NULL)
    {
        delete exp; exp = NULL;
    }
    
    return Mk(i, v0, v1);
}

void Robdd::PrintNodes()
{
    assert(T!=NULL);
    puts("--------------------------------");
    puts("|u\t|var\t|low\t|hi\t|");
    puts("--------------------------------");
    for(int i=0; i<size; i++)//TODO
    {
        if(T[i]!=NULL)
            printf("|%d\t|%d\t|%d\t|%d\t|\n", i, T[i]->var, T[i]->low, T[i]->high);
        if(i==1)
            puts("--------------------------------");
    }
    puts("--------------------------------");
}