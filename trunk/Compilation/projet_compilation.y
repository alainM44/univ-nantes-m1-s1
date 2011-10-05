//projet_compilation.yacc

%{
#include <stdio.h> //FILE
#include <stdlib.h> //atoi
extern int yylex();
%}

//

%token DEB
%token TABLEAU
%token OPTION_T
%token FUSION
%token TRAIT_HOR
%token SEPAR_COL
%token FIN_LIGNE
%token SEPAR
%token FIN
%token ACCOL_G
%token ACCOL_D
%token NOMBRE
%token MOT SPACE
%token INUTILE

%start fichier

%%

fichier   : inutile DEB ACCOL_G TABLEAU ACCOL_D tableau  FIN ACCOL_G TABLEAU ACCOL_D inutile
tableau   :  ACCOL_G option ACCOL_D blancs suitetab
option    : SEPAR option | OPTION_T option | SEPAR | OPTION_T
suitetab  : TRAIT_HOR blancs | ligne | TRAIT_HOR blancs suitetab | ligne suitetab
ligne     : suitecol FIN_LIGNE blancs
suitecol  : SEPAR_COL blancs | MOT blancs | SEPAR_COL blancs suitecol | MOT blancs suitecol //ne pas oublier multicol


inutile   : INUTILE inutile | INUTILE
blancs    : SPACE blancs | SPACE

%%
	    /*
void yyerror(char *s)
{
    fprintf(stderr,"%s\n",s);
}
	    */
int main(void)
{
    /*yydebug=1;*/
    yyparse();
    return 0;
}
