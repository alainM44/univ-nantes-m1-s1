/*exo1.l */
%{
#include "projet_compilation_syn.h"
%}

/*def*/
deb "\\"begin
tabular tabular
table table
caption "\\"caption
fusion "\\"multicolumn
trait_hor "\\"hline
separ_col "&"
fin_ligne "\\""\\"
separ \|
fin "\\"end
entier [0-9]+
reel {entier}"."[0-9]+
word [a-zA-Z][a-zA-Z0-9"%"]*
DML "\\"
croch_G "["
croch_D "]" 
garbage [a-zA-Z0-9"&""\\""'""."]*

accol_G \{
accol_D \}

space [ \t\n]*





/*rules analyseur lexico*/
%%
{deb}         {printf("DEB ");return DEB;}
{table}       {printf("TABLE ");return TABLE;}
{tabular}     {printf("TABULAR ");return TABULAR;}
{caption}     {printf("CAPTION ");return CAPTION;}
{fusion}      {printf("FUSION ");return FUSION;}
{trait_hor}   {printf("TRAIT_HOR ");return TRAIT_HOR;}
{separ_col}   {printf("SEPAR_COL ");return SEPAR_COL;}
{fin_ligne}   {printf("FIN_LIGNE ");return FIN_LIGNE;}
{separ}       {printf("SEPAR ");return SEPAR;}
{fin}         {printf("FIN ");return FIN;}
{accol_G}     {printf("ACCOL_G ");return ACCOL_G;}
{accol_D}     {printf("ACCOL_D ");return ACCOL_D;}
{entier}      {printf("ENTIER ");yylval.entier=atoi(yytext);return ENTIER; }
{reel}        {printf("REEL ");yylval.reel=atof(yytext);return REEL; }
{word}        {printf("MOT ");yylval.str=strdup(yytext);return MOT;}
{space}       {printf("SPACE ");yylval.str=strdup(yytext);return SPACE;}
{DML}         {printf("DML ");return DML;}
{croch_G}     {printf("CROCH_G ");return CROCH_G;}
{croch_D}     {printf("CROCH_D ");return CROCH_D;}

.             {printf("/n%serreur/n", yytext);}

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
