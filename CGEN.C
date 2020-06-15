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
		//	if (TraceCode) emitComment("-> if");
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
		//	if (TraceCode)  emitComment("<- if");
		//	break; /* if_k */

		//case RepeatK:
		//	if (TraceCode) emitComment("-> repeat");
		//	p1 = tree->child[0];
		//	p2 = tree->child[1];
		//	savedLoc1 = emitSkip(0);
		//	emitComment("repeat: jump after body comes back here");
		//	/* generate code for body */
		//	cGen(p1);
		//	/* generate code for test */
		//	cGen(p2);
		//	emitRM_Abs("JEQ", ac, savedLoc1, "repeat: jmp back to body");
		//	if (TraceCode)  emitComment("<- repeat");
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
		//	if (TraceCode) emitComment("-> Op");
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
		//	if (TraceCode)  emitComment("<- Op");
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
			if (TraceCode) emitComment("-> Const");
			/* gen code to load integer constant using LDC */
			emitRM("LDC", ac, tree->attr.value, 0, "load const");
			if (TraceCode)  emitComment("<- Const");
			break;
		case varType:
			list = st_lookup(tree->attr.ch, &tree->location);
			if (strcmp(list->type, typeString[Integer]) == 0) {
				//int类型变量
				if (TraceCode) emitComment("-> Id");
				emitRM("LD", ac, list->memloc, gp, "load id value");
				if (TraceCode)  emitComment("<- Id");
			}
			else {
				//数组
				if (TraceCode) emitComment("-> Array");
				cGen(tree->childrenNode[0]);
				emitRM("ST", ac, tmpOffset--, mp, "array: push index");
				emitRM("LDC", ac, list->memloc, 0, "load const");
				emitRM("LD", ac1, ++tmpOffset, mp, "array: load index");
				emitRO("ADD", ac, ac, ac1, "op +");
				emitRM("LDR", ac, ac, gp, "load id value");
				if (TraceCode) emitComment("<- Array");
			}
			break;
		case defaultType:
			if (tree->brotherNode[0] != NULL && tree->brotherNode[1] != NULL) {
				if (opType == tree->brotherNode[0]->nodeType) {
					//简单表达式
					if (TraceCode) emitComment("-> Op");
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
					default:
						emitComment("BUG: Unknown operator");
						break;
					} /* case op */
					if (TraceCode)  emitComment("<- Op");
				}
			}
			break;
		case assignStmt:
			if (TraceCode) emitComment("-> assign");
			/* generate code for rhs */
			cGen(tree->childrenNode[1]);
			/* now store value */
			list = st_lookup(
				tree->childrenNode[0]->attr.ch,
				&tree->childrenNode[0]->location);
			if (strcmp(list->type, typeString[Integer]) == 0) {
				//int类型变量
				if (TraceCode) emitComment("-> Id");
				emitRM("ST", ac, list->memloc, gp, "assign: store value");
				if (TraceCode)  emitComment("<- Id");
			}
			else {
				//数组
				emitRM("ST", ac, tmpOffset--, mp, "assign: push right");
				if (TraceCode) emitComment("-> Array");
				//数组下标
				cGen(tree->childrenNode[0]->childrenNode[0]);

				emitRM("ST", ac, tmpOffset--, mp, "array: push index");
				emitRM("LDC", ac, list->memloc, 0, "load const");
				emitRM("LD", ac1, ++tmpOffset, mp, "array: load index");
				emitRO("ADD", ac, ac, ac1, "op +");
				emitRM("LD", ac1, ++tmpOffset, mp, "assign: load right");
				emitRM("STR", ac1, ac, gp, "assign: store value"); //dMem[reg[ac]+reg[gp]] = reg[ac1]
				emitRM("LDR", ac, ac, gp, "load id value");
				if (TraceCode) emitComment("<- Array");
			}
			if (TraceCode)  emitComment("<- assign");
			break;
		case funCall:
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
				//TODO
				;
			}
			break;
		case funDeclaration:
			cGen(tree->childrenNode[2]);
			//TODO
			break;
		case compoundStmt:
			cGen(tree->childrenNode[1]);
			//TODO
			break;
		case ifStmt:
			if (TraceCode) emitComment("-> if");
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
			if (TraceCode)  emitComment("<- if");
			break;
		case whlieStmt:
			break;
		case returnStmt:
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
