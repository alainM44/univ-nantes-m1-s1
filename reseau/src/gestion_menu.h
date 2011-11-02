#ifndef H_GESTION_MENU
#define H_GESTION_MENU

/* #include <stdlib.h> */
/* #include <stdio.h> */
/* #include <stdbool.h> */
/* #include <string.h> */
/* #include <unistd.h> */
/* #include <sys/types.h> */
/* #include <sys/stat.h> */
/* #include <fcntl.h> */
#include "network.h"
#include "messages.h"


char* create_main_folder (const char name[],char final_name[]); //retourne le chemin pour la suppresion
void give_path(char strOut[]);
int menu(int sock,char folder_name []);
void clean_stdin(void);


#endif
