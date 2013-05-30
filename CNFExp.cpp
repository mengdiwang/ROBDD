//
//  CNFExp.cpp
//  ROBDD
//
//  Created by Mengdi Wang on 13-5-16.
//  Copyright (c) 2013年 Mengdi Wang. All rights reserved.
//

#include "CNFExp.h"

void CNFExp::ProduceStack(std::string formula)
{
    formula+="#";
    memset(mystack, 0, (size+2)*sizeof(char));
    memset(ex, 0, size*sizeof(char));
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
    
#ifdef DD
	printf("转化为后缀表达为：\n");
	for(i=0;i<position;i++)
	{
		printf("%c",ex[i]);
	}
	printf("\n");
#endif
}
//-------------------------------------------
void CNFExp::Setv(char var, int value)
{
	for(int i=0;i<position;i++)
	{
		if (ex[i] == var)
			ex[i] = '0' + value;
	}
}
//-------------------------------------------
void CNFExp::Setvbyn(int varn, int value)// 1=='a'
{
	for(int i=0;i<position;i++)
	{
		if (ex[i] == 'a'-1+varn)
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
    return true;
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