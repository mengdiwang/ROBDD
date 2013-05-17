//
//  main.cpp
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-14.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include <iostream>
#include "bddhtable.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define MAXINT_CHARS 12

char* itoa(int n)
{
    char* buf = new char[MAXINT_CHARS * sizeof(char)];
    snprintf(buf, MAXINT_CHARS, "%d", n);
    return buf;
}

/* elements */
struct elem 
{
    char* word;			/* key */
    int count;			/* information */
    
    ~elem()
    {
        if(word != NULL)
        {
            delete word;
            word = NULL;
        }
    }
     
};

/* key comparison */
bool testequal(void *s1, void  *s2) 
{
    if(s1 == NULL || s2== NULL)
        return false;
    return strcmp((char*)s1,(char*)s2) == 0;		/* different from C0! */
    /* or: !strcmp(s1,s2); */
}

/* hash function */
/* uses pseudo-random number generation */
/* converted to use unsigned int in C */
int testhash(char *s, int m)
{
    REQUIRES(m > 1);
    unsigned int a = 1664525;
    unsigned int b = 1013904223;	/* inlined random number generator */
    unsigned int r = 0xdeadbeef;	       /* initial seed */
    int len = strlen(s);		       /* different from C0! */
    int i; unsigned int h = 0;	       /* empty string maps to 0 */
    for (i = 0; i < len; i++)
    {
        h = r*h + ((char*)s)[i];	 /* mod 2^32 */
        r = r*a + b;	 /* mod 2^32, linear congruential random no */
    }
    h = h % m;			/* reduce to range */
    //@assert -m < (int)h && (int)h < m;
    int hx = (int)h;
    if (hx < 0) h += m;	/* make positive, if necessary */
    ENSURES(0 <= hx && hx < m);
    return hx;
}

int main(int argc, const char * argv[])
{
       int n = (1<<10)+1; // start with 1<<10 for timing; 1<<9 for -d
    int num_tests = 10; // start with 1000 for timing; 10 for -d
    int i; int j;
    
    /* different from C0! */
    printf("Testing array of size %d with %d values, %d times\n",
           n/5, n, num_tests);
    for (j = 0; j < num_tests; j++)
    {
        Thtable<char, elem> *H = new Thtable<char, elem>(n/5, &testequal, &testhash);
        
        for (i = 0; i < n; i++)
        {
            elem *e = new elem;
            e->word = itoa(j*n+i);	/* diff from C0 */
            e->count = j*n+i;
            char *ekey = itoa(j*n+i);
            //H.insert(e->word, e);
            H->insert(ekey, e);
        }
        for (i = 0; i < n; i++)
        {
            char* s = itoa(j*n+i);
            //assert(((elem)table_search(H, s))->count == j*n+i); /* "missed existing element" */
            assert(H->search(s)->count == j*n+i);
            
            delete s;
            s = NULL;
        }
        for (i = 0; i < n; i++)
        {
            char* s = itoa((j+1)*n+i);
            assert(H->search(s) == NULL); /* "found nonexistent element" */
            
            delete s;
            s = NULL;
        }
        delete H;
    }
    printf("All tests passed!\n");
    
    return 0;
}

