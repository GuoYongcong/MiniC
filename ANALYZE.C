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
	"unknown",
	"void",
	"int",
	"array",
	"function"
};
//保留字:input和output
const char * func_input = "input";
const char * func_output = "output";

typedef struct LocationList
{
	Loc loc; //位置信息
	struct LocationList *next;
} *LocList;
//释放空间
void freeLocList(LocList locs) {
	LocList loc = NULL;
	while (locs != NULL) {
		loc = locs;
		locs = locs->next;
		free(loc);
	}
}

//释放空间
void freeParamList(PL pls) {
	PL pl = NULL;
	while (pls != NULL) {
		pl = pls;
		pls = pls->next;
		free(pl);
	}
}
/* Procedure traverse is a generic recursive
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc
 * in postorder to tree pointed to by t
 */
static void traverse(STNode t,
	void(*preProc)(STNode),
	void(*midProc)(STNode),
	void(*postProc)(STNode))
{
	if (t != NULL)
	{
		preProc(t);
		{
			for (int i = 0; i < MAXNUM; i++)
				traverse(t->childrenNode[i], preProc, midProc, postProc);
		}
		midProc(t);
		{
			for (int i = 0; i < MAXBRONUM; i++)
				traverse(t->brotherNode[i], preProc, midProc, postProc);
		}
		postProc(t);
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
static void invalidDeclarationError(STNode t)
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
static void invalidConversionError(Type t1, Type t2, Loc *loc)
{
	fprintf(stderr, "error: invalid conversion from \'%s\' to \'%s\',  at line %d, column %d.\n",
		typeString[t1], typeString[t2], loc->first_line, loc->first_column);
	Error = true;
}

//error: assignment of function
static void assignmentError(Type type, Loc *loc)
{
	fprintf(stderr, "error: cannot assign to \'%s\',  at line %d, column %d.\n",
		typeString[type], loc->first_line, loc->first_column);
	Error = true;
}
static void invalidAssignmentError(const char * type, Loc *loc)
{
	fprintf(stderr, "error: invalid \'%s\' assignment,  at line %d, column %d.\n",
		type, loc->first_line, loc->first_column);
	Error = true;
}

static void invalidOperandError(Type type, Loc *loc)
{
	fprintf(stderr, "error: invalid operand of type \'%s\' to operator,  at line %d, column %d.\n",
		typeString[type], loc->first_line, loc->first_column);
	Error = true;
}


static void argumentNumberError(const char *s1, Loc *loc)
{
	fprintf(stderr, "too %s arguments to function,  at line %d, column %d.\n",
		s1, loc->first_line, loc->first_column);
	Error = true;
}

static void arrayError(const char *s1, Loc *loc)
{
	fprintf(stderr, "error: \'%s\' is not an array,  at line %d, column %d.\n",
		s1, loc->first_line, loc->first_column);
	Error = true;
}

static void insertNode(STNode t)
{
	switch (t->nodeType)
	{
	case program:
	case compoundStmt:
		//进入新的作用域
		push(&t->location);
		break;
	case funDeclaration:
	{
		if (strcmp(t->attr.ch, func_input) == 0 || strcmp(t->attr.ch, func_output) == 0) {
			//函数名跟保留字input或output冲突
			funRedeclarationError(t);
			break;
		}
		if (NULL == st_lookup(t->attr.ch, &t->location))
		{
			//不在符号表中
			while (1 != compareScope(getTop(), &t->location))
				pop();
			insertBucketList(t->attr.ch,
				Function,
				t->location.first_line,
				location,
				0,
				t);
			/*函数占两个位置:
			一个存储函数入口；
			一个存储函数内部的局部变量的最后一个位置；
			*/
			location += 2;
		}
		else
			// 已存在符号表中，重复声明函数
			funRedeclarationError(t);
		break;
	}
	case funCall:
	{
		if (strcmp(t->attr.ch, func_input) == 0 || strcmp(t->attr.ch, func_output) == 0) {
			//函数名跟保留字input或output相同，使用前无需声明，也不用添加到符号表
			break;
		}
		BucketList l = st_lookup(t->attr.ch, &t->location);
		if (NULL == l)
			//不在符号表中，变量使用前未声明
			notDeclarationError(t);
		else
		{
			// 已存在符号表中
			insertLineList(l, t->location.first_line);
			t->dataType = l->type;

		}
		break;
	}
	case varDeclaration:
	{
		if (strcmp(t->childrenNode[1]->attr.ch, func_input) == 0
			|| strcmp(t->childrenNode[1]->attr.ch, func_output) == 0)
		{
			//变量名跟保留字input或output冲突
			varRedeclarationError(t);
			break;
		}
		if (strcmp(t->childrenNode[0]->attr.ch, typeString[Integer]) != 0)
		{
			invalidDeclarationError(t);
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
				//数组
				int length = 1;
				if (constType == stn->childrenNode[0]->nodeType)
					length = stn->childrenNode[0]->attr.value;
				insertBucketList(stn->attr.ch,
					Array,
					stn->location.first_line,
					location,
					length,
					NULL);
				location += length;
			}
			else
				insertBucketList(stn->attr.ch,
					Integer,
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
						Array,
						stn->location.first_line,
						location++,
						length,
						NULL);
				}
				else
					insertBucketList(stn->attr.ch,
						Integer,
						stn->location.first_line,
						location++,
						0,
						NULL);
			}
		}
		break;
	}
	case varType:
	{
		BucketList l = st_lookup(t->attr.ch, &t->location);
		if (NULL == l)
			//不在符号表中，变量使用前未声明
			notDeclarationError(t);
		else
			// 已存在符号表中
			insertLineList(l, t->location.first_line);
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
	traverse(syntaxTree, insertNode, nullProc, nullProc);
	BucketList l = st_lookup("main", &syntaxTree->location);
	if (NULL == l || l->type != Function)
		//程序没有main函数
		fprintf(stderr, "error: program has no main function.\n");
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
	case varType:
	{
		BucketList l = st_lookup(t->attr.ch, &t->location);
		if (NULL != l)
		{
			// 已存在符号表中
			if (t->childrenNode[0] != NULL)
			{
				//带有下标
				if (Array == l->type)
				{
					//如果是数组，则检查下标类型
					if (t->childrenNode[0]->dataType != Integer)
					{
						//如果下标类型不是int
						if (t->childrenNode[0]->dataType != Unknown)
							invalidConversionError(
								t->childrenNode[0]->dataType,
								Integer,
								&t->childrenNode[0]->location);
					}
					else
						t->dataType = Integer;
				}
				else
					//如果不是数组，则报错
					arrayError(t->attr.ch, &t->location);
			}
			else
				//不带下标
				t->dataType = l->type;
		}
	}
	break;
	case defaultType:
		if (t->childrenNode[0] != NULL && t->childrenNode[1] != NULL)
		{
			Type leftType = t->childrenNode[0]->dataType, rightType = t->childrenNode[1]->dataType;
			if (Integer == leftType&&Integer == rightType)
				t->dataType = Integer;
			else if (Integer != leftType)
				invalidOperandError(leftType, &t->childrenNode[0]->location);
			else if (Integer != rightType)
				invalidOperandError(rightType, &t->childrenNode[1]->location);
		}
		break;

	case funCall:
	{
		if (strcmp(t->attr.ch, func_input) == 0) {
			//input函数没有参数
			if (t->childrenNode[0] != NULL)
				argumentNumberError("many", &t->location);
			break;
		}
		else if (strcmp(t->attr.ch, func_output) == 0) {
			//output函数有且只有一个参数，且参数类型是int
			STNode p = t->childrenNode[0];
			if (NULL == p)
				//参数太少
				argumentNumberError("few", &t->location);
			else if (defaultType == p->nodeType
				&& p->brotherNode[0] != NULL
				&& p->brotherNode[0]->nodeType != opType)
				//参数太多
				argumentNumberError("many", &t->location);
			else if (p->dataType != Integer)
				//参数类型不是int
				invalidConversionError(
					p->dataType,
					Integer,
					&p->location);
			break;
		}
		BucketList bl = st_lookup(t->attr.ch, &t->location);
		if (bl != NULL && Function == bl->type)
		{
			t->dataType = bl->attr.info.returnType;
			PL pl = bl->attr.info.params;
			STNode stn = t->childrenNode[0];
			PL args = NULL, arg = NULL;
			LocList locs = NULL, loc = NULL;
			while (stn != NULL && defaultType == stn->nodeType) {
				//保存形参类型
				arg = (PL)malloc(sizeof(struct ParamList));
				arg->type = stn->brotherNode[1]->dataType;
				arg->next = args;
				args = arg;
				//保存位置信息
				loc = (LocList)malloc(sizeof(struct LocationList));
				copyLocation(&loc->loc, &stn->brotherNode[1]->location);
				loc->next = locs;
				locs = loc;
				stn = stn->brotherNode[0];
			}
			if (NULL != stn) {
				//保存形参类型
				arg = (PL)malloc(sizeof(struct ParamList));
				arg->type = stn->dataType;
				arg->next = args;
				args = arg;
				//保存位置信息
				loc = (LocList)malloc(sizeof(struct LocationList));
				copyLocation(&loc->loc, &stn->location);
				loc->next = locs;
				locs = loc;
			}
			while (args != NULL && pl != NULL) {
				if (pl->type != Void && args->type != pl->type)
					invalidConversionError(
						args->type,
						pl->type,
						&locs->loc);
				args = args->next;
				locs = loc->next;
				pl = pl->next;
			}
			if (args != NULL)
			{
				if (NULL == pl)
					argumentNumberError("many", &t->location);
			}
			else if (NULL != pl)
				argumentNumberError("few", &t->location);
			freeLocList(loc);
			freeParamList(arg);
		}

		break;
	}
	case assignStmt:
	{
		Type leftType = t->childrenNode[0]->dataType, rightType = t->childrenNode[1]->dataType;
		if (leftType != Unknown && rightType != Unknown)
		{
			if (leftType != Integer)
				assignmentError(leftType, &t->childrenNode[0]->location);
			else if (rightType != Integer)
				invalidConversionError(rightType, leftType, &t->childrenNode[1]->location);
			else
				t->dataType = Integer;
		}
		break;
	}
	case compoundStmt:
		break;
	case ifStmt:
	case whileStmt:
		if (Integer != t->childrenNode[0]->dataType)
			invalidConversionError(
				t->childrenNode[0]->dataType,
				Integer,
				&t->childrenNode[0]->location);
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

static void checkBrotherNode(STNode t) {
	if (defaultType == t->nodeType && t->brotherNode[1] != NULL)
		t->dataType = t->brotherNode[1]->dataType;
}

/* Procedure typeCheck performs type checking
 * by a postorder syntax tree traversal
 */
void typeCheck(STNode syntaxTree)
{
	traverse(syntaxTree, nullProc, checkNode, checkBrotherNode);
}
