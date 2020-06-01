/*
* @Copyright (c), 2020-2020, GuoYongcong.
* @File name: lex.l
* @Description: 该文件定义了 Mini C 的保留字、专用符号和其他标记，
*               该文件经过Flex编译之后生成lex.yy.c文件。
* @Author: 郭永聪
* @Version: 1.0
* @Date:   2020-05-01
* @History:
*   <author>    <version>   <date>    <description>
*/


%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yacc.tab.h"
%}
%option yylineno 
/**
 * 保留字
 */
ELSE             else
IF               if
INT              int
RETURN           return
VOID             void
WHILE            while

/**
 * 专用符号
 */
ADD              \+
SUB              \-
MUL              \*
DIV              \/
LESS             \<
LESS_OR_EQUAL    \<\=
GREA             \>
GREA_OR_EQUAL    \>\=
EQUAL            \=\=
NOT_EQUAL        \!\=
ASSI             \=
SEM              \;
COM              \,
LP               \(
RP               \)
LS               \[
RS               \]
LC               \{
RC               \}
LN               [/][*]
RN               [*][/]

/**
 * 其他标记
 */
letter           [a-zA-Z]
digit            [0-9]
ID               {letter}+
NUM              {digit}+

/**
 * 注释
 */
NOTES            {LN}([^*]|[*]+[^*/])*[*]*{RN}  

%%
{ELSE}             {return ELSE;}
{IF}               {return IF;}
{INT}              {yylval.ch = strdup(yytext);return INT;}
{RETURN}           {return RETURN;}
{VOID}             {yylval.ch = strdup(yytext);return VOID;}
{WHILE}            {return WHILE;}
{ADD}              {yylval.ch = strdup(yytext);return ADD;}
{SUB}              {yylval.ch = strdup(yytext);return SUB;}
{MUL}              {yylval.ch = strdup(yytext);return MUL;}
{DIV}              {yylval.ch = strdup(yytext);return DIV;}
{LESS}             {yylval.ch = strdup(yytext);return LESS;}
{LESS_OR_EQUAL}    {yylval.ch = strdup(yytext);return LESS_OR_EQUAL;}
{GREA}             {yylval.ch = strdup(yytext);return GREA;}
{GREA_OR_EQUAL}    {yylval.ch = strdup(yytext);return GREA_OR_EQUAL;}
{EQUAL}            {yylval.ch = strdup(yytext);return EQUAL;}
{NOT_EQUAL}        {yylval.ch = strdup(yytext);return NOT_EQUAL;}
{ASSI}             {return ASSI;}
{SEM}              {return SEM;}
{COM}              {return COM;}
{LP}               {return LP;}
{RP}               {return RP;}
{LS}               {return LS;}
{RS}               {return RS;}
{LC}               {return LC;}
{RC}               {return RC;}
{ID}               {yylval.ch = strdup(yytext);return ID;}
{NUM}              {yylval.value = atoi(yytext);return NUM;}
{NOTES}            {}

[ \t\n]+             {}
<<EOF>>            {yyterminate();}
.                  {printf("lexical error,%s at line %d.\n",yytext,yylineno);}
%%
