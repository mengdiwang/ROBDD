//
//  main.cpp
//  nqueentest
//
//  Created by Mengdi Wang on 13-5-16.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "nqueen.h"

int main(int argc, const char * argv[])
{
    int n = 8;			/* board of size n*n */
    Nqueen *nq = new Nqueen(n);
    int r = nq->BuildQueen();		/* r = bdd representing n-queens constraints */
    printf("Final bdd size: %d nodes\n", nq->GetBdd()->Getsize());
    // allsat(B, r);		     /* print all solutions in compact form */
    printf("%d solutions\n", nq->GetBdd()->SatCount(r));
    
    return 0;
}

