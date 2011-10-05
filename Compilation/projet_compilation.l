/*exo1.l */
%{
#include "projet_compilation_syn.h"
  extern int yylval();
%}

/*def*/

deb  \\begin
tabular tabular
opt_tableau [lcrp]
fusion \\multicolumn
trait_hor \\hline
separ_col &
fin_ligne \\\\
separ \|
fin \\end
nombre [0-9]*
word [a-zA-Z][a-zA-Z0-9_]*

accol_G \{
accol_D \}

space [ \t\n]*




/*rules analyseur lexico*/
%%
{deb}         {return DEB;}
{tabular}     {return TABLEAU;}
{opt_tableau} {return OPTION_T;}
{fusion}      {return FUSION;}
{trait_hor}   {return TRAIT_HOR;}
{separ_col}   {return SEPAR_COL;}
{fin_ligne}   {return FIN_LIGNE;}
{separ}       {return SEPAR;}
{fin}         {return FIN;}
{accol_G}     {return ACCOL_G;}
{accol_D}     {return ACCOL_D;}
[0-9]+[\.]?[0-9]*      {return NOMBRE;}
{word}        {return MOT;}
{space}       {return SPACE;}
.             {return INUTILE;}

%%
	/*subroutine*/
main(int argc, char** argv)
{
  if( argc>1)
    {
      FILE* ptr_file;
      if((ptr_file = fopen(argv[1], "r")) == NULL)
	{printf("blah"); exit(1);}
      yyin = ptr_file;
      yylex();
    }
/*
lettre[a-zA-Z]
/*aaa [a-zA-Z0-9_] */
/*
{a}{n}{d} {return AND}
{lettre}{aaa}* {yyval chaine = (char *)strdup(yylead);return IDENTIFIANT;}
 */
}


/*
lex projet_compilation.l
yacc -d projet_compilation.y
mv lex.yy.c projet_compilation_lex.c
mv y.tab.c projet_compilation_syn.c
mv y.tab.h projet_compilation_syn.h
cc -o proj projet_compilation_lex.c projet_compilation_syn.c -lfl
 */
