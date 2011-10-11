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

%start fichier


%%

fichier   :  DEB ACCOL_G TABLEAU ACCOL_D tableau  FIN ACCOL_G TABLEAU ACCOL_D blancs {printf(" DEB ACCOL_G TABLEAU ACCOL_D tableau  FIN ACCOL_G TABLEAU ACCOL_D \n");}
;
tableau   :  ACCOL_G option ACCOL_D blancs lignes {printf(" ACCOL_G option ACCOL_D blancs suitetab\n");}
;
option    : SEPAR option {printf("SEPAR option\n");}
          | MOT option {printf("OPTION_T option\n");}
          | SEPAR {printf("SEPAR \n");}
          | MOT {printf("OPTION_T\n");}
;
lignes    : ligne FIN_LIGNE blancs lignes {printf("ligne FIN_LIGNE blancs lignes\n");}
          |ligne FIN_LIGNE blancs {printf("ligne FIN_LIGNE blancs\n");}
;
ligne     : TRAIT_HOR {printf("TRAIT_HOR blancs\n");}
          | colonnes {printf("colonnes\n");}
;
colonnes  : colonne blancs colonnes {printf("colonne blancs colonnes\n");}
          | colonne blancs{printf("colonne blancs\n");}
          |FUSION ACCOL_G NOMBRE ACCOL_D ACCOL_G option ACCOL_D MOT colonnes {printf("FUSION ACCOL_G NOMBRE ACCOL_D ACCOL_G option ACCOL_D MOT colonnes\n");}
          |FUSION ACCOL_G NOMBRE ACCOL_D ACCOL_G option ACCOL_D ACCOL_G mots ACCOL_D {printf("FUSION ACCOL_G NOMBRE ACCOL_D ACCOL_G option ACCOL_D MOT\n");}
;
colonne   : SEPAR_COL   {printf("SEPAR_COL \n");}
          | MOT   {printf("MOT \n");}
          | NOMBRE {printf("NOMBRE \n");}
;
mots      : MOT blancs mots
          | MOT blancs
          | MOT
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
	  printf("error\n");
	  exit(1);
	}
      if (!yyparse() ) 
	{
	  fclose(yyin);
	}
      else
	{
	  printf("parse error\n");
	  exit(1);
	}
    }
  else 
    {
      printf("call : ./exo3 texxte.txt...");
      exit(1);
    }
}
