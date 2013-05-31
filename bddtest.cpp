//
//  BddMain.cpp
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-15.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include "CNFExp.h"
#include "robdd.h"
#include "bdd.h"
#include <iostream>
#include <string.h>
#include <assert.h>

void test1()
{
    int SIZE = 37;
    int *u = new int[SIZE];
    Robdd *bdd = new Robdd(2);
    
    u[1] = bdd->Mk(2, 0, 1); //u[1] = x2
    u[2] = bdd->Mk(1, 0, u[1]); //u[2] = x1 /\x2
    bdd->AnySat(u[2]);
    assert(bdd->SatCount(u[2])==1);
    
    printf("---------------------------------\n");
    
    u[3] = bdd->Apply(&xorop, u[2], 1);//u[3] = (x1/\x2)xor 1 =  ~(x1 /\ x2)
    u[4] = bdd->Apply(&andop, u[2], u[3]);//u[4] = u[2] /\ u[3] = 0
    assert(bdd->SatCount(u[4])==0);
    assert(u[4] == 0);
    printf("u[4]=%d\n", u[4]);
    printf("---------------------------------\n");
    
    u[5] = bdd->Mk(2, 0, 1);	// u[3] = x2
    u[6] = bdd->Mk(1, u[5], 1);	// u[4] = x1 \/ x2
    bdd->AnySat(u[6]);
    assert(bdd->SatCount(u[6]) == 3);
    printf("---------------------------------\n");
    
    u[7] = bdd->Mk(1, 0, 1);	// u[7] = x1
    u[8] = bdd->Mk(2, 0, 1);	// u[8] = x2
    u[9] = bdd->Apply(&andop, u[7], u[8]); 	// u[9] = x1 /\ x2
    for (int i = 1; i < 10; i++) {
        printf("u[%d] = %d\n", i, u[i]);
    }
    assert(u[9] == u[2]);
    printf("---------------------------------\n");
    
    printf("ROBDD of %d", bdd->GetNumVars());
    printf(" vars has %d nodes\n",bdd->Getsize());
    printf("passed all tests!\n");
}

void test2()
{
    const int SIZE = 37;
    int u[SIZE] = {0};
    Robdd bdd = Robdd(2);
    
    u[1] = bdd.GetIthVar(1);
    u[2] = bdd.GetIthVarNeg(2);
    if(u[1]>0 && u[2]>0)
        u[3] = bdd.bdd_and(u[1], u[2]);
    bdd.PrintNodes();
}

void test3()
{
    const int SIZE = 4;
    Robdd *base = new Robdd(SIZE);
    base->InitVars(SIZE-1);
    bdd bddlist[SIZE];
    for(int i=0; i<SIZE-1; i++)
    {
        bddlist[i].SetBase(base);
        bool ret = bddlist[i].GetIthvar(i);
        if(!ret)
        {
            printf("Error @%d",i);
            return;
        }
    }
    
    bddlist[3] = bddlist[1] &  bddlist[2] | !bddlist[0];
    //base->PrintNodes();
    base->AnySat(bddlist[3].id());
}

void test4()
{
    printf("Test boolean expression:a&b|!c\n");
    CNFExp *myexp = new CNFExp("a&b|!c");

    int valt[8] = {1,0,1,0,1,0,1,1};
    int c = 0;

    printf("-----------\n");
    printf("|a|b|c|Exp|\n");
    printf("-----------\n");
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<2; j++)
        {
            for(int k=0; k<2; k++)
            {
                myexp->ProduceStack("a&b|!c");
                myexp->Setv('a',i);
                myexp->Setv('b',j);
                myexp->Setv('c',k);
                int val = myexp->GetValue();
                printf("|%d|%d|%d| %d |\n",i,j,k,val);
                //printf("--------------------------\n");
                assert(val==valt[c]);
                c++;
            }
        }
    }
    printf("-----------\n");
    printf("All Test Pass\n");
    printf("--------------------------\n\n");
}

void test5()
{

    printf("a&b|!c build ROBDD, with a<b<c\n");
    CNFExp *texp = new CNFExp("a&b|!c");
    Robdd *bdd = new Robdd(3);
    bdd->Build(texp);
    bdd->PrintNodes();
}

void test6()
{
    const int size = 10;
    bdd x[size], s;
    Robdd *bdd = new Robdd(size+1);
    bdd->InitVars(size);
    
    for(int i=0; i<size; i++)
    {
        x[i].robdd = bdd;
        x[i].GetIthvar(i+1);
    }
    s.robdd = bdd;
    
    s = x[1] & x[2] & x[3] | x[4] |x[5] |x[6]|x[7] &x[8] &x[9] & x[0];
    
    bdd->PrintNodes(s.id());
    //bdd->AnySat(s.id());
}

void test7()
{
    Robdd *bdd = new Robdd(4);
    
    int x1 = bdd->Mk(1, 0, 1);
    int x2 = bdd->Mk(2, 0, 1);
    int x3 = bdd->Mk(3, 1, 0);
    int x4 = bdd->Apply(x1, x2, AND);
    int x5 = bdd->Apply(x4, x3, OR);
    
    bdd->PrintNodes(x5);
}

void test8()
{
    bdd x, y, z,s;
    Robdd *bdd = new Robdd(4);
    bdd->InitVars(3);
    x.robdd = bdd;
    y.robdd = bdd;
    z.robdd = bdd;
    x.GetIthvar(1);
    y.GetIthvar(2);
    z.GetIthvar(3);
    
    s.robdd = bdd;

    s = x&y|!z;
    bdd->PrintNodes(s.id());
}

int main()
{
    float duration;
    clock_t start, finish;
    
//    start = clock();
//    test8();
//    finish = clock();
//    duration = (double)(finish - start) / CLOCKS_PER_SEC *1000;
//    printf( "%f ms\n", duration);

    start = clock();
    test6();
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC *1000;
    printf( "%f ms\n", duration);

    return 0;
}
