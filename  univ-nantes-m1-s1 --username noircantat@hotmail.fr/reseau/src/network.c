#include "network.h"

#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

int send_data (int sock,Messsage message,int size){

  return 0;
}

int receive_data (int sock,Messsage message, int size){
  return 0;
}

int client_request_connect(char* host){
  sockaddr_in adresse_locale;
  hostent * ptr_host;

  if((ptr_host = gethostbyname(host)) == NULL)
    {
      perror("impossible de trouver le serveur a partir de son adresse.");
      exit(1);
    }
    
  bcopy((char*)ptr_host->h_addr, (char*)&adresse_locale.sin_addr, ptr_host->h_length);
  adresse_locale.sin_family = AF_INET;


  adresse_locale.sin_port = htons(5000);
  printf("numero de port pour la connexion au serveur : %d \n", ntohs(adresse_locale.sin_port));

  if ((socket_descriptor =socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("impossible de creer la socket de connexion avec le serveur.");
      exit(1);
    }
  
  if((connect(socket_descriptor, (sockaddr*)(&adresse_locale), sizeof(adresse_locale))) < 0)
    {
      perror("impossible de se connecter au serveur.");
      exit(1);
    }
    
  printf("connexion etablie avec le serveur. \n");
  return 0;

}

int serveur_answer_connect(int i){

  return 0;
}

int client_deconnect(int i){
  close(socket_descriptor);
  printf("connexion avec le serveur fermee, fin du programme.\n");
  return 0;
}

int serveur_deconnect(int i){
  return 0;
}


