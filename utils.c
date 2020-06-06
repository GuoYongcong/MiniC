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

//添加位置信息
void setLoc(Loc *loc, int fl, int fc, int ll, int lc);

bool TraceAnalyze = true;
bool Error = false;

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
STNode createSyntaxTreeNode(
    NodeType nodeType, char *value,
    STNode n1, STNode n2, STNode n3)
{
    STNode t = (STNode)malloc(sizeof(struct Node));
    if (NULL == t)
        fprintf(yyout, "Out of memory error at line %d\n", yylineno);
    else
    {
        t->nodeType = nodeType;
        t->attr.ch = value;
        t->childrenNode[0] = n1;
        t->childrenNode[1] = n2;
        t->childrenNode[2] = n3;
        for (int i = 0; i < MAXBRONUM; i++)
            t->brotherNode[i] = 0;
        setLoc(&t->location, 0, 0, 0, 0);
    }
    return t;
}

STNode addBrotherNode(STNode n1, STNode n2)
{
    STNode t = (STNode)malloc(sizeof(struct Node));
    if (NULL == t)
        fprintf(yyout, "Out of memory error at line %d\n", yylineno);
    else
    {
        t->nodeType = defaultType;
        t->attr.ch = 0;
        for (int i = 0; i < MAXNUM; i++)
            t->childrenNode[i] = 0;
        t->brotherNode[0] = n1;
        t->brotherNode[1] = n2;
        setLoc(&t->location, 0, 0, 0, 0);
    }
    return t;
}

void setLocation(Loc *loc, YYLTYPE *ltype)
{
    setLoc(loc,
           ltype->first_line,
           ltype->first_column,
           ltype->last_line,
           ltype->last_column);
}

void setLoc(Loc *loc, int fl, int fc, int ll, int lc)
{

    loc->first_line = fl;
    loc->first_column = fc;
    loc->last_line = ll;
    loc->last_column = lc;
}

//缩进的空格数
static int indentno = 0;

//增加或减少缩进的空格数的代码宏定义
#define INDENT indentno += 2
#define UNINDENT indentno -= 2

/**
 * 打印空格函数
 * @method printSpaces
 */
static void printSpaces(void)
{
    for (int i = 0; i < indentno; i++)
        fprintf(yyout, " ");
}

/**
 * 退格函数
 * @method backspaces
 */
static void backspaces(void)
{
    fseek(yyout, -1L * indentno, SEEK_CUR);
}

/**
 * 20个打印不同类型结点内容的函数
 * @param  tree     语法树的某个结点
 */
void fun_ifStmt(STNode tree) { fprintf(yyout, "if\n"); }

void fun_whlieStmt(STNode tree) { fprintf(yyout, "while\n"); }

void fun_assignStmt(STNode tree) { fprintf(yyout, "assign\n"); }

void fun_returnStmt(STNode tree) { fprintf(yyout, "return\n"); }

void fun_compoundStmt(STNode tree) { fprintf(yyout, "compoundStmt\n"); }

void fun_varDeclaration(STNode tree) { fprintf(yyout, "varDeclaration\n"); }

void fun_funDeclaration(STNode tree) { fprintf(yyout, "funDeclaration: %s\n", tree->attr.ch); }

void fun_funCall(STNode tree) { fprintf(yyout, "call: %s\n", tree->attr.ch); }

void fun_expressionType(STNode tree) { fprintf(yyout, "expression\n"); }

void fun_declarationList(STNode tree) { fprintf(yyout, "declarationList\n"); }

void fun_paramList(STNode tree) { fprintf(yyout, "paramList\n"); }

void fun_localDeclaration(STNode tree) { fprintf(yyout, "localDeclaration\n"); }

void fun_statementList(STNode tree) { fprintf(yyout, "statementList\n"); }

void fun_argList(STNode tree) { fprintf(yyout, "argList\n"); }

void fun_opType(STNode tree) { fprintf(yyout, "op: %s\n", tree->attr.ch); }

void fun_constType(STNode tree) { fprintf(yyout, "const: %d\n", tree->attr.value); }

void fun_idType(STNode tree) { fprintf(yyout, "id: %s\n", tree->attr.ch); }

void fun_typeType(STNode tree) { fprintf(yyout, "type: %s\n", tree->attr.ch); }

void fun_program(STNode tree) { fprintf(yyout, "program\n"); }

void fun_defaultType(STNode tree) { backspaces(); }

//函数指针数组
void (*funs[])(STNode) =
    {
        fun_ifStmt, fun_whlieStmt, fun_assignStmt, fun_returnStmt, fun_compoundStmt,
        fun_varDeclaration, fun_funDeclaration, fun_funCall, fun_expressionType,
        fun_declarationList, fun_paramList, fun_localDeclaration, fun_statementList,
        fun_argList, fun_opType, fun_constType, fun_idType, fun_typeType, fun_program,
        fun_defaultType};

/**
 * 打印语法树
 * @method printTree
 * @param  tree     语法树根结点
 */
void printTree(STNode tree)
{
    if (tree != 0)
    {
        INDENT;
        printSpaces();
        if (tree->nodeType >= ifStmt && tree->nodeType <= defaultType)
            funs[tree->nodeType](tree); //根据nodeType直接调用相应的打印结点函数
        else
            fprintf(yyout, "Unknown node type\n");
        for (int i = 0; i < MAXNUM; i++)
            printTree(tree->childrenNode[i]);
        UNINDENT;
        for (int i = 0; i < MAXBRONUM; i++)
            printTree(tree->brotherNode[i]);
    }
}

void printLocation(STNode tree)
{
    if (tree != 0)
    {
        switch (tree->nodeType)
        {
        case idType:
            fprintf(yyout, "id: %s, location: %d:%d, %d:%d\n",
                    tree->attr.ch,
                    tree->location.first_line,
                    tree->location.first_column,
                    tree->location.last_line,
                    tree->location.last_column);
            break;
        case compoundStmt:
            fprintf(yyout, "compoundStmt, location: %d:%d, %d:%d\n",
                    tree->location.first_line,
                    tree->location.first_column,
                    tree->location.last_line,
                    tree->location.last_column);

            break;
        case funDeclaration:
            if (0 == tree->childrenNode[0])
                break;
            fprintf(yyout, "funcion: %s, location: %d:%d, %d:%d, returnType: %s\n",
                    tree->attr.ch,
                    tree->location.first_line,
                    tree->location.first_column,
                    tree->location.last_line,
                    tree->location.last_column,
                    tree->childrenNode[0]->attr.ch);
            break;

        default:
            break;
        }
        for (int i = 0; i < MAXNUM; i++)
            printLocation(tree->childrenNode[i]);
        for (int i = 0; i < MAXBRONUM; i++)
            printLocation(tree->brotherNode[i]);
    }
}

// 比较作用域
// loc1包含loc2，返回1;
// loc1与loc2相同，返回0;
// loc1包含于loc2，返回-1;
// loc1与loc2不相交，返回-2;
// 其它情况，返回-3;
int compareScope(Loc *loc1, Loc *loc2)
{
    bool fl1 = loc1->first_line < loc2->first_line;
    bool fl2 = loc1->first_line == loc2->first_line;
    // bool fl3 = loc1->first_line > loc2->first_line;

    bool ll1 = loc1->last_line < loc2->last_line;
    bool ll2 = loc1->last_line == loc2->last_line;
    // bool ll3 = loc1->last_line > loc2->last_line;

    bool fc1 = loc1->first_column < loc2->first_column;
    bool fc2 = loc1->first_column == loc2->first_column;
    // bool fc3 = loc1->first_column > loc2->first_column;

    bool lc1 = loc1->last_column < loc2->last_column;
    bool lc2 = loc1->last_column == loc2->last_column;
    // bool lc3 = loc1->last_column > loc2->last_column;

    bool ll_fl1 = loc1->last_line < loc2->first_line;
    bool ll_fl2 = loc1->last_line == loc2->first_line;

    bool fl_ll1 = loc1->first_line > loc2->last_line;
    bool fl_ll2 = loc1->first_line == loc2->last_line;

    bool lc_fc1 = loc1->last_column < loc2->first_column;

    bool fc_lc1 = loc1->first_column > loc2->last_column;

    int result = -3;
    if (fl1)
    {
        if (!ll1 && !ll2)
            result = 1;
        else if (ll2)
            if (!lc1 && !lc2)
                result = 1;
    }
    else if (fl2)
    {
        if (ll1)
        {
            if (!fc1 && !fc2)
                result = -1;
        }
        else if (ll2)
        {
            if (fc1)
            {
                if (!lc1 && !lc2)
                    result = 1;
            }
            else if (fc2)
            {
                if (lc2)
                    result = 0;
            }
            else
            {
                if (lc1)
                    result = -1;
            }
        }
        else
        {
            if (fc1)
                result = 1;
        }
    }
    else
    {
        if (ll1)
            result = -1;
        else if (ll2)
            if (lc1)
                result = -1;
    }
    if (ll_fl1)
        result = -2;
    else if (ll_fl2)
        if (lc_fc1)
            result = -2;
    if (fl_ll1)
        result = -2;
    else if (fl_ll2)
        if (fc_lc1)
            result = -2;
    // if (fl1 && ll3)
    //     result = 1;
    // if (fl2 && ll2 && fc1 && lc3)
    //     result = 1;
    // if (fl2 && ll3 && fc1)
    //     result = 1;
    // if (fl1 && ll2 && lc3)
    //     result = 1;
    // if (fl2 && ll2 && fc2 && lc2)
    //     result = 0;
    // if (fl3 && ll1)
    //     result = -1;
    // if (fl2 && ll2 && fc3 && lc1)
    //     result = -1;
    // if (fl2 && ll1 && fc3)
    //     result = -1;
    // if (fl3 && ll2 && lc1)
    //     result = -1;
    // if (ll_fl1 || fl_ll1)
    //     result = -2;
    // if (ll_fl2 && lc_fc1)
    //     result = -2;
    // if (fl_ll2 && fc_lc1)
    //     result = -2;
    return result;
}