#include "network.h"
#include "messages.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>


int client_request_connect( int socket_descriptor, char* host, sockaddr_in adresse_locale,  hostent * ptr_host);
int send_data (int sock_descriptor, MESSAGE_DATA data);
MESSAGE_DATA receive_data (int sock_descriptor,MESSAGE_DATA data);

int main(int argc, char **argv)
{
  int socket_descriptor;
  sockaddr_in adresse_locale;
  hostent * ptr_host;
  servent * ptr_service;
  char buffer[256];
  char * prog;
  char * host;
  char* mesg;
  int longueur;

  if (argc != 2)
    {
      perror("usage : client<adresse-serveur>");
      exit(1);
    }

  prog = argv[0];
  host = argv[1];
  mesg = argv[2];

  printf("nom de l'executable : %s \n", prog);
  printf("adresse du serveur : %s \n", host);
  // printf("message envoye : %s \n", mesg);


  
 int result = client_request_connect(socket_descriptor, host,adresse_locale,ptr_host); 

/*  int flag; */
 MESSAGE_DATA reponse;
 /* fd_set rfds; */
 /* struct timeval tv; */
 /* int retval; */
 /* // Surveiller stdin (fd 0) en attente d'entrées */
 /* FD_ZERO(&rfds); */
 /* FD_SET(socket_descriptor, &rfds); */
 /* /\* Pendant 5 secondes maxi *\/ */
 /* tv.tv_sec = 5; */
 /* tv.tv_usec = 0; */
 /* retval = select(1, &rfds, NULL, NULL, &tv); */
 /* /\* Considerer tv comme indéfini maintenant ! *\/ */
 /*    if (retval) */
 /*      { */
 /*        fprintf(stderr,"Données disponibles maintenant\n"); */
 /* 	//	reponse=receive_data(socket_descriptor,reponse); */
 /* 	/\* FD_ISSET(0, &rfds) est vrai *\/ */
 /*      } */
 /*    else */
 /*      printf("Pas de données depuis 5 secondes\n"); */
 /*    exit(0); */

 
 // fprintf(stderr,"avant wil\n");
 // while( sizeof(reponse = receive_data(socket_descriptor,reponse))> 0   )
 // sleep(2);
 
 reponse=receive_data(result,reponse);
 //write(1, reponse.data.tab, sizeof(reponse.data.tab));
 //fprintf(stderr,"%s",reponse.data.tab);
 printf("#%s#\n",reponse.data.tab);
 
 
 printf("\nfin de la reception.\n");
 close(socket_descriptor);
 printf("connexion avec le serveur fermee, fin du programme.\n");
 
 exit(0);

} 
