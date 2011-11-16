#!/bin/sh

rm *.c *.h
rm proj
echo "compile lex"
lex projet_compilation.l
echo "compile yacc"
yacc --report=states -d projet_compilation.y
mv lex.yy.c projet_compilation_lex.c
mv y.tab.c projet_compilation_syn.c
mv y.tab.h projet_compilation_syn.h
echo "compile yacc"
cc -o proj projet_compilation_lex.c projet_compilation_syn.c -lfl
