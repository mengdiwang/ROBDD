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
	~CNFExp()
	{
		delete[] ex;
		delete[] mystack;
	}

	void apply(string var, int value);
	bool GetValue();
private:
	void ProduceStack();
	bool AllApply();
	int findAtomic(string var);

	std::string formula;  //CNF exp
	string fomulaSuffix;  //后缀计算式
	int size;   //后缀表达式可用长度

	char* ex;      /*存储后缀表达式*/
	char* mystack; /*作为栈使用 存储符号*/
	int position;
};

void CNFExp::ProduceStack()
{
	int top =0;  //符号辅助 栈指针
	mystack[top] = '#';
	
	position = 0; //后缀表达式 下标
	int i=0; //遍历表达式
	string here;
	char ch = formula.at(i);
	//忽略计算栈中的数字
	//TODO:可以考虑在apply中，将字符串冗余信息删除
	while(ch != '#')
	{
		switch(ch)
		{
		case'(':
			top++;
			mystack[top] = ch;
			break;
		case')':
			while(mystack[top]!='(')
			{
				ex[position] = mystack[top];
				top--;
				position++;
			}
			top--;
			break;
		case'|':
		case'&':
			while(top!=0 && mystack[top]!='(')
			{ 
				ex[position]=mystack[top];
				top--;
				position++; 
			}
			top++;
			mystack[top]=ch;
			break;
		case'!':
			top++;
			mystack[top]=ch; 
			break;
		case'#':
			while(top!=0)
			{ 
				ex[position]=mystack[top];
				top--;
				position++; 
			}
			break;
		default:
			ex[position]=ch;
			position++;
		}
		i++;
		ch = formula.at(i);
	}
	//表达式处理完毕，将当前所有操作数出栈
	while(mystack[top] != '#')
	{
		ex[position]=mystack[top];
		top--;
		position++; 
	}

	printf("转化为后缀表达为：\n");
	string suffix(position +1,'a');
	fomulaSuffix = suffix;

	for(i=0;i<position;i++)
	{
		printf("%c",ex[i]);
		fomulaSuffix[i]= ex[i];
	}
	printf("\n");
	fomulaSuffix[position]= '#';
}
//-------------------------------------------
void CNFExp::apply( string var, int value)
{
	int pos = findAtomic(var);
	while(pos != -1)
	{
		fomulaSuffix[pos] = (value ==1)?'T':'F';
		pos = findAtomic(var);
	}
}
//-------------------------------------------
int CNFExp::findAtomic(string var)
{
	int len = var.length();
	int pos =  fomulaSuffix.find(var, 0);
	while( pos != string::npos)
	{
		//保证找到原子命题
		if(fomulaSuffix[pos+ len] >= '0' && fomulaSuffix[pos+ len] <= '9')
		{
			pos = fomulaSuffix.find(var, pos+1);
		}
		else
			return pos;
	}
	return -1;
}
//-------------------------------------------
bool CNFExp::AllApply()
{
	char here;
	for(int i=0;i<position;i++)
	{
		here = fomulaSuffix[i];
		if (here != '&' && here != '|' && here != '!' &&  
			here != 'T' && here != 'F'
			&& !(here >='0' && here <='9') )
			return false;
	}
	return true;
}

//---------------------------------------------
bool CNFExp::GetValue()
{
	if ( !AllApply() )
		return false;
	
	char CalCharHere;
	bool Here =false;
	char CalCharBefore;
	bool Before = false;

	int top =0;  //符号辅助 栈指针
	mystack[top] = '#';
	int i=0; //遍历后缀表达式
	char ch = fomulaSuffix[i];

	while(i!= position)
	{
		switch(ch)
		{
		case'|':
			while( mystack[top] != 'T' && mystack[top] != 'F' )
				top--;
			CalCharHere = mystack[top];
				Here = (CalCharHere == 'T') ? true:false;
			top--;
			while( mystack[top] != 'T' && mystack[top] != 'F' )
				top--;
			CalCharBefore = mystack[top];
				Before = (CalCharBefore == 'T') ? true:false;
			
			mystack[top]= (Here || Before) ? 'T' : 'F' ;
			break;

		case'&':
			while( mystack[top] != 'T' && mystack[top] != 'F' )
				top--;
			CalCharHere = mystack[top];
				Here = (CalCharHere == 'T') ? true:false;
			top--;
			while( mystack[top] != 'T' && mystack[top] != 'F' )
				top--;
			CalCharBefore = mystack[top];
				Before = (CalCharBefore == 'T') ? true:false;
			
			mystack[top]= (Here && Before) ? 'T' : 'F' ;
			break;

		case'!':
			while( mystack[top] != 'T' && mystack[top] != 'F' )
				top--;
			CalCharHere = mystack[top];
				Here = (CalCharHere == 'T') ? true:false;
			mystack[top]= Here ? 'F' : 'T' ;
			break;
		default:
			top++;
			mystack[top]= ch;
		}
		i++;
		ch = fomulaSuffix[i];
	}
	return mystack[top] =='T';
}
#endif /* defined(__ROBDD__CNFExp__) */
