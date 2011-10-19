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
 void redigeColonne(char* texte, int multicolumn, int colspan);
 void redigeColonneNum(double val, int multicolumn, int colspan);
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
%token<nb> NOMBRE
%token<str> MOT SPACE
%type<str> mots

%start fichier


%%

fichier   :  init tableau final {}
;
init      :  DEB ACCOL_G TABLEAU ACCOL_D { fprintf(yyout, "<table ");} 
;
final     :  FIN ACCOL_G TABLEAU ACCOL_D blancs
;
tableau   : options blancs lignes {fprintf(yyout,"</tbody>\n</table>");}
;
options   :  ACCOL_G option ACCOL_D {fprintf(yyout,"<tr>");}
;
option    : SEPAR option {nbseparateur++;}
          | MOT option {nbcol =+ yyleng;}
          | SEPAR {nbseparateur++; redigeOption(nbseparateur>=nbcol/2); }
          | MOT {nbcol =+ yyleng;printf("%d",nbcol); redigeOption(nbseparateur>=nbcol/2);}
;

lignes    : ligne FIN_LIGNE blancs lignes{fprintf(yyout,"</tr>\n<tr>");}
|{fprintf(yyout,"</tr>\n");}
;


ligne     : TRAIT_HOR
          | colonnes 
;

colonnes  : colonne blancs SEPAR_COL blancs colonnes {fprintf(yyout,"colonne");}
| colonne blancs
;



colonne   : MOT   {fprintf(yyout,"test");}
          | NOMBRE {fprintf(yyout,"test");}
          | FUSION ACCOL_G NOMBRE ACCOL_D ACCOL_G option ACCOL_D ACCOL_G mots ACCOL_D {fprintf(yyout,"test");}
          | FUSION ACCOL_G NOMBRE ACCOL_D ACCOL_G option ACCOL_D ACCOL_G NOMBRE ACCOL_D {fprintf(yyout,"test");}
;

mots      : MOT blancs mots {fprintf(yyout,"test");}
          | MOT blancs  {fprintf(yyout,"test");}
          | MOT     {fprintf(yyout,"test");}
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

char tab[]= "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"   \"http://www.w3.org/TR/html4/strict.dtd\">\n<html>\n<head><head/>\n<body>";

void redigeOption( int border)
{
  fprintf(yyout, "style=text-align: left; width: 90%%;\"border=\"");
  if (border)
    fprintf(yyout,"1");
  else
    fprintf(yyout,"0");
  fprintf(yyout,"\"cellpadding=\"2\" cellspacing=\"2\">\n<tbody>");
}

void redigeColonne(char* texte, int multicolumn, int colspan)
{
  if(multicolumn)
    fprintf(yyout,"<td style=\"text-align: center;\" colspan=\"%d\" rowspan = \"1\">%s</td>",colspan, texte);
  else
    fprintf(yyout,"<td style=\"text-align: center;\">%s</td>", texte);
}

void redigeColonneNum(double val, int multicolumn, int colspan)
{
  if(multicolumn)
    fprintf(yyout,"<td style=\"text-align: center;\" colspan=\"%d\" rowspan = \"1\">%lf</td>",colspan,  val);
  else
    fprintf(yyout,"<td style=\"text-align: center;\">%lf</td>", val);
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
	  yyout=fopen(argv[2], "a");
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
