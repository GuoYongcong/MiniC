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
int columnno = 1;
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
{ELSE}             {columnno+=yyleng; return ELSE;}
{IF}               {columnno+=yyleng; return IF;}
{INT}              {columnno+=yyleng; yylval.ch = strdup(yytext);return INT;}
{RETURN}           {columnno+=yyleng; return RETURN;}
{VOID}             {columnno+=yyleng; yylval.ch = strdup(yytext);return VOID;}
{WHILE}            {columnno+=yyleng; return WHILE;}
{ADD}              {columnno+=yyleng; yylval.ch = strdup(yytext);return ADD;}
{SUB}              {columnno+=yyleng; yylval.ch = strdup(yytext);return SUB;}
{MUL}              {columnno+=yyleng; yylval.ch = strdup(yytext);return MUL;}
{DIV}              {columnno+=yyleng; yylval.ch = strdup(yytext);return DIV;}
{LESS}             {columnno+=yyleng; yylval.ch = strdup(yytext);return LESS;}
{LESS_OR_EQUAL}    {columnno+=yyleng; yylval.ch = strdup(yytext);return LESS_OR_EQUAL;}
{GREA}             {columnno+=yyleng; yylval.ch = strdup(yytext);return GREA;}
{GREA_OR_EQUAL}    {columnno+=yyleng; yylval.ch = strdup(yytext);return GREA_OR_EQUAL;}
{EQUAL}            {columnno+=yyleng; yylval.ch = strdup(yytext);return EQUAL;}
{NOT_EQUAL}        {columnno+=yyleng; yylval.ch = strdup(yytext);return NOT_EQUAL;}
{ASSI}             {columnno+=yyleng; return ASSI;}
{SEM}              {columnno+=yyleng; return SEM;}
{COM}              {columnno+=yyleng; return COM;}
{LP}               {columnno+=yyleng; return LP;}
{RP}               {columnno+=yyleng; return RP;}
{LS}               {columnno+=yyleng; return LS;}
{RS}               {columnno+=yyleng; return RS;}
{LC}               {columnno+=yyleng; return LC;}
{RC}               {columnno+=yyleng; return RC;}
{ID}               {columnno+=yyleng; yylval.ch = strdup(yytext);return ID;}
{NUM}              {columnno+=yyleng; yylval.value = atoi(yytext);return NUM;}
{NOTES}            {}

[ ]+                {columnno+=yyleng; }
\t                  {columnno+=4; }
\n                  {columnno=0;}
<<EOF>>            {yyterminate();}
.                  {columnno+=yyleng; printf("lexical error,%s at line %d, column %d.\n",yytext,yylineno, columnno);}
%%
