/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the MINIC compiler                            */
/* (generates code for the TM machine)              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"
#include "yacc.tab.h"

/* tmpOffset is the memory offset for temps
   It is decremented each time a temp is
   stored, and incremeted when loaded again
*/
static int tmpOffset = 0;

//当前函数在符号表中的位置指针
static BucketList curFuncion = NULL;

static void genStmt(STNode tree);

/* prototype for internal recursive code generator */
static void cGen(STNode  tree);

/* Procedure genStmt generates code at a statement node */
static void genStmt(STNode  tree)
{
	STNode  p1, p2, p3;
	int savedLoc1, savedLoc2, currentLoc;
	BucketList list;
	switch (tree->nodeType) {

		//case IfK:
		//	 emitComment("-> if");
		//	p1 = tree->child[0];
		//	p2 = tree->child[1];
		//	p3 = tree->child[2];
		//	/* generate code for test expression */
		//	cGen(p1);
		//	savedLoc1 = emitSkip(1);
		//	emitComment("if: jump to else belongs here");
		//	/* recurse on then part */
		//	cGen(p2);
		//	savedLoc2 = emitSkip(1);
		//	emitComment("if: jump to end belongs here");
		//	currentLoc = emitSkip(0);
		//	emitBackup(savedLoc1);
		//	emitRM_Abs("JEQ", ac, currentLoc, "if: jmp to else");
		//	emitRestore();
		//	/* recurse on else part */
		//	cGen(p3);
		//	currentLoc = emitSkip(0);
		//	emitBackup(savedLoc2);
		//	emitRM_Abs("LDA", pc, currentLoc, "jmp to end");
		//	emitRestore();
		//	  emitComment("<- if");
		//	break; /* if_k */

		//case RepeatK:
		//	 emitComment("-> repeat");
		//	p1 = tree->child[0];
		//	p2 = tree->child[1];
		//	savedLoc1 = emitSkip(0);
		//	emitComment("repeat: jump after body comes back here");
		//	/* generate code for body */
		//	cGen(p1);
		//	/* generate code for test */
		//	cGen(p2);
		//	emitRM_Abs("JEQ", ac, savedLoc1, "repeat: jmp back to body");
		//	  emitComment("<- repeat");
		//	break; /* repeat */


		//case ReadK:
		//	emitRO("IN", ac, 0, 0, "read integer value");
		//	list = st_lookup(tree->attr.name);
		//	emitRM("ST", ac, list, gp, "read: store value");
		//	break;
		//case WriteK:
		//	/* generate code for expression to write */
		//	cGen(tree->child[0]);
		//	/* now output it */
		//	emitRO("OUT", ac, 0, 0, "write ac");
		//	break;
	default:
		break;
	}
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp(STNode  tree)
{
	BucketList list;
	STNode  p1, p2;
	switch (tree->nodeType) {



		//case OpK:
		//	 emitComment("-> Op");
		//	p1 = tree->child[0];
		//	p2 = tree->child[1];
		//	/* gen code for ac = left arg */
		//	cGen(p1);
		//	/* gen code to push left operand */
		//	emitRM("ST", ac, tmpOffset--, mp, "op: push left");
		//	/* gen code for ac = right operand */
		//	cGen(p2);
		//	/* now load left operand */
		//	emitRM("LD", ac1, ++tmpOffset, mp, "op: load left");
		//	switch (tree->attr.op) {
		//	case PLUS:
		//		emitRO("ADD", ac, ac1, ac, "op +");
		//		break;
		//	case MINUS:
		//		emitRO("SUB", ac, ac1, ac, "op -");
		//		break;
		//	case TIMES:
		//		emitRO("MUL", ac, ac1, ac, "op *");
		//		break;
		//	case OVER:
		//		emitRO("DIV", ac, ac1, ac, "op /");
		//		break;
		//	case LT:
		//		emitRO("SUB", ac, ac1, ac, "op <");
		//		emitRM("JLT", ac, 2, pc, "br if true");
		//		emitRM("LDC", ac, 0, ac, "false case");
		//		emitRM("LDA", pc, 1, pc, "unconditional jmp");
		//		emitRM("LDC", ac, 1, ac, "true case");
		//		break;
		//	case EQ:
		//		emitRO("SUB", ac, ac1, ac, "op ==");
		//		emitRM("JEQ", ac, 2, pc, "br if true");
		//		emitRM("LDC", ac, 0, ac, "false case");
		//		emitRM("LDA", pc, 1, pc, "unconditional jmp");
		//		emitRM("LDC", ac, 1, ac, "true case");
		//		break;
		//	default:
		//		emitComment("BUG: Unknown operator");
		//		break;
		//	} /* case op */
		//	  emitComment("<- Op");
		//	break; /* OpK */

	default:
		break;
	}
} /* genExp */

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen(STNode  tree)
{
	if (tree != NULL)
	{
		STNode  p1, p2, p3;
		int savedLoc1, savedLoc2, currentLoc;
		BucketList list;
		switch (tree->nodeType) {
		case constType:
			emitComment("-> Const");
			/* gen code to load integer constant using LDC */
			emitRM("LDC", ac, tree->attr.value, 0, "load const");
			emitComment("<- Const");
			break;
		case varType:
			list = st_lookup(tree->attr.ch, &tree->location);
			if (strcmp(list->type, typeString[Integer]) == 0) {
				//int类型变量
				emitComment("-> Id");
				emitRM("LD", ac, list->memloc, gp, "load id value");
				emitComment("<- Id");
			}
			else {
				//数组
				emitComment("-> Array");
				cGen(tree->childrenNode[0]);
				emitRM("ST", ac, tmpOffset--, mp, "array: push index");
				emitRM("LDC", ac, list->memloc, 0, "load const");
				emitRM("LD", ac1, ++tmpOffset, mp, "array: load index");
				emitRO("ADD", ac, ac, ac1, "array add index");
				emitRM("LDR", ac, ac, gp, "load id value");
				emitComment("<- Array");
			}
			break;
		case defaultType:
			if (tree->brotherNode[0] != NULL && tree->brotherNode[1] != NULL) {
				if (opType == tree->brotherNode[0]->nodeType) {
					//简单表达式
					emitComment("-> Op");
					p1 = tree->brotherNode[1]->childrenNode[0];
					p2 = tree->brotherNode[1]->childrenNode[1];
					//左操作数
					cGen(p1);
					emitRM("ST", ac, tmpOffset--, mp, "op: push left");
					//右操作数
					cGen(p2);
					emitRM("LD", ac1, ++tmpOffset, mp, "op: load left");
					switch (tree->brotherNode[0]->dataType) {
					case ADD:
						emitRO("ADD", ac, ac1, ac, "op +");
						break;
					case SUB:
						emitRO("SUB", ac, ac1, ac, "op -");
						break;
					case MUL:
						emitRO("MUL", ac, ac1, ac, "op *");
						break;
					case DIV:
						emitRO("DIV", ac, ac1, ac, "op /");
						break;
					case LESS_OR_EQUAL:
						emitRO("SUB", ac, ac1, ac, "op <=");
						emitRM("JLE", ac, 2, pc, "br if true");
						emitRM("LDC", ac, 0, ac, "false case");
						emitRM("LDA", pc, 1, pc, "unconditional jmp");
						emitRM("LDC", ac, 1, ac, "true case");
					case LESS:
						emitRO("SUB", ac, ac1, ac, "op <");
						emitRM("JLT", ac, 2, pc, "br if true");
						emitRM("LDC", ac, 0, ac, "false case");
						emitRM("LDA", pc, 1, pc, "unconditional jmp");
						emitRM("LDC", ac, 1, ac, "true case");
						break;
					case EQUAL:
						emitRO("SUB", ac, ac1, ac, "op ==");
						emitRM("JEQ", ac, 2, pc, "br if true");
						emitRM("LDC", ac, 0, ac, "false case");
						emitRM("LDA", pc, 1, pc, "unconditional jmp");
						emitRM("LDC", ac, 1, ac, "true case");
						break;
					case NOT_EQUAL:
						emitRO("SUB", ac, ac1, ac, "op !=");
						emitRM("JNE", ac, 2, pc, "br if true");
						emitRM("LDC", ac, 0, ac, "false case");
						emitRM("LDA", pc, 1, pc, "unconditional jmp");
						emitRM("LDC", ac, 1, ac, "true case");
						break;
					case GREA_OR_EQUAL:
						emitRO("SUB", ac, ac1, ac, "op >=");
						emitRM("JGE", ac, 2, pc, "br if true");
						emitRM("LDC", ac, 0, ac, "false case");
						emitRM("LDA", pc, 1, pc, "unconditional jmp");
						emitRM("LDC", ac, 1, ac, "true case");
					case GREA:
						emitRO("SUB", ac, ac1, ac, "op >");
						emitRM("JGT", ac, 2, pc, "br if true");
						emitRM("LDC", ac, 0, ac, "false case");
						emitRM("LDA", pc, 1, pc, "unconditional jmp");
						emitRM("LDC", ac, 1, ac, "true case");
						break;
					default:
						emitComment("BUG: Unknown operator");
						break;
					}
					emitComment("<- Op");
				}
			}
			break;
		case assignStmt:
			emitComment("-> assign");
			/* generate code for rhs */
			cGen(tree->childrenNode[1]);
			/* now store value */
			list = st_lookup(
				tree->childrenNode[0]->attr.ch,
				&tree->childrenNode[0]->location);
			if (strcmp(list->type, typeString[Integer]) == 0) {
				//int类型变量
				emitComment("-> Id");
				emitRM("ST", ac, list->memloc, gp, "assign: store value");
				emitComment("<- Id");
			}
			else {
				//数组
				emitRM("ST", ac, tmpOffset--, mp, "assign: push right");
				emitComment("-> Array");
				//数组下标
				cGen(tree->childrenNode[0]->childrenNode[0]);

				emitRM("ST", ac, tmpOffset--, mp, "array: push index");
				emitRM("LDC", ac, list->memloc, 0, "load const");
				emitRM("LD", ac1, ++tmpOffset, mp, "array: load index");
				emitRO("ADD", ac, ac, ac1, "array add index");
				emitRM("LD", ac1, ++tmpOffset, mp, "assign: load right");
				emitRM("STR", ac1, ac, gp, "assign: store value"); //dMem[reg[ac]+reg[gp]] = reg[ac1]
				emitRM("LDR", ac, ac, gp, "load id value");
				emitComment("<- Array");
			}
			emitComment("<- assign");
			break;
		case funCall:
		{
			if (strcmp(tree->attr.ch, func_input) == 0) {
				//input函数
				emitRO("IN", ac, 0, 0, "input integer value");
			}
			else if (strcmp(tree->attr.ch, func_output) == 0) {
				//output函数
				cGen(tree->childrenNode[0]);
				emitRO("OUT", ac, 0, 0, "output ac");
			}
			else {
				//保存相应局部变量的值
				if (curFuncion != NULL) {
					int i = 0,
						start = curFuncion->memloc + 2,
						total = curFuncion->last_memloc - start + 1;
					currentLoc = emitSkip(0);
					emitRM("STC", sp, currentLoc, 0, "save current location");
					emitRM("LDA", sp, 1, sp, "move stack pointer");
					emitRM("LDM", start, total, sp, "save local variables");
					emitRM("LDA", sp, total, sp, "move stack pointer");
					emitRM("STC", sp, total, 0, "save number of local variables");
					emitRM("LDA", sp, 1, sp, "move stack pointer");
					emitRM("STC", sp, curFuncion->last_memloc, 0, "save last memloc");
					emitRM("LDA", sp, 1, sp, "move stack pointer");
				}
				//跳转到被调用的函数的入口
				list = st_lookup(tree->attr.ch, &tree->location);
				emitRM("LD", pc, list->memloc, gp, "load entry to a function");
			}
			break;
		}
		case funDeclaration:
		{
			bool isMain = (strcmp(tree->attr.ch, "main") == 0);
			if (!isMain)
			{
				//如果不是main函数则跳过
				savedLoc1 = emitSkip(2);
				emitComment("Jump to end of function belongs here");
			}
			if (TraceCode) fprintf(code, "* --- Function %s ---\n", tree->attr.ch);
			//存储函数入口
			list = st_lookup(tree->attr.ch, &tree->location);
			curFuncion = list;
			currentLoc = emitSkip(0);
			emitRM("LDC", ac, currentLoc, 0, "load const");
			emitRM("ST", ac, list->memloc, gp, "store value");
			//存储last_memloc
			emitRM("LDC", ac, list->last_memloc, 0, "load const");
			emitRM("ST", ac, list->memloc + 1, gp, "store value");
			cGen(tree->childrenNode[2]);
			if (TraceCode) fprintf(code, "* --- End of Function %s ---\n", tree->attr.ch);
			if (isMain)
				//如果是main函数，则程序结束
				emitRO("HALT", 0, 0, 0, "");
			else {
				//如果不是main函数，则回到调用该函数的地方
				emitRM("STM", 0, 0, sp, "recover local variables");
				emitRM("LDSR", pc, 0, sp, "back to function call");
				emitRM("LDA", sp, -1, sp, "move stack pointer");
			}
			if (!isMain)
			{
				//如果不是main函数则跳过
				currentLoc = emitSkip(0);
				emitBackup(savedLoc1);
				emitRM("LDC", ac, 1, 0, "load const");
				emitRM_Abs("JEQ", ac, currentLoc, "Jump to end of function");
				emitRestore();
			}
			break;
		}
		case compoundStmt:
			cGen(tree->childrenNode[1]);
			//TODO
			break;
		case ifStmt:
			emitComment("-> if");
			p1 = tree->childrenNode[0];
			p2 = tree->childrenNode[1];
			p3 = tree->childrenNode[2];
			/* generate code for test expression */
			cGen(p1);
			savedLoc1 = emitSkip(1);
			emitComment("if: jump to else belongs here");
			/* recurse on then part */
			cGen(p2);
			savedLoc2 = emitSkip(1);
			emitComment("if: jump to end belongs here");
			currentLoc = emitSkip(0);
			emitBackup(savedLoc1);
			emitRM_Abs("JEQ", ac, currentLoc, "if: jmp to else");
			emitRestore();
			/* recurse on else part */
			cGen(p3);
			currentLoc = emitSkip(0);
			emitBackup(savedLoc2);
			emitRM_Abs("LDA", pc, currentLoc, "jmp to end");
			emitRestore();
			emitComment("<- if");
			break;
		case whileStmt:
			emitComment("-> while");
			p1 = tree->childrenNode[0];
			p2 = tree->childrenNode[1];
			savedLoc1 = emitSkip(0);
			emitComment("while: jump after body comes back here");
			/* generate code for test */
			cGen(p1);
			savedLoc2 = emitSkip(1);
			emitComment("while: jump to end belongs here");
			/* generate code for body */
			cGen(p2);
			emitRM_Abs("LDA", pc, savedLoc1, "while: jmp back to test");
			currentLoc = emitSkip(0);
			emitBackup(savedLoc2);
			emitRM_Abs("JEQ", ac, currentLoc, "while: jmp to end");
			emitRestore();
			emitComment("<- while");
			break;

		case returnStmt:
			emitComment("->return");
			cGen(tree->childrenNode[0]);
			emitComment("<-return");
			if (strcmp(curFuncion->name, "main") == 0) {
				//如果不是main函数，则回到调用该函数的地方
				emitRM("STM", 0, 0, sp, "recover local variables");
				emitRM("LDSR", pc, 0, sp, "back to function call");
				emitRM("LDA", sp, -1, sp, "move stack pointer");
			}
			break;
		default:
			for (int i = 0; i < MAXNUM; i++)
				cGen(tree->childrenNode[i]);
			break;
		}
		for (int i = 0; i < MAXBRONUM; i++)
			cGen(tree->brotherNode[i]);
	}
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void codeGen(STNode * syntaxTree, char * codefile)
{
	char * s = malloc(strlen(codefile) + 7);
	strcpy(s, "File: ");
	strcat(s, codefile);
	emitComment("MINIC Compilation to TM Code");
	emitComment(s);
	/* generate standard prelude */
	emitComment("Standard prelude:");
	emitRM("LD", mp, 0, ac, "load maxaddress from location 0");
	emitRM("ST", ac, 0, ac, "clear location 0");
	emitComment("End of standard prelude.");
	/* generate code for MINIC program */
	cGen(syntaxTree);
	/* finish */
	emitComment("End of execution.");
	emitRO("HALT", 0, 0, 0, "");
}
