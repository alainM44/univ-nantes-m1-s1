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
 void redigeOption( int border, char* pos);
 char* redigeColonne(char* texte, char* pos, int multicolumn, int colspan);
 char* redigeColonneReel(double val, char* pos, int multicolumn, int colspan);
 char* redigeColonneEntier(int val, char* pos, int multicolumn, int colspan);
char * positionnement = "center";
%}

//

%union{ char* str; double reel; int entier;}
%token DEB
%token DOC
%token DC
%token GFX
%token TABLE
%token TABULAR
%token CAPTION
%token OPTION_T
%token FUSION
%token TRAIT_HOR
%token SEPAR_COL
%token FIN_LIGNE
%token SEPAR
%token FIN
%token ACCOL_G
%token ACCOL_D
%token DML
%token CROCH_G
%token CROCH_D
%token<entier> ENTIER
%token<reel> REEL
%token<str> MOT 
%token<str> SPACE
%type<str> mots
%type<str> blancs
%type<str> colonne
%type<str> colonnes
%type<str> phrase

%start fichier


%%

fichier   : debLatex blancs init tableau end blancs endLatex blancs{fprintf(yyout,"</html>");}
;

debLatex  : DC blancs GFX blancs DEB ACCOL_G DOC ACCOL_D blancs
;

endLatex  : FIN ACCOL_G DOC ACCOL_D

init      :  tabledeb  posdeb   DEB ACCOL_G TABULAR ACCOL_D { fprintf(yyout, "<table ");} 
| tabledeb  DEB ACCOL_G TABULAR ACCOL_D { fprintf(yyout, "<table ");} 
| DEB ACCOL_G TABULAR ACCOL_D { fprintf(yyout, "<table ");} 
;

end       : FIN ACCOL_G TABULAR ACCOL_D blancs posend blancs caption tableend
;

tabledeb  : DEB ACCOL_G TABLE ACCOL_D CROCH_G MOT CROCH_D blancs
;

tableend  : FIN ACCOL_G TABLE ACCOL_D
          |
;

posdeb       :  DEB ACCOL_G MOT ACCOL_D blancs{positionnement = $3;}
;

posend    : FIN ACCOL_G MOT ACCOL_D
;

caption : CAPTION ACCOL_G phrase ACCOL_D blancs {fprintf(yyout,"%s",$3);}
        |
;

tableau   : options blancs lignes {fprintf(yyout,"</tbody>\n</table>\n");}
;

options   :  ACCOL_G option ACCOL_D {redigeOption(nbseparateur>=nbcol/2, positionnement);}
;

option    : SEPAR option {nbseparateur++;}
          | MOT option {nbcol =+ strlen($1);}
          | SEPAR {nbseparateur++;}
          | MOT {nbcol =+ strlen($1);}
;

lignes    : ligne FIN_LIGNE  blancs lignes{}
          | ligne FIN_LIGNE blancs {}
          | TRAIT_HOR blancs lignes;
          | TRAIT_HOR blancs
;


ligne     : colonnes {fprintf(yyout,"<tr>%s</tr>\n",$1);free($1);}
;

colonnes  :blancs colonne blancs SEPAR_COL  colonnes {$$= strcat($2, $5);}
| blancs colonne blancs {$$ = $2;}
;

colonne   : phrase   {$$ = redigeColonne($1, positionnement, 0,0 );}
          | ENTIER {$$ = redigeColonneEntier($1, positionnement, 0, 0);}
          | REEL {$$ = redigeColonneReel($1, positionnement, 0, 0);}
| FUSION ACCOL_G ENTIER ACCOL_D ACCOL_G option ACCOL_D ACCOL_G phrase ACCOL_D {$$ = redigeColonne($9, positionnement, 1, $3);}
| FUSION ACCOL_G ENTIER ACCOL_D ACCOL_G option ACCOL_D ACCOL_G ENTIER ACCOL_D {$$ = redigeColonneEntier($9, positionnement, 1, $3);}
| FUSION ACCOL_G ENTIER ACCOL_D ACCOL_G option ACCOL_D ACCOL_G REEL ACCOL_D {$$ = redigeColonneReel($9, positionnement, 1, $3);}
;
phrase : phrase blancs  mots {$$= strcat(strcat($1, $2),$3);}
       | mots        {$$ = $1;}
;
mots      : MOT     {$$ = $1;}
          | ACCOL_G DML MOT SPACE phrase  ACCOL_D {$$= $5;}
|DML MOT ACCOL_G phrase ACCOL_D {$$ = $4;}
;

blancs    : SPACE blancs {$$ = strcat($1, $2);}
| {$$ ="";}
;

%%
void yyerror(char *s)
{
fprintf(stderr,"yyerror : %s\n",s);
return;
}

char tab[]= "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"   \"http://www.w3.org/TR/html4/strict.dtd\">\n<html>\n<head><head/>\n<body>";

void redigeOption( int border, char * pos)
{
  fprintf(yyout, "style=text-align: %s; width: 90%%; border=\"", pos);
  if (border)
    fprintf(yyout,"1");
  else
    fprintf(yyout,"0");
  fprintf(yyout,"\"cellpadding=\"2\" cellspacing=\"2\">\n<tbody>\n<tr>");
}

char* redigeColonne(char* texte, char* pos, int multicolumn, int colspan)
{
  char* retour = malloc(sizeof(char)*1000);
  if(multicolumn)
    {
      sprintf(retour,"<td style=\"text-align: %s;\" colspan=\"%d\" rowspan = \"1\">%s</td>", pos, colspan, texte);
    }
  else
    {
      sprintf(retour,"<td style=\"text-align: %s ;\">%s</td>", pos, texte);
    }
  return retour;
}

char* redigeColonneReel(double val, char* pos, int multicolumn, int colspan)
{
   char* retour = malloc(sizeof(char)*1000);
  if(multicolumn)
    {
      sprintf(retour,"<td style=\"text-align: %s;\" colspan=\"%d\" rowspan = \"1\">%.2f</td>", pos, colspan, val);
    }
  else
    {
      sprintf(retour,"<td style=\"text-align: %s;\">%.2f</td>", pos, val);
    }
  return retour;
}

char* redigeColonneEntier(int val, char* pos, int multicolumn, int colspan)
{
   char* retour = malloc(sizeof(char)*1000);
  if(multicolumn)
    {
      sprintf(retour,"<td style=\"text-align: %s;\" colspan=\"%d\" rowspan = \"1\">%d</td>", pos, colspan, val);
    }
  else
    {
      sprintf(retour,"<td style=\"text-align: %s;\">%d</td>", pos, val);
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
