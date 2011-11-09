//projet_compilation.yacc
%{
#include <stdio.h> //FILE
#include <stdlib.h> //atoi
#include <string.h>
extern int yylex(void);
extern int yyleng;
void yyerror(char *s);
extern FILE* yyin;
extern FILE* yyout;
extern FILE* yyerr;
int nbcol = 0;
int nbseparateur = 0;
 void redigeOption( int border);
 char* redigeColonne(char* texte, int multicolumn, int colspan);
 char* redigeColonneNum(double val, int multicolumn, int colspan);
%}

//

%union{ char* str; double nb;}
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
%token GARBAGE
%token<nb> NOMBRE
%token<str> MOT 
%token<str> SPACE
%type<str> mots
%type<str> blancs
%type<str> colonne
%type<str> colonnes

%start fichier


%%

fichier   :  poubelle init tableau FIN blancs {fprintf(yyout,"</html>");}
;
poubelle  : GARBAGE poubelle
          |MOT poubelle
          |ACCOL_D poubelle
          |ACCOL_G poubelle
          |
;
init      :  DEB { fprintf(yyout, "<table ");} 
;
tableau   : options blancs lignes {fprintf(yyout,"</tbody>\n</table>\n");}
;
options   :  ACCOL_G option ACCOL_D {redigeOption(nbseparateur>=nbcol/2);}
;
option    : SEPAR option {nbseparateur++;}
          | MOT option {nbcol =+ strlen($1);}
          | SEPAR {nbseparateur++;}
          | MOT {nbcol =+ strlen($1);}
;

lignes    : ligne FIN_LIGNE blancs lignes{}
          |ligne FIN_LIGNE blancs {}
;


ligne     : TRAIT_HOR
| colonnes {fprintf(yyout,"<tr>%s</tr>\n",$1);free($1);}
;

colonnes  : colonne blancs SEPAR_COL blancs colonnes {$$= strcat($1, $5);}
| colonne blancs {$$ = $1;}
| colonne {$$ = $1;}
;



colonne   : MOT   {$$ = redigeColonne($1, 0,0 );}
          | NOMBRE {$$ = redigeColonneNum($1, 0, 0);}
| FUSION ACCOL_G NOMBRE ACCOL_D ACCOL_G option ACCOL_D ACCOL_G mots ACCOL_D {$$ = redigeColonne($9, 1, $3);}
| FUSION ACCOL_G NOMBRE ACCOL_D ACCOL_G option ACCOL_D ACCOL_G NOMBRE ACCOL_D {$$ = redigeColonneNum($9, 1, $3);}
;

mots      : MOT blancs mots {$1= strcat($1, $2);$$ =strcat( $1, $3);}
| MOT blancs  {$$ = $1;}
          | MOT     {$$ = $1;}
;

blancs    : SPACE blancs {$$ = strcat($1, $2);}
          | SPACE {$$ = $1;}
;

%%
void yyerror(char *s)
{
fprintf(stderr,"yyerror : %s\n",s);
return;
}

char tab[]= "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"   \"http://www.w3.org/TR/html4/strict.dtd\">\n<html>\n<head><head/>\n<body>";

void redigeOption( int border)
{
  fprintf(yyout, "style=text-align: left; width: 90%%; border=\"");
  if (border)
    fprintf(yyout,"1");
  else
    fprintf(yyout,"0");
  fprintf(yyout,"\"cellpadding=\"2\" cellspacing=\"2\">\n<tbody>\n<tr>");
}

char* redigeColonne(char* texte, int multicolumn, int colspan)
{
  char* retour = malloc(sizeof(char)*1000);
  if(multicolumn)
    {
      sprintf(retour,"<td style=\"text-align: center;\" colspan=\"%d\" rowspan = \"1\">%s</td>", colspan, texte);
    }
  else
    {
      sprintf(retour,"<td style=\"text-align: center;\">%s</td>", texte);
    }
  return retour;
}

char* redigeColonneNum(double val, int multicolumn, int colspan)
{
   char* retour = malloc(sizeof(char)*1000);
  if(multicolumn)
    {
      sprintf(retour,"<td style=\"text-align: center;\" colspan=\"%d\" rowspan = \"1\">%.2f</td>", colspan, val);
    }
  else
    {
      sprintf(retour,"<td style=\"text-align: center;\">%.2f</td>", val);
    }
  return retour;
}



int main(int argc, char* argv[])
{
  if (argc >1)
    {
      yyin=fopen(argv[1],"r");
      if (!yyin) 
	{
	  printf("error when open input file\n");
	  exit(1);
	}
      if (argc >2)
	{
	  yyout=fopen(argv[2], "w");
	}
      if(!yyout)
	{
	  printf("error when open output file\n");
	  exit(1);
	}
      fprintf(yyout, "%s", tab);
      if (!yyparse() ) 
	{
	  fclose(yyin);
	  fclose(yyout);
	}
      else
	{
	  printf("parse error\n" );
	  exit(1);
	}
    }
  else 
    {
      printf("call : ./exo3 texxte.txt...");
      exit(1);
    }
}
