#ifndef STACK_H
#define STACK_H

bool push(Loc *scope); //进栈
void pop();			   //出栈
Loc *getTop();		   //读取栈顶元素值
void makeEmpty();	   //清空栈

#endif
