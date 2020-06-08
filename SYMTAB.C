/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the TINY compiler*/
/* (allows only one symbol table)                   */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "globals.h"
#include "stack.h"
#include "utils.h"

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

   /* the hash table */
static BucketList hashTable[SIZE];

/* the hash function */
static int hash(char *key)
{
	int temp = 0;
	int i = 0;
	while (key[i] != '\0')
	{
		temp = ((temp << SHIFT) + key[i]) % SIZE;
		++i;
	}
	return temp;
}
void insertBucketList(char *name, char *type, int lineno, int loc, int len, STNode t)
{
	int h = hash(name);
	BucketList l = (BucketList)malloc(sizeof(struct BucketListRec));
	l->name = name;
	l->type = type;
	l->attr.length = 0;
	copyLocation(&l->scope, getTop());
	l->lines = (LineList)malloc(sizeof(struct LineListRec));
	l->lines->lineno = lineno;
	l->lines->next = NULL;
	l->memloc = loc;
	l->next = hashTable[h];
	hashTable[h] = l;
	if (strcmp(type, "array") == 0)
		l->attr.length = len;
	if (strcmp(type, "function") == 0)
	{
		Loc scope = { t->location.first_line,
					 t->location.first_column,
					 t->childrenNode[2]->location.last_line,
					 t->childrenNode[2]->location.last_column };
		push(&scope);
		if (strcmp(t->childrenNode[0]->attr.ch, "int") == 0)
			l->attr.info.returnType = Integer;
		else
			l->attr.info.returnType = Void;
		//params
		l->attr.info.params = NULL;
		STNode p = t->childrenNode[1];
		char * paramType = "";
		if (p != NULL)
		{
			while (defaultType == p->nodeType)
			{
				PL pl = (PL)malloc(sizeof(struct ParamList));
				paramType = p->brotherNode[1]->childrenNode[0]->attr.ch;
				if (strcmp(paramType, "int") == 0)
				{
					pl->type = Integer;
					if (p->brotherNode[1]->childrenNode[1]->childrenNode[0] != NULL)
						pl->type = Array;
				}
				else if (strcmp(paramType, "void") == 0)
					pl->type = Void;
				pl->next = l->attr.info.params;
				l->attr.info.params = pl;
				p = p->brotherNode[0];
			}
			// p->nodeType为varDeclaration
			PL pl = (PL)malloc(sizeof(struct ParamList));
			paramType = p->childrenNode[0]->attr.ch;
			if (strcmp(paramType, "int") == 0)
			{
				pl->type = Integer;
				if (p->childrenNode[1]->childrenNode[0] != NULL)
					pl->type = Array;
			}
			else if (strcmp(paramType, "void") == 0)
				pl->type = Void;
			pl->next = l->attr.info.params;
			l->attr.info.params = pl;
		}
	}
}

void insertLineList(BucketList l, int lineno)
{
	LineList t = l->lines;
	while (t->next != NULL)
		t = t->next;
	t->next = (LineList)malloc(sizeof(struct LineListRec));
	t->next->lineno = lineno;
	t->next->next = NULL;
}

/* Function st_lookup returns the memory
 * location of a variable or 0 if not found
 */
BucketList st_lookup(char *name, Loc *loc)
{
	int h = hash(name);
	BucketList l = hashTable[h];
	BucketList p = NULL;
	// while (l != NULL)
	// {
	//     while ((l != NULL) && (strcmp(name, l->name) != 0))
	//         l = l->next;
	//     if (l == NULL)
	//         return p;
	//     else
	//     {
	//         int result = compareScope(&l->scope, loc);
	//         if (1 == result)
	//         {
	//             p = l;
	//             l = l->inner;
	//         }
	//         else if (-2 == result)
	//         {
	//             l = l->next;
	//         }
	//     }
	// }

	while ((l != NULL) && (strcmp(name, l->name) != 0) && compareScope(&l->scope, loc) != 1)
		l = l->next;
	if (l == NULL)
		return NULL;
	else
		return l;
}

/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */
void printSymTab(FILE *listing)
{
	int i;
	fprintf(listing, "VariableName   Type       Scope               Location  LineNumbers\n");
	fprintf(listing, "-------------  ---------  ------------------  --------  ------------\n");
	for (i = 0; i < SIZE; ++i)
	{
		if (hashTable[i] != NULL)
		{
			BucketList l = hashTable[i];
			while (l != NULL)
			{
				LineList t = l->lines;
				fprintf(listing, "%-14s ", l->name);
				fprintf(listing, "%-8s  ", l->type);
				fprintf(listing, "(%4d:%-3d,%4d:%-3d)  ",
					l->scope.first_line,
					l->scope.first_column,
					l->scope.last_line,
					l->scope.last_column);
				fprintf(listing, "%-8d  ", l->memloc);
				while (t != NULL)
				{
					fprintf(listing, "%-4d ", t->lineno);
					t = t->next;
				}
				fprintf(listing, "\n");
				l = l->next;
			}
		}
	}
} /* printSymTab */
