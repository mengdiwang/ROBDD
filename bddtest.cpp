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
#include "nqueen.h"

int main()
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
    
    return 0;
}
