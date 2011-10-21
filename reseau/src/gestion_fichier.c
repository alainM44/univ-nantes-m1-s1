#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char* cheminRacine;
const char* courant;

void createRacine (char* cheminRacine)
{   
  char record[1000];
  sprintf(record,"mkdir %s", cheminRacine);
  system(record);
}

void ls ()
{    
  char record[1000];
  sprintf(record,"ls %s", cheminRacine);
  system(record);
}

void cd ( char* chemin)
{  
  /* char buffer[100];
  char* pwd;
  FILE * resultat;
  sprintf(pwd, "pwd");*/
  // char record[1000];
  strcpy(cheminRacine, chemin);
  // sprintf(record,"cd %s", chemin);//-c modifier pour la racine later
  // system(record);
}

void mkdir(char* nom_fichier)
{
  char record[1000];
  sprintf(record,"mkdir %s/%s",cheminRacine, nom_fichier);
  system(record);
}

void main(int argc, char * argv)
{
  cheminRacine = (char *) malloc(sizeof(char)*256);
  char * chem ="/comptes/E074862X/Hello";
  cd(chem);
  mkdir("maison");
  ls();
}
