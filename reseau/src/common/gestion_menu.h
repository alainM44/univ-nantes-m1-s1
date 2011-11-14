#ifndef H_GESTION_MENU
#define H_GESTION_MENU
#include "network.h"
#include "messages.h"


void create_main_folder (const char name[],const char * path,char final_name[]);
void give_path(char strOut[]);
int menu(int soc,char folder_name []);
void clean_stdin(void);


#endif
