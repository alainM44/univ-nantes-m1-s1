#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char* cheminRacine;
const char* courant;

void createRacine (char* cheminRacine)
{   
  char record[1000];
  sprintf(record,"mkdir %s", cheminRacine);
  system(record);
}

void ls ()
{  
  char record[5];
  sprintf(record,"ls");
  system(record);
}

void cd (char* chemin)
{  
  /* char buffer[100];
  char* pwd;
  FILE * resultat;
  sprintf(pwd, "pwd");*/
  char record[1000];
  sprintf(record,"cd %s", chemin);//-c modifier pour la racine later
  system(record);
}

void mkdir(char* nom_fichier)
{
  char record[1000];
  sprintf(record,"mkdir %s", nom_fichier);
  system(record);
}

void main(int argc, char * argv)
{
  cd("/comptes/E074862X/test");
}
