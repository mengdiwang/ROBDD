//
//  main.cpp
//  testCNF
//
//  Created by Mengdi Wang on 13-5-16.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include <iostream>
#include "CNFExp.h"
#include "robdd.h"

int main(int argc, const char * argv[])
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
    
    printf("a&b|!c build ROBDD, with a<b<c\n");
    CNFExp *texp = new CNFExp("a&b|!c");
    Robdd *bdd = new Robdd(3);
    bdd->Build(texp);
    bdd->PrintNodes();
}

