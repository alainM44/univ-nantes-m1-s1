 #include "network.h"
#include "messages.h"
#include "gestion_menu.h"




int traitement_client(int sock);
int main (int argc, char ** argv){
  int sd, longueur_adresse_courant, socket_descriptor;
  sockaddr_in adresse_locale, adresse_client_courant ;// structure d'adresse locale
  hostent* ptr_host;
  char nom_machine [TAILLE_MAX_NOM+1];
  int nouv_socket_descriptor;
  int fin,pid_pere;
  //Pour fermer brutalement
  char * kill;
  char * pids;
  pid_pere=getpid();
  pids=malloc(30);
  sprintf(pids,"%d",pid_pere);




  kill=malloc(20);
  strcpy(kill,"kill -9 ");
  strcat(kill,pids);
  //////////////////////:/

  fprintf(stderr,"lauching server \n");
  /* Le serveur se met en place  */
  if ((sd = server_answer_connect(socket_descriptor,nom_machine,adresse_locale,ptr_host)) <  0   )
    
    {
      perror("connexion avec le client impossible");
      exit(1);
    }
    

  /* Le serveur se met en écoute */
  longueur_adresse_courant = sizeof(adresse_client_courant);
  while(1){
    if ((nouv_socket_descriptor=accept(sd,(sockaddr*)(&adresse_client_courant),&longueur_adresse_courant))<0)
      {
	perror("erreur : impossible d'accepter la connexion avec le client");
	exit(1);
      }
    switch(fork())
      {
      case 0 ://fils
	if ( ( fin=traitement_client(nouv_socket_descriptor))==(-1))
	  {
	  fprintf(stderr,"return -1\n");
 
	  close(nouv_socket_descriptor);
	  system(kill);
	  exit(0);
	  return -1 ;
	  }

	break;
      case -1: // le pere a un pblm
	perror("erreur :probleme du pere");
	exit(1);
	break;
	  
      default : // pere 
	break;
      }

  }

  close(sd);
  fprintf(stderr,"End server\n");
  close(sd);
  return 0;
}

 int traitement_client (int sock){
  int i;
  bool fin=false;
  MESSAGE message;
  char *path ;
  //  fprintf(stderr,"client connexion nbfils %d\n",nbfils); 
  path = malloc(100);
  give_path(path);

  while(!fin)
    {
      if (( i=receive_serveur (sock,message,&fin,path))==-1)
	{
	  fprintf(stderr,"return -1\n"); 
	  return -1;
	}
    }
  fprintf(stderr,"client deconnexion\n"); 
  return 0 ;
}




