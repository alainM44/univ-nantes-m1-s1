#include <stdlib.h>;
#include "new_file_manager.h";


tree racine;


void creerRacine(char * cheminRacine)
{
 racine := createTree(cheminRacine);
}
