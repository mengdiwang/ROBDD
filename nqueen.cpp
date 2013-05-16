//
//  nqueen.cpp
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-16.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include "nqueen.h"
#include "utilfunc.h"

int Nqueen::BuildQueen()
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
            x = robdd->Mk(i+j*size+1, 0, 1); // x_ij
            u = robdd->Apply(&orop, u, x);
        }
        r = robdd->Apply(&andop, r, u);
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
                    notx = robdd->Mk(i+k*size+1, 1, 0);//x_ik
                    u = robdd->Apply(&andop, notx, u);
                }
            }
            x = robdd->Mk(i+j*size+1, 0, 1);//x_ij
            u = robdd->Apply(&impop, x, u);
            r = robdd->Apply(&andop, r, u);
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
                    notx = robdd->Mk(k+j*size+1, 1, 0); //x_kj
                    u = robdd->Apply(&andop, notx, u);
                }
            }
            x = robdd->Mk(i+j*size+1, 0, 1); //x_ij
            u = robdd->Apply(&impop, x, u);
            r = robdd->Apply(&andop, r, u);
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
                    notx = robdd->Mk((i+k)+(j+k)*size+1, 1, 0);//x_(i+k)(j+k)
                    u = robdd->Apply(&andop, notx, u);
                }
            }
            x = robdd->Mk(i+j*size+1, 0, 1); //x_ij
            u = robdd->Apply(&impop, x, u);
            r = robdd->Apply(&andop, r, u);
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
                    notx = robdd->Mk((i+k)+(j-k)*size+1, 1, 0);//x_(i+k)(j-k)
                    u = robdd->Apply(&andop, notx, u);
                }
            }
            x = robdd->Mk(i+j*size+1, 0, 1);
            u = robdd->Apply(&impop, x, u);
            r = robdd->Apply(&andop, r, u);
        }
    }
    
    return r;
}