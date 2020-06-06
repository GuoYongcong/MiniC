typedef union{
    int value;
    char* ch;
    struct Node* node;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#define	ELSE	257
#define	IF	258
#define	RETURN	259
#define	WHILE	260
#define	INT	261
#define	VOID	262
#define	ADD	263
#define	SUB	264
#define	MUL	265
#define	DIV	266
#define	LESS	267
#define	LESS_OR_EQUAL	268
#define	GREA	269
#define	GREA_OR_EQUAL	270
#define	EQUAL	271
#define	NOT_EQUAL	272
#define	ASSI	273
#define	SEM	274
#define	COM	275
#define	LP	276
#define	RP	277
#define	LS	278
#define	RS	279
#define	LC	280
#define	RC	281
#define	ID	282
#define	NUM	283
#define	LOWER_ELSE	284


extern YYSTYPE yylval;
