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
#include <time.h>
#include <stdio.h>
#include <fstream>

int main(int argc, const char * argv[])
{
//    printf("Test boolean expression:a&b|!c\n");
//    CNFExp *myexp = new CNFExp("a&b|!c");
//    
//    int valt[8] = {1,0,1,0,1,0,1,1};
//    int c = 0;
//    
//    printf("-----------\n");
//    printf("|a|b|c|Exp|\n");
//    printf("-----------\n");
//    for(int i=0; i<2; i++)
//    {
//        for(int j=0; j<2; j++)
//        {
//            for(int k=0; k<2; k++)
//            {
//                myexp->ProduceStack("a&b|!c");
//                myexp->Setv('a',i);
//                myexp->Setv('b',j);
//                myexp->Setv('c',k);
//                int val = myexp->GetValue();
//                printf("|%d|%d|%d| %d |\n",i,j,k,val);
//                //printf("--------------------------\n");
//                assert(val==valt[c]);
//                c++;
//            }
//        }
//    }
//    printf("-----------\n");
//    printf("All Test Pass\n");
//    printf("--------------------------\n\n");
//    
//    
//    printf("a&b|!c build ROBDD, with a<b<c\n");
//    CNFExp *texp = new CNFExp("a&b|!c");
//    Robdd *bdd = new Robdd(3);
//    bdd->Build(texp);
//    bdd->PrintNodes();
    
    if(argc < 2)
    {
        printf("Usage: <input>\n");
        return 1;
    }
    
    std::ifstream is (argv[1], std::ifstream::binary);
    
    if (is.is_open())
    {
        int varnum = 0;
        std::string num;
        std::string todo;
        while(is.good())
        {
            getline(is, num);
            sscanf(num.c_str(), "%d", &varnum);
            getline(is, todo);
            if(todo.length() < 1)
                continue;
            
            clock_t start, finish;
            
            printf("%s build ROBDD, with a<b<c<d\n", todo.c_str());
            
            start = clock();
            
            CNFExp *texp1 = new CNFExp(todo);
            Robdd *bdd1 = new Robdd(varnum);
            bdd1->Build(texp1);
            bdd1->PrintNodes();
            
            finish = clock();
            float duration = (double)(finish - start) / CLOCKS_PER_SEC *1000;
            printf( "%f ms\n", duration);
            
            delete bdd1;
            delete texp1;
        }
        is.close();
    }
}

