#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;

int main(int argc, char **argv)
{
  int socket_descriptor, longueur;
  sockaddr_in adresse_locale;
  hostent * ptr_host;
  servent * ptr_service;
  char buffer[256];
  char * prog;
  char * host;
  char* mesg;

  if (argc != 3)
    {
      perror("usage : client<adresse-serveur> <message-a-transmettre>");
      exit(1);
    }

  prog = argv[0];
  host = argv[1];
  mesg = argv[2];

  printf("nom de l'executable : %s \n", prog);
  printf("adresse du serveur : %s \n", host);
  printf("message envoye : %s \n", mesg);

  if((ptr_host = gethostbyname(host)) == NULL)
    {
      perror("impossible de trouver le serveur a partir de son adresse.");
      exit(1);
    }

  bcopy((char*)ptr_host->h_addr, (char*)&adresse_locale.sin_addr, ptr_host->h_length);
  adresse_locale.sin_family = AF_INET;
  /*
  if ((ptr_service = getservbyname("irc","tcp")) == NULL)
    {
      perror("impossible de creer la socket de connexion avec le serveur.");
      exit(1);
    }
  
  adresse_locale.sin_port = htons(ptr_service->s_port);
  */

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
    
  /* printf("connexion etablie avec le serveur. \n"); */
  /* printf("envoi d'un message au serveur. \n"); */

  /* if((write(socket_descriptor, mesg, strlen(mesg))) < 0) */
  /*   { */
  /*     perror("impossible d'ecrire le message destine au serveur."); */
  /*     exit(1); */
  /*   } */

  // sleep(3);

  //  printf("message envoye au serveur. \n");

  while((longueur = read(socket_descriptor, buffer, sizeof(buffer)))> 0)
    {
      //      printf("reponse du serveur : \n");
      write(1, buffer, longueur);
    }
    
  printf("\nfin de la reception.\n");
  close(socket_descriptor);
  printf("connexion avec le serveur fermee, fin du programme.\n");
    
  exit(0);
} 
