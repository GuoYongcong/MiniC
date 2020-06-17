/*
* @Copyright (c), 2020-2020, GuoYongcong.
* @File name: globals.h
* @Description: 该文件声明和定义了一些供其他文件使用的宏定义、联合体、枚举、结构体等。
* @Author: 郭永聪
* @Version: 1.0
* @Date:   2020-05-01
* @History:
*   <author>    <version>   <date>          <description>
*   郭永聪         1.0.1     2020-06-01       结构体Node添加了两个个属性：brotherNode[MAXBRONUM]和lineno
*	郭永聪		  1.1.0		2020-06-16		 结构体BucketListRec添加属性last_memloc
*/
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//最多的孩子结点数量
#define MAXNUM 3
//最多的兄弟结点数量
#define MAXBRONUM 2

//结点内容联合体定义
typedef union {
    int value;
    char *ch;
} Val;

//结点类型定义
typedef enum
{
    ifStmt,
    whileStmt,
    assignStmt,
    returnStmt,
    compoundStmt,
    varDeclaration,
    funDeclaration,
    funCall,
    //expressionType,
    //declarationList,
    //paramList,
    //localDeclaration,
    //statementList,
    //argList,
    opType,
    constType,
    idType,
    typeType,
    varType,
    program,
    defaultType
} NodeType;

typedef enum DataType
{
	Unknown,
    Void,
    Integer,
    Array,
	Function
} Type;



//符号位置信息结构体
typedef struct Location
{
    int first_line;   //起点行号
    int first_column; //起点列号
    int last_line;    //终点行号
    int last_column;  //终点列号
} Loc;

//语法树结点定义
typedef struct Node
{
    NodeType nodeType;                   //结点类型
    Val attr;                            //结点内容
    struct Node *childrenNode[MAXNUM];   //孩子结点
    struct Node *brotherNode[MAXBRONUM]; //兄弟结点
    Loc location;                        //符号位置
    Type dataType;
} * STNode;

#ifndef YYLTYPE
typedef struct yyltype
{
    int timestamp;
    int first_line;
    int first_column;
    int last_line;
    int last_column;
    char *text;
} yyltype;

#define YYLTYPE yyltype
#endif

/* the list of line numbers of the source
 * code in which a variable is referenced
 */
typedef struct LineListRec
{
    int lineno;
    struct LineListRec *next;
} * LineList;

//函数的形参结构体
typedef struct ParamList
{
    Type type; //形参类型
    struct ParamList *next;
} * PL;
//函数信息结构体
typedef struct FunctionInformation
{
    Type returnType; //函数返回值类型
    PL params;       //函数形参类型列表
} FuncInfo;

/* The record in the bucket lists for
 * each variable, including name,
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
{
    char *name; //变量名
    Type type; //变量类型
    union {
        int length;    //数组的长度
        FuncInfo info; //函数信息
    } attr;
    Loc scope; //作用域
    LineList lines;
    int memloc; /* memory location for variable */
	int last_memloc; //函数内部的局部变量的最后一个位置
    struct BucketListRec *next;
} * BucketList;

//行号
extern int yylineno;
//输入输出文件指针
extern FILE *yyin, *yyout;
extern bool TraceAnalyze;
extern bool Error;
extern YYLTYPE yylloc;
extern FILE *code;
extern bool TraceCode;
//保留字:input和output
extern const char * func_input;
extern const char * func_output;
extern const char * typeString[];
#endif
