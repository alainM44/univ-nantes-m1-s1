#include "network.h"
#include "messages.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int send_data (int sock_descriptor, MESSAGE_DATA data);
MESSAGE_DATA receive_data (int sock_descriptor,MESSAGE_DATA data);

void renvoi (int sock){
  char buffer[256];
  int longueur;
  MESSAGE_DATA message;
   sprintf(message.data.tab, "%s", "datatatatatatatatatat");

  sprintf(buffer,"%s","reponse du serveur : connexion acceptée");
  send_data (sock,message);
  //mise en attente du prog pour simuler un delai de transmission
  //  sleep(3);
  fprintf(stderr,"rep : %s. \n",buffer);
  //  write(sock,buffer,strlen(buffer)+1);
  //  fprintf(stderr,"message envoye. \n");
  close(sock);
  return;
}

 


//server_answer_connect(socket_descriptor,nom_machine,adresse_locale,ptr_host) <  0   ))
int main (int argc, char ** argv){
  //  int res;
  int sd, longueur_adresse_courant,res, socket_descriptor;
  
  sockaddr_in adresse_locale, adresse_client_courant ;// structure d'adresse locale
  hostent* ptr_host;
  servent* ptr_service;
  char nom_machine [TAILLE_MAX_NOM+1];
  int nouv_socket_descriptor;
  fprintf(stderr,"lauching server \n");

  
  if ((sd = server_answer_connect(socket_descriptor,nom_machine,adresse_locale,ptr_host)) <  0   )
    
    {
      perror("connexion avec le client impossible");
      exit(1);
    }
    

  //  server_answer_connect(socket_descriptor,nom_machine, adresse_locale,ptr_host);
  longueur_adresse_courant = sizeof(adresse_client_courant);
  //  res = server_answer_connect(socket_descriptor,nom_machine,adresse_locale,ptr_host);
  for(;;){
    
    if ((nouv_socket_descriptor=accept(sd,(sockaddr*)(&adresse_client_courant),&longueur_adresse_courant))<0)
      {
	 perror("erreur : impossible d'accepter la connexion avec le client");
	 exit(1);
       }
    fprintf(stderr,"connexion d'un client\n");
    renvoi(nouv_socket_descriptor);

    
  }
  fprintf(stderr,"end server\n");
  return 0;
}

