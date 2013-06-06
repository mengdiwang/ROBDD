//
//  htable.h
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-14.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#ifndef __ROBDD_htable_h
#define __ROBDD_htable_h

#include "bddlist.h"
#include <stdlib.h>
#include "caution.h"

template <typename key, typename element>
class Thtable
{
public:
    Thtable(int asize,
            bool (*equal) (key *k1, key *k2),
            int (*hash) (key *k, int m));
    
    ~Thtable()
    {
        for(int i=0; i<size; i++)
        {
            if(array[i] != NULL)
            {
                delete array[i];
                array[i] = NULL;
            }
        }
        delete[] array;
        array = NULL;
    }

    bool IsValid();
    
    void clear()
    {
        memset(array, 0, sizeof(Tlist<key, element>*) *size);
//        for(int i=0; i<size; i++)
//        {
//            if(array[i] != NULL)
//            {
//                delete array[i];
//                array[i] = NULL;
//            }
//        }
//        delete[] array;
//        array = NULL;

    }
    
    
    element *insert(key *k, element *e);
    element *search(key *k);
    Tlist<key, element> **array;
    bool (*equal) (key *k1, key *k2);
    int (*hash) (key *k, int m);
    int size;
    int num_ele;
};

template <typename key, typename element>
Thtable<key, element>::Thtable(int asize,
                               bool (*aequal) (key *k1, key *k2),
                               int (*ahash) (key *k, int m))
{
    if(asize <=0)
        return;
    
    size    = asize;
    equal   = aequal;
    hash    = ahash;
    num_ele = 0;
    array   = new Tlist<key, element>* [asize];
    memset(array, 0, sizeof(Tlist<key, element>*) *size);
#ifdef DD
    if(!IsValid())
        assert(0);
#endif
}

template <typename key, typename element>
bool Thtable<key, element>::IsValid()
{
    /*
     for(int i=0; i<size; i++)
     {
     Tlist<key, element> *tmp = array[i];
     if(tmp != NULL && !tmp->IsValid(i, size, hash))
     return false;
     }
     */
    return true;
}

template <typename key, typename element>
element* Thtable<key, element>::insert(key *k, element *e)
{
    REQUIRES(IsValid());
    //if(!IsValid())
    //    return NULL;
    
    element *olde;
    int h = (hash)(k, size);
    if(array[h] == NULL)
        array[h] = new Tlist<key, element>(equal);
    
    olde = array[h]->insert(k, e);
    if(olde != NULL)
        return olde;
    //check;
    
    return NULL;
}

template <typename key, typename element>
element *Thtable<key, element>::search(key *k)
{
    REQUIRES(IsValid());
    //if(!IsValid())
    //    return NULL;
    int h = (hash)(k, size);
    if(array[h] == NULL)
        return NULL;
    element *e = array[h]->search(k);
    //check
    return e;
}

#endif /* defined(__ROBDD__htable__) */
