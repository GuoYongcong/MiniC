
/*  A Bison parser, made from yacc.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

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

#line 13 "yacc.y"

#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "utils.h"

//打印语法错误
void yyerror(const char *str);
//行号
extern int yylineno;
//列号
extern int columnno;
//token
extern char *yytext;
//语法树根结点
struct Node * treeRoot = 0; 

#line 30 "yacc.y"
typedef union{ 
    int value;
    char* ch;
    struct Node* node;
} YYSTYPE;
#ifndef YYDEBUG
#define YYDEBUG 1
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		103
#define	YYFLAG		-32768
#define	YYNTBASE	31

#define YYTRANSLATE(x) ((unsigned)(x) <= 284 ? yytranslate[x] : 60)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,     9,    11,    13,    17,    24,    26,
    28,    35,    37,    39,    43,    45,    48,    53,    58,    61,
    62,    65,    66,    68,    70,    72,    74,    76,    79,    81,
    89,    95,   101,   105,   108,   112,   114,   116,   121,   123,
   127,   129,   131,   133,   135,   137,   139,   143,   145,   147,
   149,   153,   155,   157,   159,   163,   165,   167,   169,   174,
   176,   177,   181
};

static const short yyrhs[] = {    32,
     0,    32,    33,     0,    48,     0,    33,     0,    34,     0,
    36,     0,    35,    28,    20,     0,    35,    28,    24,    29,
    25,    20,     0,     7,     0,     8,     0,    35,    28,    22,
    37,    23,    40,     0,    38,     0,     8,     0,    38,    21,
    39,     0,    39,     0,    35,    28,     0,    35,    28,    24,
    25,     0,    26,    41,    42,    27,     0,    41,    34,     0,
     0,    42,    43,     0,     0,    44,     0,    40,     0,    45,
     0,    46,     0,    47,     0,    48,    20,     0,    20,     0,
     4,    22,    48,    23,    43,     3,    43,     0,     4,    22,
    48,    23,    43,     0,     6,    22,    48,    23,    43,     0,
     5,    48,    20,     0,     5,    20,     0,    49,    19,    48,
     0,    50,     0,    28,     0,    28,    24,    48,    25,     0,
    52,     0,    52,    51,    52,     0,    14,     0,    13,     0,
    16,     0,    15,     0,    17,     0,    18,     0,    52,    53,
    54,     0,    54,     0,     9,     0,    10,     0,    54,    55,
    56,     0,    56,     0,    11,     0,    12,     0,    22,    48,
    23,     0,    49,     0,    57,     0,    29,     0,    28,    22,
    58,    23,     0,    59,     0,     0,    59,    21,    48,     0,
    48,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    71,    73,    74,    75,    77,    78,    80,    84,    90,    91,
    93,    95,    96,    98,    99,   101,   105,   110,   112,   113,
   115,   116,   118,   119,   120,   121,   122,   124,   125,   127,
   128,   130,   132,   133,   136,   137,   139,   140,   142,   143,
   148,   149,   150,   151,   152,   153,   155,   159,   161,   162,
   164,   168,   170,   171,   173,   174,   175,   176,   178,   180,
   181,   183,   184
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","ELSE","IF",
"RETURN","WHILE","INT","VOID","ADD","SUB","MUL","DIV","LESS","LESS_OR_EQUAL",
"GREA","GREA_OR_EQUAL","EQUAL","NOT_EQUAL","ASSI","SEM","COM","LP","RP","LS",
"RS","LC","RC","ID","NUM","LOWER_ELSE","program","declaration_list","declaration",
"var_declaration","tpye_specifier","fun_declaration","params","param_list","param",
"compound_stmt","local_declaration","statement_list","statement","expression_stmt",
"selection_stmt","iteration_stmt","return_stmt","expression","var","simple_expression",
"relop","additive_expression","addop","term","mulop","factor","call","args",
"arg_list", NULL
};
#endif

static const short yyr1[] = {     0,
    31,    32,    32,    32,    33,    33,    34,    34,    35,    35,
    36,    37,    37,    38,    38,    39,    39,    40,    41,    41,
    42,    42,    43,    43,    43,    43,    43,    44,    44,    45,
    45,    46,    47,    47,    48,    48,    49,    49,    50,    50,
    51,    51,    51,    51,    51,    51,    52,    52,    53,    53,
    54,    54,    55,    55,    56,    56,    56,    56,    57,    58,
    58,    59,    59
};

static const short yyr2[] = {     0,
     1,     2,     1,     1,     1,     1,     3,     6,     1,     1,
     6,     1,     1,     3,     1,     2,     4,     4,     2,     0,
     2,     0,     1,     1,     1,     1,     1,     2,     1,     7,
     5,     5,     3,     2,     3,     1,     1,     4,     1,     3,
     1,     1,     1,     1,     1,     1,     3,     1,     1,     1,
     3,     1,     1,     1,     3,     1,     1,     1,     4,     1,
     0,     3,     1
};

static const short yydefact[] = {     0,
     9,    10,     0,    37,    58,     1,     4,     5,     0,     6,
     3,    56,    36,    39,    48,    52,    57,     0,    61,     0,
     2,     0,     0,    49,    50,    42,    41,    44,    43,    45,
    46,     0,     0,    53,    54,     0,    55,    63,     0,    60,
     0,     7,     0,     0,    35,    56,    40,    47,    51,    59,
     0,    38,    10,     0,     0,    12,    15,     0,    62,    16,
     0,     0,     0,     0,    20,    11,    14,     8,    17,    22,
    19,     0,     0,     0,     0,     0,     0,    29,    18,    24,
    21,    23,    25,    26,    27,     0,     0,    34,     0,     0,
    28,     0,    33,     0,     0,     0,    31,    32,     0,    30,
     0,     0,     0
};

static const short yydefgoto[] = {   101,
     6,     7,     8,     9,    10,    55,    56,    57,    80,    70,
    73,    81,    82,    83,    84,    85,    86,    12,    13,    32,
    14,    33,    15,    36,    16,    17,    39,    40
};

static const short yypact[] = {    20,
-32768,-32768,   -11,    -8,-32768,    38,-32768,-32768,   -21,-32768,
-32768,    -4,-32768,    51,    59,-32768,-32768,    -1,   -11,   -11,
-32768,    17,   -11,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   -11,   -11,-32768,-32768,   -11,-32768,-32768,     2,    19,
    13,-32768,    55,    26,-32768,-32768,    63,    59,-32768,-32768,
   -11,-32768,    52,    46,    54,    57,-32768,    56,-32768,    58,
    53,    38,    60,    61,-32768,-32768,-32768,-32768,-32768,    38,
-32768,    64,     4,   -19,    62,   -16,    66,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,    65,   -11,-32768,    69,   -11,
-32768,    68,-32768,    70,    30,    30,    80,-32768,    30,-32768,
    94,    95,-32768
};

static const short yypgoto[] = {-32768,
-32768,    90,    27,   -41,-32768,-32768,-32768,    36,    39,-32768,
-32768,   -52,-32768,-32768,-32768,-32768,     0,    21,-32768,-32768,
    67,-32768,    71,-32768,    72,-32768,-32768,-32768
};


#define	YYLAST		108


static const short yytable[] = {    11,
    42,    54,    18,    88,    44,     3,    22,    75,    76,    77,
     3,     4,     5,    19,    23,    20,     4,     5,    38,    41,
    54,    37,    45,    78,    50,     3,     1,     2,    72,    65,
    79,     4,     5,    75,    76,    77,    42,    52,    43,    51,
    44,     3,    97,    98,     1,     2,   100,     4,     5,    78,
    59,     3,    46,    46,    58,    65,    46,     4,     5,    24,
    25,     1,    53,    26,    27,    28,    29,    30,    31,    34,
    35,    24,    25,    60,   -13,    89,    61,    62,    65,    68,
    63,    64,    99,    87,    91,    69,    92,    90,    93,    94,
    95,    74,    96,   102,   103,    21,    71,    67,    47,    66,
     0,     0,     0,    48,     0,     0,     0,    49
};

static const short yycheck[] = {     0,
    20,    43,     3,    20,    24,    22,    28,     4,     5,     6,
    22,    28,    29,    22,    19,    24,    28,    29,    19,    20,
    62,    23,    23,    20,    23,    22,     7,     8,    70,    26,
    27,    28,    29,     4,     5,     6,    20,    25,    22,    21,
    24,    22,    95,    96,     7,     8,    99,    28,    29,    20,
    51,    22,    32,    33,    29,    26,    36,    28,    29,     9,
    10,     7,     8,    13,    14,    15,    16,    17,    18,    11,
    12,     9,    10,    28,    23,    76,    23,    21,    26,    20,
    25,    24,     3,    22,    20,    25,    87,    22,    20,    90,
    23,    28,    23,     0,     0,     6,    70,    62,    32,    61,
    -1,    -1,    -1,    33,    -1,    -1,    -1,    36
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/local/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/local/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 71 "yacc.y"
{treeRoot=createSyntaxTreeNode(program, 0,yyvsp[0].node,0,0);;
    break;}
case 2:
#line 73 "yacc.y"
{yyval.node=addBrotherNode(yyvsp[-1].node, yyvsp[0].node);;
    break;}
case 3:
#line 74 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 4:
#line 75 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 5:
#line 77 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 6:
#line 78 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 7:
#line 80 "yacc.y"
{
                    struct Node * n1=createSyntaxTreeNode(idType, yyvsp[-1].ch, 0,0,0);
                    yyval.node=createSyntaxTreeNode(varDeclaration, 0, yyvsp[-2].node, n1,0);
;
    break;}
case 8:
#line 84 "yacc.y"
{
                    struct Node * n1=createSyntaxTreeNode(constType, yyvsp[-2].value, 0,0,0);
                    struct Node * n2=createSyntaxTreeNode(idType, yyvsp[-4].ch, n1,0,0);
                    yyval.node=createSyntaxTreeNode(varDeclaration, 0, yyvsp[-5].node, n2, 0);
;
    break;}
case 9:
#line 90 "yacc.y"
{yyval.node=createSyntaxTreeNode(typeType, yyvsp[0].ch, 0,0,0); ;
    break;}
case 10:
#line 91 "yacc.y"
{yyval.node=createSyntaxTreeNode(typeType, yyvsp[0].ch, 0,0,0);;
    break;}
case 11:
#line 93 "yacc.y"
{yyval.node=createSyntaxTreeNode(funDeclaration, yyvsp[-4].ch, yyvsp[-5].node, yyvsp[-2].node, yyvsp[0].node);;
    break;}
case 12:
#line 95 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 13:
#line 96 "yacc.y"
{yyval.node=0;;
    break;}
case 14:
#line 98 "yacc.y"
{yyval.node=addBrotherNode(yyvsp[-2].node, yyvsp[0].node);;
    break;}
case 15:
#line 99 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 16:
#line 101 "yacc.y"
{
    struct Node * n1=createSyntaxTreeNode(idType, yyvsp[0].ch, 0,0,0);
    yyval.node=createSyntaxTreeNode(varDeclaration, 0, yyvsp[-1].node, n1,0);
;
    break;}
case 17:
#line 105 "yacc.y"
{
    struct Node * n1=createSyntaxTreeNode(idType, yyvsp[-2].ch, 0,0,0);
    yyval.node=createSyntaxTreeNode(varDeclaration, 0,yyvsp[-3].node, n1,0);
;
    break;}
case 18:
#line 110 "yacc.y"
{yyval.node=createSyntaxTreeNode(compoundStmt, 0,yyvsp[-2].node, yyvsp[-1].node,0); ;
    break;}
case 19:
#line 112 "yacc.y"
{yyval.node=addBrotherNode(yyvsp[-1].node, yyvsp[0].node); ;
    break;}
case 20:
#line 113 "yacc.y"
{yyval.node=0;;
    break;}
case 21:
#line 115 "yacc.y"
{yyval.node=addBrotherNode(yyvsp[-1].node, yyvsp[0].node); ;
    break;}
case 22:
#line 116 "yacc.y"
{yyval.node=0;;
    break;}
case 23:
#line 118 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 24:
#line 119 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 25:
#line 120 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 26:
#line 121 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 27:
#line 122 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 28:
#line 124 "yacc.y"
{yyval.node=yyvsp[-1].node;;
    break;}
case 29:
#line 125 "yacc.y"
{yyval.node=0;;
    break;}
case 30:
#line 127 "yacc.y"
{yyval.node=createSyntaxTreeNode(ifStmt, 0,yyvsp[-4].node, yyvsp[-2].node, yyvsp[0].node);;
    break;}
case 31:
#line 128 "yacc.y"
{yyval.node=createSyntaxTreeNode(ifStmt, 0, yyvsp[-2].node, yyvsp[0].node,0);;
    break;}
case 32:
#line 130 "yacc.y"
{yyval.node=createSyntaxTreeNode(whlieStmt, 0, yyvsp[-2].node, yyvsp[0].node,0);;
    break;}
case 33:
#line 132 "yacc.y"
{yyval.node=createSyntaxTreeNode(returnStmt, 0 ,yyvsp[-1].node,0,0);;
    break;}
case 34:
#line 133 "yacc.y"
{yyval.node=createSyntaxTreeNode(returnStmt, 0, 0,0,0);;
    break;}
case 35:
#line 136 "yacc.y"
{yyval.node=createSyntaxTreeNode(assignStmt, 0, yyvsp[-2].node, yyvsp[0].node,0);;
    break;}
case 36:
#line 137 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 37:
#line 139 "yacc.y"
{yyval.node=createSyntaxTreeNode(idType, yyvsp[0].ch, 0,0,0);;
    break;}
case 38:
#line 140 "yacc.y"
{yyval.node=createSyntaxTreeNode(idType, yyvsp[-3].ch,yyvsp[-1].node,0,0);;
    break;}
case 39:
#line 142 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 40:
#line 143 "yacc.y"
{
    struct Node * n = createSyntaxTreeNode(defaultType,0, yyvsp[-2].node, yyvsp[0].node, 0);
    yyval.node=addBrotherNode(yyvsp[-1].node, n);
;
    break;}
case 41:
#line 148 "yacc.y"
{ yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 42:
#line 149 "yacc.y"
{ yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 43:
#line 150 "yacc.y"
{ yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 44:
#line 151 "yacc.y"
{ yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 45:
#line 152 "yacc.y"
{ yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 46:
#line 153 "yacc.y"
{ yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 47:
#line 155 "yacc.y"
{
    struct Node * n = createSyntaxTreeNode(defaultType,0, yyvsp[-2].node, yyvsp[0].node, 0);
    yyval.node=addBrotherNode(yyvsp[-1].node, n);
;
    break;}
case 48:
#line 159 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 49:
#line 161 "yacc.y"
{yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 50:
#line 162 "yacc.y"
{yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 51:
#line 164 "yacc.y"
{
    struct Node * n = createSyntaxTreeNode(defaultType,0, yyvsp[-2].node, yyvsp[0].node, 0);
    yyval.node=addBrotherNode(yyvsp[-1].node, n);
;
    break;}
case 52:
#line 168 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 53:
#line 170 "yacc.y"
{yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 54:
#line 171 "yacc.y"
{yyval.node=createSyntaxTreeNode(opType, yyvsp[0].ch, 0,0,0);;
    break;}
case 55:
#line 173 "yacc.y"
{yyval.node=yyvsp[-1].node;;
    break;}
case 56:
#line 174 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 57:
#line 175 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 58:
#line 176 "yacc.y"
{yyval.node=createSyntaxTreeNode(constType, yyvsp[0].value, 0,0,0);;
    break;}
case 59:
#line 178 "yacc.y"
{yyval.node=createSyntaxTreeNode(funCall, yyvsp[-3].ch, yyvsp[-1].node,0,0);;
    break;}
case 60:
#line 180 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
case 61:
#line 181 "yacc.y"
{yyval.node=0;;
    break;}
case 62:
#line 183 "yacc.y"
{yyval.node=addBrotherNode(yyvsp[-2].node, yyvsp[0].node);;
    break;}
case 63:
#line 184 "yacc.y"
{yyval.node=yyvsp[0].node;;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/local/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 187 "yacc.y"

/**
 * 打印语法错误
 * @method yyerror
 * @param  str 错误信息
 * @return 无返回值
 */
void yyerror(const char *str){
    fprintf(stderr,"%s, unexpected token -> %s at line %d, column %d.\n",
    str, yytext,yylineno, columnno);
}

/**
 * 此函数在每一个输入文件被解析完毕时被调用
 * @method yywrap
 * @return 如果返回值为0，允许打开其它的文件继续解析；如果返回值为1，则结束解析文件。
 */
int yywrap(){
    return 1;
}
/**
 * 程序入口函数
 * @method main
 * @param  int   argc   命令行运行此程序时输入的参数个数
 * @param  char* argv[]    输入的参数数组
 * 调用注意事项：参数个数为1时，默认标准输入输出；
 * 参数个数为2时，argv[1]为输入文件，输出为默认；
 * 参数个数为3时，argv[1]为输入文件，argv[2]为输出文件
 * @return 返回值为0，正常退出；返回值为1，无法打开待分析的文件。
 */
int main(int argc, char* argv[]) {

    if (argc > 1) {
        FILE *fin = fopen(argv[1], "r");
        if (!fin) {   
           perror(argv[1]);
           return 1;
        }
        FILE * fout = 0;
        if(argc > 2)
            fout = fopen(argv[2], "w");
        if(fout)
            yyout = fout;
        //从头开始分析fin文件
        yyrestart(fin);
        //开始分析
        yyparse();
        //打印语法树
        printTree(treeRoot);
        //关闭输入输出文件
        fclose(fin);
        if(fout)
            fclose(fout);
    }
    else{
		yyparse();
		printTree(treeRoot);
	}
    system("pause");
    return 0;
}
