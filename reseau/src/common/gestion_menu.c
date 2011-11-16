#include "gestion_menu.h"
#include "network.h"

int menu(int sock,char folder_name []){
  bool fin;
  fin=false;
  char *record;
  char param[100];
  char out_name[100];
  char cmd[100];
  int comande;
  MESSAGE message;
  MESSAGE serveurmessage;
  char *path ;
  path = malloc(100);
  give_path(path);
  create_main_folder("CLIENT",path,folder_name);
  path[strlen(path)]='/';
  strcat(path,folder_name);
  path[strlen(path)+1]='/';
  record=malloc(1000);
  sprintf(record,"%s","clear");
  system(record);
  fprintf(stderr,"PRESS ENTER TO BEGIN\n");
  while(!fin){
    clean_stdin();
    fprintf(stderr,"\n**************************************\n***********MENU CLIENT FTP************\n**************************************\nN°   COMMAND \n1 -> Listing folder \n2 -> Dowload file  \n3 -> Upload file \n4 -> Enter a commande \n5 -> Quit \n6 -> Eteindre le server\n\nYour current folder : #%s#\nEnter a command number  : ",path);
    // getline(char **lineptr, size_t *n, FILE *stream);
    scanf("%d",&comande);
    fprintf(stderr,"Commande choisie : %d",comande);
     system(record);
    clean_stdin();
    switch(comande) {

    case 1 :
      //prepare command to send
      message.type=COMMANDE;
      send_commande(sock,message) ;
      //serveurmessage.tab=malloc(500);
      if ( read(sock,(char *)&serveurmessage,sizeof(serveurmessage)) <0)
	perror("read de receive \n");
        fprintf(stderr,"reponse serveur reçu \n");
      printf("Server's contain \n ****%s**** \n",serveurmessage.tab);
      //      free(serveurmessage);
      break;
    case 2 :
      fprintf(stderr," File name to download : ");
      gets(param);
      //prepare command to send
      message.type=1;
      strncpy(message.tab,param,strlen(param));
      message.tab[strlen(param)]='\0';
      send_commande(sock,message) ;
      //init de out_name
      strcpy(out_name,path);
      out_name[strlen(path)]='/';
      out_name[strlen(path)+1]='\0';
      strcat(out_name,param);
      out_name[strlen(out_name)]='\0';
      //on envoie
      receve_and_merge(sock,out_name);
      break;
    case 3 :
      fprintf(stderr," File name to upload : ");
      gets(param);
      //prepare command to send
      message.type=2;
      strncpy(message.tab,"out",3);
      strncat(message.tab,param,strlen(param));
      fprintf(stderr,"messtab#%s#\n",message.tab);
      send_commande(sock,message) ;
      frag_and_send(sock,param);
      break;
    case 4 : 
      fprintf(stderr,"Enter the command: ");
      gets(param);
      strcpy(cmd,param);
      strcat(cmd," ");
      strcat(cmd,path);
      cmd[strlen(cmd)]='\0';
      fprintf(stderr,"#%s\n#",cmd);
      system(cmd);
      break;
    case 5 :
      message.type=QUIT;
      send_commande(sock,message) ;
      fin=true;
      break;
    case 6:
      message.type=SHUTDOWN;
      send_commande(sock,message) ;
      fin=true;
      break;
    default : 
      fprintf(stderr,"Invalid command");
    }	   
  }
  free(record);

  return 0;
}


void give_path(char strOut[]){
  FILE* fichier;
  char std[100];
  if ((freopen("std.txt", "w", stdout)) != NULL) // attention ferme stdinXS
    {
      /* Exécuter le programme */
      system("pwd");
      fichier=fopen("std.txt","r");
      if ((freopen("std.txt", "r", stdin)) != NULL)
	gets(std);
      //!!! réouvrir stdin !!
      fclose(fichier);
      freopen("/dev/tty","r",stdin);
      freopen("/dev/tty","w",stdout);
      //      system("rm std.txt");

    }
  else
    {
      fprintf(stderr,"erreur lors de la redirection de la sortie ");
      exit(EXIT_FAILURE);
    }

  strncpy(strOut,std, strlen(std));
}

void create_main_folder (const char name[],const char*path, char fname[]){ // client ou server // retourne le chemin pour la supression
  int pid = getpid();
  char * pids;
  pids=malloc(30);
  sprintf(pids,"%d",pid);
  char mk [7]="mkdir ";
  char *cmd;
  cmd =malloc(100);
  char *final_name;
  final_name =malloc(100);
  fprintf(stderr,"mkdir1#%s#\n",path);
  strcpy(final_name,name);
  final_name=strncat(final_name,pids,strlen(pids));  
  strncpy(cmd,mk,7);
  cmd=strncat(cmd,path,strlen(path));
  cmd=strncat(cmd,"/",1);
  cmd=strncat(cmd,final_name,strlen(final_name));
  system(cmd);

  free(cmd);
  free(pids);

  strncpy(fname,final_name,strlen(final_name));
  fname[strlen(final_name)]='\0';

  free(final_name);
}


void clean_stdin(void)
{
  int c;
    
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}
