#include "gestion_menu.h"
#include "network.h"






int menu(int sock,char folder_name []){
  bool end;
  end=false;
  char *record;
  char param[100];
  char out_name[100];
  char cmd[100];
  int comande;
  MESSAGE message;
  char *path ;
  path = malloc(100);
  give_path(path);
  create_main_folder("CLIENT",path,folder_name);

  fprintf(stderr,"path1 #%s#\n",path);
  path[strlen(path)]='/';
fprintf(stderr,"path11 #%s#\n",path);
   strcat(path,folder_name);
    path[strlen(path)+1]='/';

   fprintf(stderr,"path2 #%s#\n",path);

  record=malloc(1000);
  //  param=malloc(1000);
  //  sprintf(record,"%s","clear");
  system(record);
  while(!end){
    clean_stdin();
 /* give_path(path); */
 /*  path[strlen(path)-1]='/'; */
 /*   strcat(path,folder_name); */
 /*  path[strlen(path)-1]='/'; */

    //    give_path(path);
    //    strncat(path,
    fprintf(stderr,"\n**************************************\n***********MENU CLIENT FTP************\n**************************************\nN°   COMMAND \n1 -> Listing folder \n2 -> Dowload file  \n3 -> Upload file \n4 -> switch to the folder \n5 -> Enter a commande \n6 -> Quit \n\n your current folder : #%s#\nEnter a command number  : ",path);
    // getline(char **lineptr, size_t *n, FILE *stream);
    scanf("%d",&comande);
    fprintf(stderr,"commande choisie : %d",comande);
 
    system(record);
    clean_stdin();
    switch(comande) {

    case 1 :
      fprintf(stderr," LSSSSS\n",comande);
      sleep(2);
      break;
    case 2 :
      fprintf(stderr," File name to download : ",comande);
      gets(param);
      //prepare command to send
      message.type=0;
      strncpy(message.tab,param,strlen(param));
      message.tab[strlen(param)]='\0';
      send_commande(sock,message) ;
      //init de out_name
      strcpy(out_name,path);
      out_name[strlen(path)]='/';
      out_name[strlen(path)+1]='\0';
      fprintf(stderr,"outname1 #%s#\n",out_name);
      fprintf(stderr,"param #%s#\n",param);
      strcat(out_name,param);
      out_name[strlen(out_name)]='\0';

      fprintf(stderr,"outname2 #%s#\n",out_name);

           receve_and_merge(sock,out_name);
	   // fprintf(stderr," Low dowload of file #%s# please wait... : ",message.tab);
      //      sleep(2);
      break;
    case 3 :
      fprintf(stderr," File name to upload : ",comande);
      gets(param);
      //prepare command to send
      message.type=1;
      strncpy(message.tab,"out",3);
      strncat(message.tab,param,strlen(param));
      fprintf(stderr,"messtab#%s#\n",message.tab);
      //      message.tab[strlen(param)]='\0';
      send_commande(sock,message) ;
      
      frag_and_send(sock,param);

      fprintf(stderr," Low uoload of fie : %s  please wait... : ",param);
      sleep(2);
      break;
    case 4 :
      fprintf(stderr,"Give the path : ",comande);
      scanf("%s",param);
      sleep(2);
      fprintf(stderr," new location %s ",param);
      sleep(2);
      break;
    case 5 : 
      fprintf(stderr,"Enter the command: ");
      gets(param);
      strcpy(cmd,param);
      strcat(cmd," ");
      strcat(cmd,path);

      //      cmd[strlen(path)]='/';
      // cmd[strlen(path)+1]='\0';
      //      fprintf(stderr,"param #%s#\n",param);
      // strcat(cmd,param);
      cmd[strlen(cmd)]='\0';
      fprintf(stderr,"#%s#",cmd);
      system(cmd);

      break;
    case 6 :
      message.type=QUIT;
      send_commande(sock,message) ;
      end=true;
      break;
    
    default : 
      fprintf(stderr,"Invalid command");
      sleep(2);
    }	   
  }
  free(record);
  //  free(param);
  fprintf(stderr,"*****CLIENT_END*****");
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


      system("rm std.txt");

    }
  else
    {
      fprintf(stderr,"erreur lors de la redirection de la sortie ");
      exit(EXIT_FAILURE);
    }
  //  fprintf(stderr,"SDDDDDDDDDDDDDDDDDDDDDDDD");
  //sprintf(strOut,"%s",std);
  //strOut=malloc(strlen(std)*sizeof(char));
  strncpy(strOut,std, strlen(std));
  fprintf(stderr,"give path#%s#\n",strOut);
}

char* create_main_folder (const char name[],const char*path, char fname[]){ // client ou server // retourne le chemin pour la supression
  int pid = getpid();
  char * pids;
  pids=malloc(30);
  sprintf(pids,"%d",pid);
  FILE*fichier;
  char mk [7]="mkdir ";
  //  char cd [7]="cd" 
    //    cd =malloc(100);
  char *cmd;
  cmd =malloc(100);
  /* char* path; */
  /* path = malloc(100); */
  char *final_name;
  final_name =malloc(100);
  //  give_path(path);
  fprintf(stderr,"mkdir1#%s#\n",path);
  strcpy(final_name,name);
  final_name=strncat(final_name,pids,strlen(pids));  
    fprintf(stderr,"final name1#%s#\n",final_name);
  strncpy(cmd,mk,7);
  fprintf(stderr,"finalnale2#%s#\n",cmd);
  cmd=strncat(cmd,path,strlen(path));
  //on rajoute le /
  cmd=strncat(cmd,"/",1);
  
  cmd=strncat(cmd,final_name,strlen(final_name));
    fprintf(stderr,"cmd#%s#\n",cmd);


  system(cmd);
  fprintf(stderr,"Folder %s created\n",final_name);
  //  free(path);
  free(cmd);
  free(pids);
 
  
  
  // fprintf(stderr,"fina#%s#\n",final_name);
  strncpy(fname,final_name,strlen(final_name));

  fname[strlen(final_name)]='\0';
  fprintf(stderr,"fname#%s#\n",fname);
  free(final_name);
}


void clean_stdin(void)
{
  int c;
    
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}
