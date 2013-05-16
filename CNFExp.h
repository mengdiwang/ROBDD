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

class CNFExp
{
public:
	CNFExp(std::string aformula)
	{
		formula = aformula + "#";
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

	void Setv(char var, int value);
	bool GetValue();

private:
	void ProduceStack();
	bool AllApply();

	std::string formula;  //CNF exp
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
	char ch = formula.at(i);
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
	for(i=0;i<position;i++)
	{
		printf("%d",ex[i]);
	}
	printf("\n");
}
//-------------------------------------------
void CNFExp::Setv( char var, int value)
{
	for(int i=0;i<position;i++)
	{
		if (ex[i] == var)
			ex[i] = '0' + value;
	}
}
//-------------------------------------------
bool CNFExp::AllApply()
{
	for(int i=0;i<position;i++)
	{
		if (ex[i] != '&' && ex[i] != '|' && ex[i] != '!' && ex[i] != '!' 
			&& ex[i] != '1' && ex[i] != '0')
			return false;
	}
}

//---------------------------------------------
bool CNFExp::GetValue()
{
	if ( !AllApply() )
		return -1;
	
	int top =0;  //符号辅助 栈指针
	mystack[top] = '#';
	
	int i=0; //遍历后缀表达式
	char ch = ex[i];
	
	char CalCharHere;
	bool Here =false;
	char CalCharBefore;
	bool Before = false;

	while(i!= position)
	{
		switch(ch)
		{
		case'|':
			CalCharHere = mystack[top];
				Here = (CalCharHere == '1') ? true:false;
			top--;
			CalCharBefore = mystack[top];
				Before = (CalCharBefore == '1') ? true:false;
			
			mystack[top]= (Here || Before) ? '1' : '0' ;
			break;

		case'&':
			CalCharHere = mystack[top];
				Here = (CalCharHere == '1') ? true:false;
			top--;
			CalCharBefore = mystack[top];
				Before = (CalCharBefore == '1') ? true:false;
			
			mystack[top]= (Here && Before) ? '1' : '0' ;
			break;

		case'!':
			CalCharHere = mystack[top];
				Here = (CalCharHere == '1') ? true:false;
			mystack[top]= Here ? '0' : '1' ;
			break;
		default:
			top++;
			mystack[top]= ch;
		}
		i++;
		ch = ex[i];
	}
	return mystack[top] =='1';
}
#endif /* defined(__ROBDD__CNFExp__) */
