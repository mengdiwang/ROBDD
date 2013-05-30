//
//  CNFExp.h
//  ROBDD
//
//  Created by Libo on 13-5-14.
//  Copyright (c) 2013年 Libo. All rights reserved.
//

#ifndef __ROBDD__CNFExp__
#define __ROBDD__CNFExp__

#include <string.h>
#include <iostream>
#include <string>

class CNFExp
{
public:    
	CNFExp(std::string aformula)
	{
        //formula = aformula + "#";
		size = aformula.size()+1;
		ex = new char[size];
		mystack = new char[size +2];
        memset(ex, 0, sizeof(char)*size);
        memset(mystack, 0, sizeof(char)*size);
		ProduceStack(aformula);
	}
    
    CNFExp(int asize)
    {
        size = asize;
		ex = new char[size];
        mystack = new char[size +2];
    }
    
	~CNFExp()
	{
        if(ex!=NULL)
        {
            delete[] ex; ex = NULL;
		}
        if(mystack!=NULL)
        {
            delete[] mystack; mystack = NULL;
        }
	}

    void Setvbyn(int varn, int value);// 1=='a'
	void Setv(char var, int value);
	bool GetValue();
    
    void CpyVal(char* _ex, char* _mystack, int _position)
    {
        strcpy(ex, _ex);
        strcpy(mystack, _mystack);
        position = _position;
    }
    
    int GetSize()
    {
        return size;
    }

	void ProduceStack(std::string aformula);
	bool AllApply();

	//std::string formula;    //CNF exp
	int size;               //后缀表达式可用长度
public:
	char* ex;               //存储后缀表达式
	char* mystack;          //作为栈使用 存储符号
	int position;
};

#endif /* defined(__ROBDD__CNFExp__) */
