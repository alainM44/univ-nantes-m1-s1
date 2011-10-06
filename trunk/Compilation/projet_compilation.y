//projet_compilation.yacc

%{
#include <stdio.h> //FILE
#include <stdlib.h> //atoi
extern int yylex(void);
void yyerror(char *s);
extern FILE* yyin;
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

fichier   :  DEB ACCOL_G TABLEAU ACCOL_D tableau  FIN ACCOL_G TABLEAU ACCOL_D inutile {printf("inutile DEB ACCOL_G TABLEAU ACCOL_D tableau  FIN ACCOL_G TABLEAU ACCOL_D inutile\n");}
;
tableau   :  ACCOL_G option ACCOL_D blancs suitetab{printf(" ACCOL_G option ACCOL_D blancs suitetab\n");}
;
option    : SEPAR option {printf("SEPAR option\n");}
          | OPTION_T option {printf("OPTION_T option\n");}
          | SEPAR {printf("SEPAR \n");}
          | OPTION_T{printf("OPTION_T\n");}
;
suitetab  : TRAIT_HOR blancs {printf("TRAIT_HOR blancs\n");}
          | ligne {printf("ligne\n");}
          | TRAIT_HOR blancs suitetab {printf("TRAIT_HOR blancs suitetab\n");}
          | ligne suitetab{printf("ligne suitetab\n");}
;
ligne     : suitecol FIN_LIGNE blancs{printf("suitecol FIN_LIGNE blancs\n");}
;
suitecol  : SEPAR_COL blancs  {printf("SEPAR_COL blancs\n");}
          | MOT blancs  {printf("lancs\n");}
          | SEPAR_COL blancs suitecol {printf("SEPAR_COL blancs suitecol\n");}
          | MOT blancs suitecol {printf("MOT blancs suitecol\n");}//ne pas oublier multicol
;


inutile   :INUTILE inutile  {printf("INUTILE inutile\n");}
| INUTILE       {printf("INUTILE\n");}
;
blancs    : SPACE blancs 
          | SPACE
;

%%
void yyerror(char *s)
{
fprintf(stderr,"yyerror : %s\n",s);
return;
}

int main(int argc, char* argv[])
{
  if (argc >1)
    {
      yyin=fopen(argv[1],"r");
      if (!yyin) 
	{
	  printf("error");
	  exit(1);
	}
      if (!yyparse() ) 
	{
	  fclose(yyin);
	}
      else
	{
	  printf("parse error");
	  exit(1);
	}
    }
  else 
    {
      printf("call : ./exo3 texxte.txt...");
      exit(1);
    }
}
