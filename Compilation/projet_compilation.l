/*exo1.l */
%{
#include "projet_compilation_syn.h"
extern int yylval;
%}

/*def*/

deb "\\"begin
tabular tabular
accol_G \{
accol_D \}
opt_tableau l
fusion "\\"multicolumn
trait_hor "\\"hline
separ_col &
fin_ligne "\\""\\"
separ \|
fin "\\"end
nombre [0-9]*
word [a-zA-Z][a-zA-Z0-9_]*



space [ \t\n]*




/*rules analyseur lexico*/
%%

{deb}         {ECHO;printf("\n"); return DEB;}
{tabular}     {ECHO;printf("\n");return TABLEAU;}
l {ECHO;printf("\n");return OPTION_T;}
{fusion}      {ECHO;printf("\n");return FUSION;}
{trait_hor}   {ECHO;printf("\n");return TRAIT_HOR;}
{separ_col}   {ECHO;printf("\n");return SEPAR_COL;}
{fin_ligne}   {ECHO;printf("\n");return FIN_LIGNE;}
{separ}       {ECHO;printf("\n");return SEPAR;}
{fin}         {ECHO;printf("\n");return FIN;}
{accol_G}     {ECHO;printf("\n");return ACCOL_G;}
{accol_D}     {ECHO;printf("\n");return ACCOL_D;}
nombre+[\.]?nombre     {ECHO;printf("\n");return NOMBRE;}
{word}        {ECHO;printf("word\n");return MOT;}
{space}       {ECHO;printf("\n");return SPACE;}
.            {ECHO; yyerror ("unexpected character");}

%%



/*
lex projet_compilation.l
yacc -d projet_compilation.y
mv lex.yy.c projet_compilation_lex.c
mv y.tab.c projet_compilation_syn.c
mv y.tab.h projet_compilation_syn.h
cc -o proj projet_compilation_lex.c projet_compilation_syn.c -lfl
 */
/*
lettre[a-zA-Z]
/*aaa [a-zA-Z0-9_] */
/*
{a}{n}{d} {return AND}
{lettre}{aaa}* {yyval chaine = (char *)strdup(yylead);return IDENTIFIANT;}
 */
