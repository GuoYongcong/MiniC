/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the TINY compiler     */
/* (allows only one symbol table)                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

void insertBucketList(char *name, char *type, int lineno, int loc);

void insertLineList(BucketList l, int lineno);

/* Function st_lookup returns the memory
 * location of a variable or 0 if not found
 */
BucketList st_lookup(char *name, Loc *loc);

/* Procedure printSymTab prints a formatted
 * listing of the symbol table contents
 * to the listing file
 */
void printSymTab(FILE *);

#endif
