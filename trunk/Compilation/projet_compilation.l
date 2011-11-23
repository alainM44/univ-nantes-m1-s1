/*exo1.l */
%{
#include "projet_compilation_syn.h"
%}

/*def*/
deb "\\"begin
tabular tabular
table table
document document
documentclass "\\"documentclass\{article\}
graphicx "\\"usepackage\{graphicx\}
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
antislash "\\"
croch_G "["
croch_D "]" 
garbage [a-zA-Z0-9"&""\\""'""."]*

accol_G \{
accol_D \}

space [ \t\n]*





/*rules analyseur lexico*/
%%
{deb}           {return DEB;}
{document}      {return DOC;}
{documentclass} {return DC;}   /* permet de recuperer \documentclass{article} en debut de fichier*/
{graphicx}      {return GFX;}  /* permet de recuperer \usepackage{graphix} en debut de fichier*/
{table}         {return TABLE;}
{tabular}       {return TABULAR;}
{caption}       {return CAPTION;}
{fusion}        {return FUSION;}
{trait_hor}     {return TRAIT_HOR;}
{separ_col}     {return SEPAR_COL;}
{fin_ligne}     {return FIN_LIGNE;}
{separ}         {return SEPAR;}
{fin}           {return FIN;}
{accol_G}       {return ACCOL_G;}
{accol_D}       {return ACCOL_D;}
{entier}        {yylval.entier=atoi(yytext);return ENTIER; }
{reel}          {yylval.reel=atof(yytext);return REEL; }
{word}          {yylval.str=strdup(yytext);return MOT;}
{space}         {yylval.str=strdup(yytext);return SPACE;}
{antislash}     {return ANTISLASH;}
{croch_G}       {return CROCH_G;}
{croch_D}       {return CROCH_D;}

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
