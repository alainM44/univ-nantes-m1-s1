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
  int  numberInLine = 1;
  float  sumLine = 0;
  int  colonneCourant = 0;
  int* numberInColonne;
  float* sumColonne;
  char * positionnement = "center";
  
  void ajouteColonne(char* chaine,char* position, float num);
  void redigeOption( int border, char* pos);
  char* redigeColonne(char* texte, char* pos, int multicolumn, int colspan);
  char* redigeColonneReel(double val, char* pos, int multicolumn, int colspan);
  char* redigeColonneEntier(int val, char* pos, int multicolumn, int colspan);
  void initialiseTabBool(int* tab, int size);
  void initialiseTabReel(float* tab, int size);
  void changeTab(int* tab, int deb, int end);
  void sommeColonne(char* chaine, char* position, int* appliqueSomme, float* toutesSommes, int nbFois);
  void afficheTabDebug(int* tab, int size);
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
%token ANTISLASH
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
;
  /*differents types de declarations de tableau*/
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

  /*lorsque toutes les lignes du tableau ont été lues,*/
  /*on alloue une chaine de caractères qui va contenir la ligne HTML des totaux des colonnes,*/
  /*et on lance la fonction sommeColonne qui va rediger cette ligne dans la chaine de caractères*/
  /*Une fois la chaine complétée, on la rédige dans le fichier*/
tableau   : options blancs lignes {char* ligneDesTotaux = malloc(sizeof(char)*1000);
sommeColonne(ligneDesTotaux,positionnement, numberInColonne, sumColonne, nbcol);
 fprintf(yyout,"%s</tbody>\n</table>\n",ligneDesTotaux);
 free(ligneDesTotaux);}
;

  /*Lorsque les options ont été lues,*/
  /*on alloue deux tableau de taille égale au nb de colonnes dans le tableau*/
  /*Le tableau numberInColonne contient des booléens qui indique pour chaque colonnes*:
  /*si elle ne contient que des valeurs numériques*/
  /*Le tableau sumColonne stocke la somme de chacune des colonnes*/
  /*Enfin on lance la fonction redigeOption qui prends une valeur booléenne qui indique si le tableau aura des bordures*/
options   :  ACCOL_G option ACCOL_D {numberInColonne = malloc(nbcol * sizeof(int));
   sumColonne = malloc(nbcol*sizeof(float));
   initialiseTabBool(numberInColonne, nbcol);
   initialiseTabReel(sumColonne, nbcol);
   redigeOption(nbseparateur>=nbcol/2, positionnement);}
;

/*option permet de connaitre le nombre de colonnes et de separateur*/
option    : SEPAR option {nbseparateur++;}
| MOT option {nbcol =+ strlen($1);}
| SEPAR {nbseparateur++;}
| MOT {nbcol =+ strlen($1);}
;

/*parcourt toutes les lignes*/
lignes    : ligne FIN_LIGNE  blancs lignes{}
| ligne FIN_LIGNE blancs {}
| TRAIT_HOR blancs lignes;
| TRAIT_HOR blancs
;

/*Lorsqu'une ligne est traité on recupère la valeur renvoyée par colonnes et on l'affiche entre deux balise */
/*Et l'on reinitialise les variables "numberInLine" qui dit si la ligne ne contient que des valeurs numeriques */
/*colonneCourante indique le numero de la colonne parcouru lors du parcours d'une ligne*/
/*sumLigne va conserver la sum de toutes les valeurs numériques de la ligne */
ligne     : colonnes {
  if (numberInLine)
    {
      ajouteColonne($1,positionnement, sumLine);
    }
  fprintf(yyout,"<tr>%s</tr>\n",$1);
  free($1);
  numberInLine = 1; 
  colonneCourant = 0;
  sumLine = 0;}
;

/*Défini l'apparence des colonnes*/
colonnes  :blancs colonne blancs SEPAR_COL  colonnes {$$= strcat($2, $5);}
| blancs colonne blancs {$$ = $2;}
;

/*colonne va lister tout ce que peut contenir une colonne (entier, reel, mot... */
/*colonne renvoie une chaine de caractères fourni par la fonction redigeColonne*/
colonne   : phrase   {$$ = redigeColonne($1, positionnement, 0,0 );
   numberInColonne[colonneCourant] = 0;
   numberInLine = 0;
   colonneCourant++;}
| ENTIER {$$ = redigeColonneEntier($1, positionnement, 0, 0);
   sumLine += $1;
   sumColonne[colonneCourant] += $1;
   colonneCourant++;}
| REEL {$$ = redigeColonneReel($1, positionnement, 0, 0);
   sumLine += $1;
   sumColonne[colonneCourant] += $1;   
   colonneCourant++;}
| FUSION ACCOL_G ENTIER ACCOL_D ACCOL_G option ACCOL_D ACCOL_G phrase ACCOL_D {$$ = redigeColonne($9, positionnement, 1, $3);
   changeTab(numberInColonne, colonneCourant, $3);
   colonneCourant += $3;
   numberInLine = 0;}
| FUSION ACCOL_G ENTIER ACCOL_D ACCOL_G option ACCOL_D ACCOL_G ENTIER ACCOL_D {$$ = redigeColonneEntier($9, positionnement, 1, $3);
   changeTab(numberInColonne, colonneCourant, $3);
   colonneCourant += $3;
   sumLine += $9;
 }
| FUSION ACCOL_G ENTIER ACCOL_D ACCOL_G option ACCOL_D ACCOL_G REEL ACCOL_D {$$ = redigeColonneReel($9, positionnement, 1, $3);
   changeTab(numberInColonne, colonneCourant, $3);
   colonneCourant += $3;
   sumLine += $9;
 }
;
/*phrase permet de gérer des suite de mots séparer par des blancs*/
phrase : phrase blancs  mots {$$= strcat(strcat($1, $2),$3);}
| mots        {$$ = $1;}
;

/*mots corresponds aux chaines des caractères composées de lettres ou de chiffres*/
/*et aux formules latex de la forme : {\d phrase} et \d{phrase} pour géré les symboles particuliers ou les mises en formes*/
/*On peut constater que la mise en forme est ignoré. Seule la phrase est recopiée*/
mots      : MOT     {$$ = $1;}
| ACCOL_G ANTISLASH MOT SPACE phrase  ACCOL_D {$$= $5;}
|ANTISLASH MOT ACCOL_G phrase ACCOL_D {$$ = $4;}
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

/*redige le champ d'option du tableau html*/
void redigeOption( int border, char * pos)
{
  fprintf(yyout, "style=text-align: %s; width: 90%%; border=\"", pos);
  if (border)
    fprintf(yyout,"1");
  else
    fprintf(yyout,"0");
  fprintf(yyout,"\"cellpadding=\"2\" cellspacing=\"2\">\n<tbody>\n<tr>");
}

/*renvoie une chaine de caractère contenant le code d'une colonne en html*/
/*texte est une string correspondant à la valeur à mettre dans la colonne*/
/*pos l'alignement dans la colonne*/
/*si multicolumn est à 1 alors colspan indique la taille de colspan*/
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

/*idem que redigecolumn mais pour les reels*/
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
/*idem que redigecolumn mais pour les entiers*/
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

void initialiseTabBool(int* tab, int size)
{
  int i;
  for(i = 0; i<size; i++)
    {
      tab[i] = 1;
    }
}

void initialiseTabReel(float* tab, int size)
{
  int i;
  for(i = 0; i<size; i++)
    {
      tab[i] = 0;
    }
}

void changeTab(int* tab, int deb, int quantity)
{
  int i;
  for(i = deb; i<deb+quantity; i++)
    {
      tab[i] = 0;
    }
}

void ajouteColonne(char* chaine, char* position, float num)
 {
   char* aCopier=malloc(100* sizeof(char));
   sprintf(aCopier,  "<td style=\"text-align: %s;\">%.2f</td>",position, num);
   strcat(chaine, aCopier);
   free(aCopier);
 }

void sommeColonne(char* chaine, char* position, int* appliqueSomme, float* toutesSommes, int nbFois)
  {
    int i, bool;
    bool=1;
    sprintf(chaine , "");
    char* aCopier;
    for(i=0;i<nbFois;i++)
      {
	bool *= appliqueSomme[i];	
      }
    if (bool)
      {
	strcat(chaine, "<tr>");
	for (i=0;i<nbFois;i++)
	  {
	    if (appliqueSomme[i])
	      {	
		aCopier=malloc(50* sizeof(char));
		sprintf(aCopier,"");
		ajouteColonne(aCopier, position, toutesSommes[i]);
		strcat(chaine, aCopier);
		free(aCopier);
	      }
	    else
	      strcat(chaine, "<td></td>");
	  }
	strcat(chaine, "</tr>\n");
      }
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
