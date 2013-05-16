//
//  list.h
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-14.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#ifndef ROBDD_list_h
#define ROBDD_list_h

#include <stdlib.h>
#include "caution.h"

template <typename key, typename element>
class Tlnode
{
public:
    Tlnode<key, element>()
    {
        k = NULL;
        e = NULL;
        next = NULL;
    }
    
    ~Tlnode<key, element>()
    {
//        printf("Node called\n");
    }
     
    
    key *k;
    element *e;
    Tlnode<key, element> *next;
};

template <typename key, typename element>
class Tlist
{
public:
    Tlist(bool (*aequal) (key *k1, key *k2))
    {
        equal = aequal;
        head = NULL;
    }
    
    ~Tlist()
    {
        Clear();
        //        printf("List called\n");
    }
    
    void Clear()
    {
        //TODO
        Tlnode<key, element> *q;
        while (head != NULL)
        {
            q = head->next;
            delete head;
            head = q;
        }
    }
    
    element* search(key *k);
    element* insert(key *k, element *e);
    bool IsValid(int h, int m, int (*hash) (key *k, int m));
    
private:
    Tlnode<key, element> *find(key *k);
    
    bool (*equal) (key *k1, key *k2);
    Tlnode<key, element> *head;
};

template<typename key, typename element>
element* Tlist<key, element>::search(key *k)
{
    Tlnode<key, element> *p = find(k);
    if(p == NULL) return NULL;
    return p->e;
}

template<typename key, typename element>
element* Tlist<key, element>::insert(key *k, element *e)
{
    Tlnode<key, element> *p = find(k);
    if(p == NULL)
    {
        Tlnode<key, element> *np = new Tlnode<key, element>();
        np->k = k;
        np->e = e;
        np->next = head;
        head = np;
        return NULL; //did not overwrite
    }
    else
    {
        //Tlnode<key, element> *old = p;
        element *olde = p->e;
        //key *oldk = p->k;
        p->e = e;
        p->k = k;
        return olde;
    }
}

template<typename key, typename element>
Tlnode<key, element>* Tlist<key, element>::find(key *k)
{
    Tlnode<key, element> *p = head;
    while(p != NULL)
    {
        if((p->k != NULL) && (equal)(k, p->k))
            return p;
        p = p->next;
    }
    return NULL;
}

template<typename key, typename element>
bool Tlist<key, element>::IsValid(int h, int m, int (*hash) (key *k, int m))
{
    Tlnode<key, element> *p = this->head;
    while (p != NULL)
    {
        if (p->k == NULL)
            return false;
        if ((hash)(p->k,m) != h)
        {
            return false;
            p = p->next;
        }
    }
    return true;
}

#endif /* defined(__ROBDD__list__) */
