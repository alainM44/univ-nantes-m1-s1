/*exo1.l */
%{
#include "projet_compilation_syn.h"
extern int yylval;
%}

/*def*/

deb "\\"begin
tabular tabular
opt_tableau [lcrp]
fusion "\\"multicolumn
trait_hor "\\"hline
separ_col &
fin_ligne "\\""\\"
separ \|
fin "\\"end
nombre [0-9]*
word [a-zA-Z][a-zA-Z0-9_]*

accol_G \{
accol_D \}

space [ \t\n]*




/*rules analyseur lexico*/
%%

{deb}         {ECHO; printf("deb");return DEB;}
{tabular}     {ECHO;return TABLEAU;}
{opt_tableau} {ECHO;return OPTION_T;}
{fusion}      {ECHO;return FUSION;}
{trait_hor}   {ECHO;return TRAIT_HOR;}
{separ_col}   {ECHO;return SEPAR_COL;}
{fin_ligne}   {ECHO;return FIN_LIGNE;}
{separ}       {ECHO;return SEPAR;}
{fin}         {ECHO;return FIN;}
{accol_G}     {ECHO;return ACCOL_G;}
{accol_D}     {ECHO;return ACCOL_D;}
nombre+[\.]?nombre     {return NOMBRE;}
{word}        {ECHO;return MOT;}
{space}       {return SPACE;}
.             { ECHO;printf("\n"); return INUTILE;} 

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
