/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "stack.h"
#include "utils.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;

/* Procedure traverse is a generic recursive
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc
 * in postorder to tree pointed to by t
 */
static void traverse(STNode t,
                     void (*preProc)(STNode),
                     void (*postProc)(STNode))
{
    if (t != NULL)
    {
        preProc(t);
        {
            for (int i = 0; i < MAXNUM; i++)
                traverse(t->childrenNode[i], preProc, postProc);
        }
        postProc(t);
        for (int i = 0; i < MAXBRONUM; i++)
            traverse(t->brotherNode[i], preProc, postProc);
    }
}

/* nullProc is a do-nothing procedure to
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(STNode t)
{
    if (t == NULL)
        return;
    else
        return;
}

/* Procedure insertNode inserts
 * identifiers stored in t into
 * the symbol table
 */
/*
重复声明（type相同）
int a;
inta;
main.cpp:11:8: error: redeclaration of 'int a'
main.cpp:10:9: note: 'int a' previously declared here

冲突声明（type不相同）

int a;
int a[2];
char a;
main.cpp:11:9: error: conflicting declaration 'char a'
main.cpp:10:9: note: previous declaration as 'int a'


main.cpp:11:10: error: invalid conversion from 'const char*' to 'int' [-fpermissive]
   11 |    a[0] ="323";
      |          ^~~~~
      |          |
      |          const char*
*/
static void insertNode(STNode t)
{
    switch (t->nodeType)
    {
    case program:
    case compoundStmt:
        push(&t->location);
        break;
    case funDeclaration:
        if (NULL == st_lookup(t->attr.ch, &t->location))
            //不在符号表中
            st_insert(t->attr.ch,
                      "function",
                      t->location.first_line,
                      location++);
        else
            // 已存在符号表中，重复声明函数
            funRedeclarationError(t);
        break;
    case funCall:
        if (NULL == st_lookup(t->attr.ch, &t->location))
            //不在符号表中，变量使用前未声明
            notDeclarationError(t);
        else
            // 已存在符号表中
            st_insert(t->attr.ch,
                      "function",
                      t->location.first_line,
                      0);

        break;
    case varDeclaration:
        STNode stn = t->childrenNode[1];
        BucketList l = st_lookup(stn->attr.ch, &stn->location);
        if (NULL == l)
            //不在符号表中
            st_insert(stn->attr.ch,
                      t->childrenNode[0]->attr.ch,
                      stn->location.first_line,
                      location++);
        else
        { // 已存在符号表中
            while (-2 == compareScope(getTop(), &stn->location))
                pop();

            if (1 == compareScope(getTop(), &stn->location))
            {
                int result = compareScope(getTop(), &l->scope);
                if (0 == result)
                    //重复声明变量
                    varRedeclarationError(t);
                else if (-1 == result)
                    //声明局部变量
                    st_insert(stn->attr.ch,
                              t->childrenNode[0]->attr.ch,
                              stn->location.first_line,
                              location++);
            }
        }
        break;
    case varType:
        /*main.cpp:8:4: error: 'b' was not declared in this scope
    8 |    b = 1;*/
        if (NULL == st_lookup(t->attr.ch, &t->location))
            //不在符号表中，变量使用前未声明
            notDeclarationError(t);
        else
            // 已存在符号表中
            st_insert(t->attr.ch,
                      NULL,
                      t->location.first_line,
                      0);

        break;
    default:
        break;
    }
    // switch (t->nodekind)
    // {
    // case StmtK:
    // 	switch (t->kind.stmt)
    // 	{
    // 	case AssignK:
    // 	case ReadK:
    // 		if (st_lookup(t->attr.name) == -1)
    // 			/* not yet in table, so treat as new definition */
    // 			st_insert(t->attr.name, t->lineno, location++);
    // 		else
    // 			/* already in table, so ignore locationlocation,
    // 					   add line number of use only */
    // 			st_insert(t->attr.name, t->lineno, 0);
    // 		break;
    // 	default:
    // 		break;
    // 	}
    // 	break;
    // case ExpK:
    // 	switch (t->kind.exp)
    // 	{
    // 	case IdK:
    // 		if (st_lookup(t->attr.name) == -1)
    // 			/* not yet in table, so treat as new definition */
    // 			st_insert(t->attr.name, t->lineno, location++);
    // 		else
    // 			/* already in table, so ignore location,
    // 					   add line number of use only */
    // 			st_insert(t->attr.name, t->lineno, 0);
    // 		break;
    // 	default:
    // 		break;
    // 	}
    // 	break;
    // default:
    // 	break;
    // }
}

/* Function buildSymtab constructs the symbol
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(STNode syntaxTree)
{
    traverse(syntaxTree, insertNode, nullProc);
    if (TraceAnalyze)
    {
        fprintf(yyout, "\nSymbol table:\n\n");
        printSymTab(yyout);
    }
}

static void typeError(STNode t, char *message)
{
    fprintf(stderr, "Type error at line %d, column %d: %s\n",
            t->location.first_line, t->location.first_column, message);
    Error = true;
}

static void varRedeclarationError(STNode t)
{
    fprintf(stderr, "error: redeclaration of \'%s %s\' at line %d, column %d.\n",
            t->childrenNode[0]->attr.ch,
            t->childrenNode[1]->attr.ch,
            t->location.first_line,
            t->location.first_column);
    Error = true;
}

static void funRedeclarationError(STNode t)
{
    fprintf(stderr, "error: redeclaration of \'%s %s\' at line %d, column %d.\n",
            t->childrenNode[0]->attr.ch,
            t->attr.ch,
            t->location.first_line,
            t->location.first_column);
    Error = true;
}
static void conflictingDeclarationError(STNode t)
{
    fprintf(stderr, "error: conflicting declaration \'%s %s\' at line %d, column %d.\n",
            t->childrenNode[0]->attr.ch,
            t->childrenNode[1]->attr.ch,
            t->location.first_line,
            t->location.first_column);
    Error = true;
}
static void notDeclarationError(STNode t)
{
    fprintf(stderr, "error: \'%s\' was not declared in this scope,  at line %d, column %d.\n",
            t->attr.ch,
            t->location.first_line,
            t->location.first_column);
    Error = true;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(STNode t)
{
    switch (t->nodeType)
    {
    case assignStmt:

        break;
    default:
        break;
    }
    // switch (t->nodekind)
    // {
    // case ExpK:
    // 	switch (t->kind.exp)
    // 	{
    // 	case OpK:
    // 		if ((t->childrenNode[0]->type != Integer) ||
    // 			(t->childrenNode[1]->type != Integer))
    // 			typeError(t, "Op applied to non-integer");
    // 		if ((t->attr.op == EQ) || (t->attr.op == LT))
    // 			t->type = Boolean;
    // 		else
    // 			t->type = Integer;
    // 		break;
    // 	case ConstK:
    // 	case IdK:
    // 		t->type = Integer;
    // 		break;
    // 	default:
    // 		break;
    // 	}
    // 	break;
    // case StmtK:
    // 	switch (t->kind.stmt)
    // 	{
    // 	case IfK:
    // 		if (t->childrenNode[0]->type == Integer)
    // 			typeError(t->childrenNode[0], "if test is not Boolean");
    // 		break;
    // 	case AssignK:
    // 		if (t->childrenNode[0]->type != Integer)
    // 			typeError(t->childrenNode[0], "assignment of non-integer value");
    // 		break;
    // 	case WriteK:
    // 		if (t->childrenNode[0]->type != Integer)
    // 			typeError(t->childrenNode[0], "write of non-integer value");
    // 		break;
    // 	case RepeatK:
    // 		if (t->childrenNode[1]->type == Integer)
    // 			typeError(t->childrenNode[1], "repeat test is not Boolean");
    // 		break;
    // 	default:
    // 		break;
    // 	}
    // 	break;
    // default:
    // 	break;
    // }
}

/* Procedure typeCheck performs type checking
 * by a postorder syntax tree traversal
 */
void typeCheck(STNode syntaxTree)
{
    traverse(syntaxTree, nullProc, checkNode);
}
