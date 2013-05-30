//
//  CNFExp.h
//  ROBDD
//
//  Created by Libo on 13-5-14.
//  Copyright (c) 2013年 Libo. All rights reserved.
//

#ifndef __ROBDD__CNFExp__
#define __ROBDD__CNFExp__

#include<iostream>
#include<string>
#include<set>
using namespace std;

/*
typedef struct mystruct
{
	bool HasCaled;
	string proposition;
	char calculation;
} FomulaElement;
*/
class CNFExp
{
public:
	CNFExp(std::string aformula)
	{
		formula = aformula + "#\0";
		size = formula.size();
		ex = new char[size];
		mystack = new char[size +2];
		ProduceStack();
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
		{delete[] ex; ex = NULL;}
		
        if(mystack != NULL)
        {   delete[] mystack; mystack = NULL;}
	}

	void apply(string var, int value);
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
    
    void Setvbyn(int varn, int value);// 1=='a'

    
    char* ex;      /*存储后缀表达式*/
	char* mystack; /*作为栈使用 存储符号*/
	int position;
private:
	void ProduceStack();
	bool AllApply();
	int findAtomic(string var);

	std::string formula;  //CNF exp
	string fomulaSuffix;  //后缀计算式
	int size;   //后缀表达式可用长度
};
#endif /* defined(__ROBDD__CNFExp__) */
