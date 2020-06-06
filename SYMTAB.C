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

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert(char *name, char *type, int lineno, int loc)
{
    //和yyltype的行号和列号进行比较
    int h = hash(name);
    BucketList l = hashTable[h];
    while ((l != NULL) && (strcmp(name, l->name) != 0))
        l = l->next;
    if (l == NULL) /* variable not yet in table */
    {
        l = (BucketList)malloc(sizeof(struct BucketListRec));
        l->name = name;
        l->type = type;
        l->lines = (LineList)malloc(sizeof(struct LineListRec));
        l->lines->lineno = lineno;
        l->memloc = loc;
        l->lines->next = NULL;
        l->next = hashTable[h];
        hashTable[h] = l;
    }
    else /* found in table, so just add line number */
    {
        LineList t = l->lines;
        while (t->next != NULL)
            t = t->next;
        t->next = (LineList)malloc(sizeof(struct LineListRec));
        t->next->lineno = lineno;
        t->next->next = NULL;
    }
} /* st_insert */

/* Function st_lookup returns the memory
 * location of a variable or 0 if not found
 */
BucketList st_lookup(char *name, Loc *loc)
{
    int h = hash(name);
    BucketList l = hashTable[h];
    BucketList p = NULL;
    // while ((l != NULL) && (strcmp(name, l->name) != 0))
    //     l = l->next;
    // if (l == NULL)
    //     return NULL;
    // else
    // {
    //     int result = compareScope(&l->scope, loc);
    //     if (1 == result)
    //     {
    //     }
    //     else if (-2 == result)
    //     {
    //         l = l->next;
    //     }
    // }
    while (l != NULL)
    {
        while ((l != NULL) && (strcmp(name, l->name) != 0))
            l = l->next;
        if (l == NULL)
            return p;
        else
        {
            int result = compareScope(&l->scope, loc);
            if (1 == result)
            {
                p = l;
                l = l->inner;
            }
            else if (-2 == result)
            {
                l = l->next;
            }
        }
    }
    return p;
}

/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */
void printSymTab(FILE *listing)
{
    int i;
    fprintf(listing, "Variable Name  Type       Location  Line Numbers\n");
    fprintf(listing, "-------------  ---------  --------  ------------\n");
    for (i = 0; i < SIZE; ++i)
    {
        if (hashTable[i] != NULL)
        {
            BucketList l = hashTable[i];
            while (l != NULL)
            {
                LineList t = l->lines;
                fprintf(listing, "%-14s ", l->name);
                fprintf(listing, "%-10d  ", l->type);
                fprintf(listing, "%-10d  ", l->memloc);
                while (t != NULL)
                {
                    fprintf(listing, "%4d ", t->lineno);
                    t = t->next;
                }
                fprintf(listing, "\n");
                l = l->next;
            }
        }
    }
} /* printSymTab */
