//
//  bdd.cpp
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-31.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include "bdd.h"

int dump=1;

inline bdd bdd_not(const bdd &r)
{
    int idx = r.robdd->Not(r.idx);
    bdd ret(r);
    ret.idx = idx;
    return ret;
}

inline bdd bdd_apply(const bdd &l, const bdd &r, Operator op)
{
    int idx = r.robdd->Apply(l.idx, r.idx, op);
    bdd ret(r);
    ret.idx = idx;
    return ret;
}

//inline bdd bdd_and(const bdd &l, const bdd &r)
//{
//    return r.robdd->Apply(l.idx, r.idx, AND);
//}
//
//inline bdd bdd_or(const bdd &l, const bdd &r)
//{
//    return r.robdd->Apply(l.idx, r.idx, OR);
//}
//
//inline bdd bdd_xor(const bdd &l, const bdd &r)
//{
//    return r.robdd->Apply(l.idx, r.idx, XOR);
//}
//
//inline bdd bdd_imp(const bdd &l, const bdd &r)
//{
//    return r.robdd->Apply(l.idx, r.idx, IMPL);
//}
//
//inline bdd bdd_biimp(const bdd &l, const bdd &r)
//{
//    return r.robdd->Apply(l.idx, r.idx, BiImpl);
//}

//bdd bdd::operator=(const bdd &r);


/*=== Inline C++ functions =============================================*/

int bdd::id() const
{
    return idx;
}

bdd bdd::operator&(const bdd &r) const
{
    return bdd_apply(*this, r, AND);
}

bdd bdd::operator&=(const bdd &r)
{
    return (*this=bdd_apply(*this, r, AND));
}

bdd bdd::operator^(const bdd &r) const
{
    return bdd_apply(*this, r, XOR);
}

bdd bdd::operator^=(const bdd &r)
{
    return (*this=bdd_apply(*this, r, XOR));
}

bdd bdd::operator|(const bdd &r) const
{
    return bdd_apply(*this, r, OR);
}

bdd bdd::operator|=(const bdd &r)
{
    return (*this=bdd_apply(*this, r, OR));
}

bdd bdd::operator!(void) const
{
    return bdd_not(*this);
}

bdd bdd::operator>>(const bdd &r) const
{
    return bdd_apply(*this, r, IMPL);
}

bdd bdd::operator>>=(const bdd &r)
{
    return (*this=bdd_apply(*this, r, IMPL));
}

bdd bdd::operator-(const bdd &r) const
{
    return bdd_apply(*this, r, GT);
}

bdd bdd::operator-=(const bdd &r)
{
    return (*this=bdd_apply(*this,r,GT));
}

bdd bdd::operator>(const bdd &r) const
{
    return bdd_apply(*this, r, GT);
}

bdd bdd::operator<(const bdd &r) const
{
    return bdd_apply(*this, r, LT);
}

bdd bdd::operator<<(const bdd &r) const
{
    return bdd_apply(*this, r, InvIMPL);
}

bdd bdd::operator<<=(const bdd &r)
{
    return (*this=bdd_apply(*this, r, InvIMPL));
}

bdd bdd::operator==(const bdd &r)
{
    return (*this=bdd_apply(*this, r, BiImpl));
}

//int bdd::operator==(const bdd &r) const
//{
//    return r.idx==idx;
//}

int bdd::operator!=(const bdd &r) const
{
    return r.idx!=idx;
}

bdd bdd_true(void)
{
    return 1;
}

bdd bdd_false(void)
{
    return 0;
}

bdd bdd::operator=(const bdd &r)
{
    if(idx != r.idx)
    {
        idx = r.idx;
        robdd = robdd;
    }
    return *this;
}
