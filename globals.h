/*
* @Copyright (c), 2020-2020, GuoYongcong.
* @File name: globals.h
* @Description: 该文件声明和定义了一些供其他文件使用的宏定义、联合体、枚举、结构体等。
* @Author: 郭永聪
* @Version: 1.0.1
* @Date:   2020-05-01
* @History:
*   <author>    <version>   <date>          <description>
*   郭永聪         1.0.1     2020-06-01       结构体Node添加了一个属性：brotherNode
*/
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//最多的孩子结点数量
#define MAXNUM 3 

//结点内容联合体定义
typedef union{ 
    int value;
    char* ch;
} Val;

//结点类型定义
typedef enum 
{
    ifStmt, whlieStmt, assignStmt, returnStmt, compoundStmt,
    varDeclaration, funDeclaration, funCall,  expressionType,
	declarationList, paramList, localDeclaration, statementList,
	argList, opType, constType, idType, typeType, program, noType
}NodeType;

//语法树结点定义
typedef struct Node
{
    NodeType nodeType; //结点类型
    Val attr; //结点内容
    struct Node * childrenNode[MAXNUM]; //孩子结点
    struct Node * brotherNode; //兄弟结点
};

//行号
extern int yylineno;
//输入输出文件指针
extern FILE *yyin, *yyout;

#endif
