//
//  bdd.h
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-31.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#ifndef __ROBDD__bdd__
#define __ROBDD__bdd__

#include "robdd.h"

class bdd
{
public:
    bdd():robdd(NULL),idx(0){}
    
    bdd(int _idx):robdd(NULL),idx(_idx){}
    
    bdd(int _idx, Robdd *_robdd):idx(_idx),robdd(_robdd){}
    
    bdd(bdd const& _bdd):robdd(_bdd.robdd), idx(_bdd.idx){}

    void SetBase(Robdd *_robdd)
    {
        robdd = _robdd;
    }

    Robdd *GetBase()
    {
        return robdd;
    }
    
    bool GetIthvar(int val)
    {
        int _idx = robdd->GetIthVar(val);
        if(_idx != -1)
        {
            idx = _idx;
            return true;
        }
        return false;
    }
    
    bool GetIthvarNeg(int val)
    {
        int _idx = robdd->GetIthVarNeg(val);
        if(_idx != -1)
        {
            idx = _idx;
            return true;
        }
        return false;
    }
    
    int id() const;
    bdd operator=(const bdd &r);
    bdd operator&(const bdd &r) const;
    bdd operator&=(const bdd &r);
    bdd operator^(const bdd &r) const;
    bdd operator^=(const bdd &r);
    bdd operator|(const bdd &r) const;
    bdd operator|=(const bdd &r);
    bdd operator!(void) const;
    bdd operator>>(const bdd &r) const;
    bdd operator>>=(const bdd &r);
    bdd operator-(const bdd &r) const;
    bdd operator-=(const bdd &r);
    bdd operator>(const bdd &r) const;
    bdd operator<(const bdd &r) const;
    bdd operator<<(const bdd &r) const;
    bdd operator<<=(const bdd &r);
    bdd operator==(const bdd &r);
    //int operator==(const bdd &r) const;
    int operator!=(const bdd &r) const;
    
    Robdd *robdd;
    
private:
    int idx;
    bdd operator=(int r);
    friend bdd bdd_not(const bdd &r);
    friend bdd bdd_simplify(const bdd &r, const bdd &l);
    friend bdd bdd_apply(const bdd &r, const bdd &l, Operator op);
    friend bdd bdd_and(const bdd &r, const bdd &l);
    friend bdd bdd_or(const bdd &r, const bdd &l);
    friend bdd bdd_xor(const bdd &r, const bdd &l);
    friend bdd bdd_imp(const bdd &r, const bdd &l);
    friend bdd bdd_biimp(const bdd &r, const bdd &l);
};
#endif /* defined(__ROBDD__bdd__) */
