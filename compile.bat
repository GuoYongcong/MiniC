bison -d -t --verbose yacc.y
flex lex.l
gcc utils.c yacc.tab.c lex.yy.c -finput-charset=UTF-8 -fexec-charset=GBK -w 
