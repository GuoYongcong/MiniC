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

const char * typeString[] = {
	"void",
	"int",
	"array"
};

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

static void typeError(STNode t, char *message)
{
    fprintf(stderr, "Type error at line %d, column %d: %s\n",
            t->location.first_line, t->location.first_column, message);
    Error = true;
}
static void invalidRedeclarationError(STNode t)
{
    fprintf(stderr, "error: invalid declaration of \'%s %s\' at line %d, column %d.\n",
            t->childrenNode[0]->attr.ch,
            t->childrenNode[1]->attr.ch,
            t->location.first_line,
            t->location.first_column);
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
static void voidValueError(STNode t)
{
    fprintf(stderr, "error: void value not ignored as it ought to be,  at line %d, column %d.\n",
            t->location.first_line,
            t->location.first_column);
    Error = true;
}
//from s1 to s2
static void invalidConversionError(char *s1, char *s2, Loc *loc)
{
    fprintf(stderr, "error: invalid conversion from \'%s\' to \'%s\',  at line %d, column %d.\n",
            s1, s2, loc->first_line, loc->first_column);
    Error = true;
}

//error: assignment of function
static void assignmentError(Loc *loc)
{
    fprintf(stderr, "error: assignment of function,  at line %d, column %d.\n",
            loc->first_line, loc->first_column);
    Error = true;
}
static void invalidOperandError(char *type, Loc *loc)
{
    fprintf(stderr, "error: invalid operand of type \'%s\' to operator,  at line %d, column %d.\n",
            type, loc->first_line, loc->first_column);
    Error = true;
}

/*
error: too many arguments to function 'void fun(int, int)'
10 |     b = fun("32","323",0);*/
static void argumentNumberError(const char *s1, Loc *loc)
{
	fprintf(stderr, "too %s arguments to function,  at line %d, column %d.\n",
		s1, loc->first_line, loc->first_column);
	Error = true;
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
        {
            //不在符号表中
            while (1 != compareScope(getTop(), &t->location))
                pop();
            insertBucketList(t->attr.ch,
                             "function",
                             t->location.first_line,
                             location++,
                             0,
                             t);
        }
        else
            // 已存在符号表中，重复声明函数
            funRedeclarationError(t);
        break;
    case funCall:
        /*main.cpp:8:18: error: 'a' cannot be used as a function
    8 |     int b = a(1,2);*/
        {
            BucketList l = st_lookup(t->attr.ch, &t->location);
            if (NULL == l)
                //不在符号表中，变量使用前未声明
                notDeclarationError(t);
            else
            {
                // 已存在符号表中
                insertLineList(l, t->location.first_line);
                if (strcmp(l->type, "int") == 0)
                    t->dataType = Integer;
            }
            break;
        }
    case varDeclaration:
    {
        if (strcmp(t->childrenNode[0]->attr.ch, "int") != 0)
        {
            invalidRedeclarationError(t);
            break;
        }
        STNode stn = t->childrenNode[1];
        BucketList l = st_lookup(stn->attr.ch, &stn->location);
        while (1 != compareScope(getTop(), &stn->location))
            pop();

        if (NULL == l)
        {
            //不在符号表中
            if (stn->childrenNode[0] != NULL)
            {
                int length = 0;
                if (constType == stn->childrenNode[0]->nodeType)
                    length = stn->childrenNode[0]->attr.value;
                insertBucketList(stn->attr.ch,
                                 "array",
                                 stn->location.first_line,
                                 location++,
                                 length,
                                 NULL);
            }
            else
                insertBucketList(stn->attr.ch,
                                 "int",
                                 stn->location.first_line,
                                 location++,
                                 0,
                                 NULL);
        }
        else
        {
            // 已存在符号表中
            int result = compareScope(getTop(), &l->scope);
            if (0 == result)
                //重复声明变量
                varRedeclarationError(t);
            else if (-1 == result)
            {
                //声明局部变量
                if (stn->childrenNode[0] != NULL)
                {
                    int length = 0;
                    if (constType == stn->childrenNode[0]->nodeType)
                        length = stn->childrenNode[0]->attr.value;
                    insertBucketList(stn->attr.ch,
                                     "array",
                                     stn->location.first_line,
                                     location++,
                                     length,
                                     NULL);
                }
                else
                    insertBucketList(stn->attr.ch,
                                     "int",
                                     stn->location.first_line,
                                     location++,
                                     0,
                                     NULL);
            }
        }
        break;
    }
    case varType:
        /*main.cpp:8:4: error: 'b' was not declared in this scope
    8 |    b = 1;*/
        {
            BucketList l = st_lookup(t->attr.ch, &t->location);
            if (NULL == l)
                //不在符号表中，变量使用前未声明
                notDeclarationError(t);
            else
            {
                // 已存在符号表中
                insertLineList(l, t->location.first_line);
                t->dataType = Integer;
            }
            break;
        }
    default:
        break;
    }

}

/* Function buildSymtab constructs the symbol
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(STNode syntaxTree)
{
    //前序遍历
    traverse(syntaxTree, insertNode, nullProc);
    if (TraceAnalyze)
    {
        fprintf(yyout, "\nSymbol table:\n\n");
        printSymTab(yyout);
    }
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(STNode t)
{
    switch (t->nodeType)
    {
    case constType:
        t->dataType = Integer;
        break;
    case defaultType:
        if (t->childrenNode[0] != NULL && t->childrenNode[1] != NULL)
        {
            if (Void == t->childrenNode[0]->dataType)
                invalidOperandError("void", &t->childrenNode[0]->location);
            if (Void == t->childrenNode[1]->dataType)
                invalidOperandError("void", &t->childrenNode[1]->location);
            if (Integer == t->childrenNode[0]->dataType && Integer == t->childrenNode[1]->dataType)
                t->dataType = Integer;
        }
        else if(t->brotherNode[1] != NULL)
            t->dataType = t->brotherNode[1]->dataType;
        break;
    case funDeclaration:
        /*
///////////////////
int fun(){}
 warning: no return statement in function returning non-void
////////////////////////
void test(){}
int fun(){return test();}
main.cpp:14:13: error: void value not ignored as it ought to be
   14 |     return f();}
///////////////////////////////////////
        int fun(){return;}
        main.cpp:9:4: error: return-statement with no value, in function returning 'int' [-fpermissive]
    9 |    return ;
/////////////////////////////////
    void fun(){return 1;}
    main.cpp:9:16: error: return-statement with a value, in function returning 'void' [-fpermissive]
    9 |         return 1;
*/

        break;
    case funCall:
    {
        BucketList bl = st_lookup(t->attr.ch, &t->location);
        if (bl != NULL && strcmp(bl->type, "function") == 0)
        {
			PL pl = bl->attr.info.params;
            STNode stn = t->childrenNode[0];
			while (stn != NULL && defaultType== stn->nodeType ) {
				if (pl != NULL)
				{
					if (stn->brotherNode[1]->dataType != pl->type)
						invalidConversionError(typeString[stn->brotherNode[1]->dataType],
							typeString[pl->type],
							&stn->brotherNode[1]->location);
					stn = stn->brotherNode[0];
					pl = pl->next;
				}
				else
					argumentNumberError("many", &t->location);
			}
			if (NULL == stn )
			{
				if (pl != NULL)
					argumentNumberError("few", &t->location);
			}
			else {
				if (pl != NULL)
				{
					if (stn->dataType != pl->type)
						invalidConversionError(typeString[stn->dataType],
							typeString[pl->type],
							&stn->location);
				}
				else
					argumentNumberError("many", &t->location);
			}
        }

        break;
    }
    case assignStmt:
    {
        BucketList bl = st_lookup(t->childrenNode[0]->attr.ch, &t->childrenNode[0]->location);
        if (bl != NULL)
            if (strcmp(bl->type, "int") == 0 || strcmp(bl->type, "array") == 0)
                if (t->childrenNode[1]->dataType != Integer)
                    invalidConversionError("void", "int", &t->childrenNode[1]->location);
                else
                    t->dataType = Integer;
            else if (strcmp(bl->type, "function") == 0)
                assignmentError(&t->childrenNode[0]->location);
        break;
    }
    case compoundStmt:
        // if (t->childrenNode[1] != NULL)
        //     t->attr.ch = t->childrenNode[1]->attr.ch;
        // else
        //     t->attr.ch = "no";

        break;
    case ifStmt:
    case whlieStmt:
        if (t->childrenNode[0]->dataType != Integer)
            invalidConversionError("void", "int", &t->childrenNode[0]->location);
        break;
    case returnStmt:
        if (t->childrenNode[0] != NULL)
            t->dataType = t->childrenNode[0]->dataType;
        else
            t->dataType = Void;
        break;

    default:
        break;
    }
 
}

/* Procedure typeCheck performs type checking
 * by a postorder syntax tree traversal
 */
void typeCheck(STNode syntaxTree)
{
    //后序遍历
    traverse(syntaxTree, nullProc, checkNode);
}
