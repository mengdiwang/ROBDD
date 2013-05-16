//
//  nqueen.cpp
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-16.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include "nqueen.h"
#include "utilfunc.h"

int Nqueen::SolveQueen()
{
    REQUIRES(robdd->IsValid());
    
    int r = 1;
    int u, x, notx;
    
    //each column has a queen
    for(int i=0; i<size; i++)
    {
        u = 0;
        for(int j=0; j<size; j++)
        {
            x = robdd->Mk(i+j*size+1, 0, 1);    // x_ij
            u = robdd->Apply(&orop, u, x);      // sum = sum \/ x_ij;
        }
        r = robdd->Apply(&andop, r, u);         // r = r /\ x_ij
    }
    
    //no two queens in the same column
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            u = 1; //ture
            for(int k=0; k<size; k++)
            {
                if(k!=j)
                {
                    notx = robdd->Mk(i+k*size+1, 1, 0); //-x_ik
                    u = robdd->Apply(&andop, notx, u);  //product = product /\ -x_ik
                }
            }
            x = robdd->Mk(i+j*size+1, 0, 1);    //x_ij
            u = robdd->Apply(&impop, x, u);     //result = x_ij -> product
            r = robdd->Apply(&andop, r, u);     //r = r /\ result
        }
    }
    
    //no two queens in the same row
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            u = 1;
            for(int k=0; k<size; k++)
            {
                if(k!=i)
                {
                    notx = robdd->Mk(k+j*size+1, 1, 0); //-x_kj
                    u = robdd->Apply(&andop, notx, u);  //product = product /\ -x_kj
                }
            }
            x = robdd->Mk(i+j*size+1, 0, 1);    //x_ij
            u = robdd->Apply(&impop, x, u);     //result = x_ij -> product
            r = robdd->Apply(&andop, r, u);     //r = r /\ result
        }
    }
    
    //no two queens on same up diagonal
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            u = 1;
            for(int k=-i; k<size-i; k++)
            {
                if(k!=0 && 0<=j+k && j+k<size)
                {
                    notx = robdd->Mk((i+k)+(j+k)*size+1, 1, 0); //-x_(i+k)(j+k)
                    u = robdd->Apply(&andop, notx, u);          //product = product /\ -x_(i+k)(j+k)
                }
            }
            x = robdd->Mk(i+j*size+1, 0, 1);    //x_ij
            u = robdd->Apply(&impop, x, u);     //result = x_ij -> product
            r = robdd->Apply(&andop, r, u);     //r = r /\ result 
        }
    }
    
    //no two queens on same down diagonal
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size; j++)
        {
            u = 1;
            for(int k=-i; k<size-i; k++)
            {
                if(k!=0 && 0<=j-k && j-k<size)
                {
                    notx = robdd->Mk((i+k)+(j-k)*size+1, 1, 0); //-x_(i+k)(j-k)
                    u = robdd->Apply(&andop, notx, u);          //product = product /\ -x_(i+k)(j-k)
                }
            }
            x = robdd->Mk(i+j*size+1, 0, 1);    //x_ij
            u = robdd->Apply(&impop, x, u);     //result = x_ij -> product
            r = robdd->Apply(&andop, r, u);     //r = r /\ result
        }
    }
    
    result = r;//conjunction of all (x_ij -> product)
    return r;
}

void Nqueen::PrintResults()
{
    if(result != 0 && robdd != NULL)
    {
        printf("Final bdd size: %d nodes\n", robdd->Getsize());
        robdd->AllSat(result);		     /* print all solutions in compact form */
        printf("%d solutions\n", robdd->SatCount(result));
    }
    else
    {
        printf("Not solved, run SolveQueen first\n");
    }
}