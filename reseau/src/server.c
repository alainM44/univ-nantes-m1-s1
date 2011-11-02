#include "network.h"
#include "messages.h"
#include "gestion_menu.h"


void renvoi (int sock);


int main (int argc, char ** argv){
  int sd, longueur_adresse_courant, socket_descriptor;
  sockaddr_in adresse_locale, adresse_client_courant ;// structure d'adresse locale
  hostent* ptr_host;
  char nom_machine [TAILLE_MAX_NOM+1];
  int nouv_socket_descriptor;

  fprintf(stderr,"lauching server \n");
  /* Le serveur se met en place  */
  if ((sd = server_answer_connect(socket_descriptor,nom_machine,adresse_locale,ptr_host)) <  0   )
    
    {
      perror("connexion avec le client impossible");
      exit(1);
    }
    

  /* Le serveur se met en écoute */
  longueur_adresse_courant = sizeof(adresse_client_courant);
  for(;;){
    
    if ((nouv_socket_descriptor=accept(sd,(sockaddr*)(&adresse_client_courant),&longueur_adresse_courant))<0)
      {
	perror("erreur : impossible d'accepter la connexion avec le client");
	exit(1);
      }
    fprintf(stderr,"connexion d'un client\n");
    renvoi(nouv_socket_descriptor);

    
  }
  close(sd);
  close(nouv_socket_descriptor);
  fprintf(stderr,"end server\n");
  return 0;
}

void renvoi (int sock){
  int i;
  bool fin=false;
  MESSAGE message;
  while(!fin)
    {
      
      // frag_and_send(sock,"test.txt");
      // frag_and_send(sock,"Rapport.pdf");
      receive_serveur (sock,message,&fin);
    }
    fprintf(stderr,"deconect\n"); 
  if( (i= close(sock)) <0  )
    fprintf(stderr,"close sock %s",strerror(errno)); 
  exit (EXIT_SUCCESS);
}



  
	  
