/*
* &@Copyright (c), 2020-2020, GuoYongcong.
* &@File name: yacc.y
* &@Description: 该文件定义了 Mini C BNF 语法，以及程序入口函数，
*               该文件经过Bison编译之后生成yacc.tab.c/.h文件。
* &@Author: 郭永聪
* &@Version: 1.0
* &@Date:   2020-05-01
* &@History:
*   <author>    <version>   <date>    <description>
*/

%{
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "utils.h"
#include "analyze.h"
#include "cgen.h"

//打印语法错误
void yyerror(const char *str);
//行号
extern int yylineno;
//列号
extern int columnno;
//token
extern char *yytext;
extern int yyleng;
//语法树根结点
STNode  treeRoot = 0;
bool TraceCode = true;
FILE * code;
bool TraceAnalyze = true;
bool Error = false;
%}
%union{
    int value; //NUM的值
    char* ch; //id、操作符、关键字的字符串
    STNode node; //语法树结点
}
/**
 *说明语法分析使用到的保留字、专用符号和其他标记
 */
%token ELSE IF RETURN WHILE
%token <ch> INT VOID ADD SUB MUL DIV
%token <ch>LESS LESS_OR_EQUAL GREA GREA_OR_EQUAL EQUAL NOT_EQUAL
%token ASSI SEM COM LP RP LS RS LC RC
%token <ch> ID
%token <value> NUM

/**
 * 解决悬挂else二义性
 */
%nonassoc LOWER_ELSE
%nonassoc ELSE
/**
 * 指定运算符优先级
 */
%left ADD SUB
%left MUL DIV
%nonassoc LESS LESS_OR_EQUAL GREA GREA_OR_EQUAL EQUAL NOT_EQUAL
%nonassoc ASSI

/**
 * 指定非终结符号的数据为union中的成员
 */
%type <node> program declaration_list declaration var_declaration tpye_specifier
%type <node> fun_declaration params param_list param compound_stmt local_declaration
%type <node> statement_list statement expression_stmt selection_stmt iteration_stmt
%type <node> return_stmt expression var simple_expression relop additive_expression
%type <node> addop term mulop mulop factor call args arg_list

%%
/**
 * 定义 Mini C BNF 语法，以及构建语法树
 */
program : declaration_list {
    treeRoot=createSyntaxTreeNode(program, 0,$1,0,0);
    setLocation(&treeRoot->location, &@1);}
        ;
declaration_list : declaration_list declaration {$$=addBrotherNode($1, $2);}
                 | expression {$$=$1;}
                 | declaration {$$=$1;}
                 ;
declaration : var_declaration {$$=$1; setLocation(&$$->location, &@1);}
            | fun_declaration {$$=$1;}
            ;
var_declaration : tpye_specifier ID SEM {
                    STNode  n1=createSyntaxTreeNode(idType, $2, 0,0,0);
                    setLocation(&n1->location, &@2);
                    $$=createSyntaxTreeNode(varDeclaration, 0, $1, n1,0);
}
                | tpye_specifier ID LS NUM RS SEM {
                    STNode  n1=createSyntaxTreeNode(constType, $4, 0,0,0);
                    STNode  n2=createSyntaxTreeNode(idType, $2, n1,0,0);
                    setLocation(&n2->location, &@2);
                    $$=createSyntaxTreeNode(varDeclaration, 0, $1, n2, 0);
}
                ;
tpye_specifier : INT {$$=createSyntaxTreeNode(typeType, $1, 0,0,0); }
               | VOID {$$=createSyntaxTreeNode(typeType, $1, 0,0,0);}
               ;
fun_declaration : tpye_specifier ID LP params RP compound_stmt {
    $$=createSyntaxTreeNode(funDeclaration, $2, $1, $4, $6);
    setLocation(&$$->location, &@2);
    setLocation(&$6->location, &@6);
}
                ;
params : param_list {$$=$1;}
       | VOID {$$=0;}
       ;
param_list : param_list COM param {$$=addBrotherNode($1, $3); setLocation(&$3->location, &@3);}
           | param {$$=$1; setLocation(&$$->location, &@1);}
           ;
param : tpye_specifier ID {
    STNode  n1=createSyntaxTreeNode(idType, $2, 0,0,0);
    setLocation(&n1->location, &@2);
    $$=createSyntaxTreeNode(varDeclaration, 0, $1, n1,0);
}
      | tpye_specifier ID LS RS {
    STNode  n1=createSyntaxTreeNode(defaultType, 0, 0,0,0);
    STNode  n2=createSyntaxTreeNode(idType, $2, n1,0,0);
    setLocation(&n2->location, &@2);
    $$=createSyntaxTreeNode(varDeclaration, 0, $1, n2, 0);

}
      ;
compound_stmt : LC local_declaration statement_list RC {
    $$=createSyntaxTreeNode(compoundStmt, 0,$2, $3,0);
}
              ;
local_declaration : local_declaration var_declaration {
	$$=addBrotherNode($1, $2);
	setLocation(&$2->location, &@2);
}
                  | {$$=0;}
                  ;
statement_list : statement_list statement {$$=addBrotherNode($1, $2); }
               | {$$=0;}
               ;
statement : expression_stmt {$$=$1;}
          | compound_stmt {
              $$=$1;
              setLocation(&$$->location, &@1);
}
          | selection_stmt {$$=$1;}
          | iteration_stmt {$$=$1;}
          | return_stmt {$$=$1;}
          ;
expression_stmt : expression SEM {$$=$1;}
                | SEM {$$=0;}
                ;
selection_stmt : IF LP expression RP statement ELSE statement {
    $$=createSyntaxTreeNode(ifStmt, 0,$3, $5, $7);
    setLocation(&$3->location, &@3);
}
               | IF LP expression RP statement %prec LOWER_ELSE {
    $$=createSyntaxTreeNode(ifStmt, 0, $3, $5,0);
    setLocation(&$3->location, &@3);
}
               ;
iteration_stmt : WHILE LP expression RP statement {
    $$=createSyntaxTreeNode(whileStmt, 0, $3, $5,0);
    setLocation(&$3->location, &@3);
}
               ;
return_stmt : RETURN expression SEM {
    $$=createSyntaxTreeNode(returnStmt, 0 ,$2,0,0);
    setLocation(&$2->location, &@2);
}
            | RETURN SEM {$$=createSyntaxTreeNode(returnStmt, 0, 0,0,0);}
            ;

expression : var ASSI expression {
    $$=createSyntaxTreeNode(assignStmt, 0, $1, $3,0);
    setLocation(&$3->location, &@3);}
           | simple_expression {$$=$1;}
           ;
var : ID {
    $$=createSyntaxTreeNode(varType, $1, 0,0,0);
    setLocation(&$$->location, &@1);
}
    | ID LS expression RS {
        $$=createSyntaxTreeNode(varType, $1,$3,0,0);
        setLocation(&$$->location, &@1);
    }
    ;
simple_expression : additive_expression {$$=$1;}
                  | additive_expression relop additive_expression {
    STNode  n = createSyntaxTreeNode(defaultType,0, $1, $3, 0);
    $$=addBrotherNode($2, n);
	setLocation(&$1->location, &@1);
	setLocation(&$3->location, &@3);
}
                  ;
relop : LESS_OR_EQUAL { $$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = LESS_OR_EQUAL;}
      | LESS { $$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = LESS;}
      | GREA_OR_EQUAL { $$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = GREA_OR_EQUAL;}
      | GREA { $$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = GREA;}
      | EQUAL { $$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = EQUAL;}
      | NOT_EQUAL { $$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = NOT_EQUAL;}
      ;
additive_expression : additive_expression addop term{
    STNode  n = createSyntaxTreeNode(defaultType,0, $1, $3, 0);
    $$=addBrotherNode($2, n);
	setLocation(&$1->location, &@1);
	setLocation(&$3->location, &@3);
}
                    | term {$$=$1;}
                    ;
addop : ADD {$$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = ADD;}
      | SUB {$$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = SUB;}
      ;
term : term mulop factor {
    STNode  n = createSyntaxTreeNode(defaultType,0, $1, $3, 0);
    $$=addBrotherNode($2, n);
	setLocation(&$1->location, &@1);
	setLocation(&$3->location, &@3);
}
     | factor {$$=$1;}
     ;
mulop : MUL {$$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = MUL;}
      | DIV {$$=createSyntaxTreeNode(opType, $1, 0,0,0); $$->dataType = DIV;}
      ;
factor : LP expression RP {$$=$2; setLocation(&$$->location, &@2);}
       | var {$$=$1; setLocation(&$$->location, &@1);}
       | call {$$=$1; setLocation(&$$->location, &@1);}
       | NUM {$$=createSyntaxTreeNode(constType, $1, 0,0,0); setLocation(&$$->location, &@1);}
       ;
call : ID LP args RP {
    $$=createSyntaxTreeNode(funCall, $1, $3,0,0);
    setLocation(&$$->location, &@1);
}
     ;
args : arg_list {$$=$1;}
     |  {$$=0;}
     ;
arg_list : arg_list COM expression {$$=addBrotherNode($1, $3);}
         | expression {$$=$1;}
         ;

%%
/**
 * 打印语法错误
 * @method yyerror
 * @param  str 错误信息
 * @return 无返回值
 */
void yyerror(const char *str){
    fprintf(stderr,"%s, unexpected token -> \'%s\' at line %d, column %d.\n",
    str, yytext,yylineno, columnno-yyleng);
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
 * &@return 返回值为0，正常退出；返回值为1，无法打开待分析的文件。
 */
int main(int argc, char* argv[]) {

	FILE *fin = 0, *fout = 0;
	code = stdout;
    if (argc > 1) {
        fin = fopen(argv[1], "r");
        if (!fin) {
           perror(argv[1]);
           return 1;
        }
        if(argc > 2){
            fout = fopen(argv[2], "w");
			if(fout){
				yyout = fout;
				code = fout;
			}
			if(argc>3){
				code = fopen(argv[3], "w");
				if(!code)
					code = stdout;
			}
		}
    }
    else{
		//printf("input and output filename:");
		char s1[100], s2[100], s3[100];
		//scanf("%s %s %s", s1, s2, s3);
		strcpy(s1,"input.txt");
		strcpy(s2,"output.txt");
		strcpy(s3,"codefile.tm");
		printf("%s,%s\n",s1,s2,s3);
		fin = fopen(s1, "r");
		if (!fin) {
			perror(s1);
			return 1;
		}
		fout = fopen(s2, "w");
		if(fout){
            yyout = fout;
		}
		code = fopen(s3, "w");
		if(!code)
			code = stdout;
	}
	//从头开始分析fin文件
	yyrestart(fin);
	//开始分析
	yyparse();
	//打印语法树
	printTree(treeRoot);
	//构建、打印符号表
	buildSymtab(treeRoot);
	if(!Error)
		//类型检查
		typeCheck(treeRoot);
	if(!Error)
		//打印中间代码
		codeGen(treeRoot,"codeFile");
	//关闭输入输出文件
	fclose(fin);
	if (fout)
		fclose(fout);
	if(code)
		fclose(code);
    system("pause");
    return 0;
}
