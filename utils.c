/*
* @Copyright (c), 2020-2020, GuoYongcong.
* @File name: utils.c
* @Description: 该文件定义了创建语法树结点、打印语法树等函数
* @Author: 郭永聪
* @Version: 1.0
* @Date:   2020-05-01
* @History:
*   <author>  <version>   <date>       <description>
*   郭永聪     1.0.1       2020-06-02   添加了两个函数addBrotherNode和backspaces
*/

#include <stdio.h>
#include "globals.h"
#include "utils.h"
/**
 * 创建语法树结点
 * @method createSyntaxTreeNode
 * @param  nodeType     结点类型
 * @param  value        结点内容
 * @param  n1           子结点1
 * @param  n2           子结点2
 * @param  n3           子结点3
 * @return              返回值为新创建的结点指针
 */
struct Node * createSyntaxTreeNode(
	NodeType nodeType, char * value,
	struct Node * n1, struct Node * n2, struct Node * n3 )
{
	struct Node * t = (struct Node *)malloc(sizeof(struct Node));
	if (NULL == t)
		fprintf(yyout, "Out of memory error at line %d\n", yylineno);
	else
	{
		t->nodeType = nodeType;
		t->attr.ch = value;
		t->childrenNode[0] = n1;
		t->childrenNode[1] = n2;
		t->childrenNode[2] = n3;
		for(int i=0;i<MAXBRONUM;i++)
		    t->brotherNode[i] = 0;
	}
	return t;
}

struct Node * addBrotherNode(struct Node * n1, struct Node * n2){
    struct Node * t = (struct Node *)malloc(sizeof(struct Node));
    if (NULL == t)
        fprintf(yyout, "Out of memory error at line %d\n", yylineno);
    else
    {
        t->nodeType = defaultType;
        t->attr.ch = 0;
        for(int i=0;i<MAXNUM;i++)
            t->childrenNode[i] = 0;
        t->brotherNode[0] = n1;
        t->brotherNode[1] = n2;
    }
    return t;
}

//缩进的空格数
static int indentno = 0;

//增加或减少缩进的空格数的代码宏定义
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/**
 * 打印空格函数
 * @method printSpaces
 */
static void printSpaces(void)
{
    for (int i=0;i<indentno;i++)
        fprintf(yyout," ");
}

/**
 * 退格函数
 * @method backspaces
 */
static void backspaces(void){
    fseek(yyout, -1L*indentno, SEEK_CUR);
}

/**
 * 20个打印不同类型结点内容的函数
 * @param  tree     语法树的某个结点
 */
void fun_ifStmt(struct Node * tree){ fprintf(yyout,"if\n"); }
void fun_whlieStmt(struct Node * tree){ fprintf(yyout,"while\n"); }
void fun_assignStmt(struct Node * tree){ fprintf(yyout,"assign\n");}
void fun_returnStmt(struct Node * tree){ fprintf(yyout,"return\n"); }
void fun_compoundStmt(struct Node * tree) { fprintf(yyout, "compoundStmt\n"); }

void fun_varDeclaration(struct Node * tree){ fprintf(yyout,"varDeclaration\n"); }
void fun_funDeclaration(struct Node * tree){ fprintf(yyout,"funDeclaration: %s\n",tree->attr.ch); }
void fun_funCall(struct Node * tree){ fprintf(yyout,"call: %s\n", tree->attr.ch); }
void fun_expressionType(struct Node * tree){ fprintf(yyout,"expression\n"); }

void fun_declarationList(struct Node * tree) { fprintf(yyout, "declarationList\n"); }
void fun_paramList(struct Node * tree) { fprintf(yyout, "paramList\n"); }
void fun_localDeclaration(struct Node * tree) { fprintf(yyout, "localDeclaration\n"); }
void fun_statementList(struct Node * tree) { fprintf(yyout, "statementList\n"); }
void fun_argList(struct Node * tree) { fprintf(yyout, "argList\n"); }

void fun_opType(struct Node * tree){ fprintf(yyout,"op: %s\n", tree->attr.ch); }
void fun_constType(struct Node * tree){ fprintf(yyout,"const: %d\n", tree->attr.value); }
void fun_idType(struct Node * tree){ fprintf(yyout,"id: %s\n", tree->attr.ch); }
void fun_typeType(struct Node * tree){ fprintf(yyout,"type: %s\n", tree->attr.ch); }
void fun_program(struct Node * tree){ fprintf(yyout,"program\n"); }
void fun_defaultType(struct Node * tree){ backspaces(); }


//函数指针数组
void (*funs[])(struct Node *) =
{
    fun_ifStmt, fun_whlieStmt, fun_assignStmt, fun_returnStmt,fun_compoundStmt,
    fun_varDeclaration, fun_funDeclaration, fun_funCall, fun_expressionType,
	fun_declarationList, fun_paramList, fun_localDeclaration, fun_statementList,
	fun_argList, fun_opType, fun_constType, fun_idType, fun_typeType, fun_program,
    fun_defaultType
};

/**
 * 打印语法树
 * @method printTree
 * @param  tree     语法树根结点
 */
void printTree( struct Node * tree )
{
    if (tree != 0)
    {
        INDENT;
        printSpaces();
        if(tree->nodeType >= ifStmt && tree->nodeType <= defaultType)
            funs[tree->nodeType](tree); //根据nodeType直接调用相应的打印结点函数
        else fprintf(yyout,"Unknown node type\n");
        for (int i=0;i<MAXNUM;i++)
             printTree(tree->childrenNode[i]);
        UNINDENT;
        for (int i=0;i<MAXBRONUM;i++)
            printTree(tree->brotherNode[i]);

    }
}
