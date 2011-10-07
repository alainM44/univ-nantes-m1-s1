#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h> // pour les sockets
#include <sys/socket.h> // pour les sockets
#include <netdb.h>
#include <string.h>
#define TAILLE_MAX_NOM 256


typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;


void renvoi (int sock){
  char buffer[256];
  int longueur;

    if ((longueur = read(sock,buffer, sizeof(buffer))) <=0)
    return;

  printf("message lu : %s \n", buffer);
  buffer[0] ='R';
  buffer[1] ='E';
  buffer[longueur] ='#';
  buffer[longueur+1] ='\0';

  printf("message apres traitement : %s \n",buffer);
  printf("renvoi du message traite.\n",buffer);

  //mise en attente du prog pour simuler un delai de transmission
  sleep(3);
  write(sock,buffer,strlen(buffer)+1);
  printf("message envoye. \n");
  return;
}



int main(int argc, char **argv)
{
  int socket_descriptor, nouv_socket_descriptor,    longueur_adresse_courant;
  sockaddr_in adresse_locale, adresse_client_courant ;// structure d'adresse locale
  hostent* ptr_hote;
  servent* ptr_service;
  char machine [TAILLE_MAX_NOM+1];

  gethostname(machine,TAILLE_MAX_NOM);

  //recuperation de la structure  d'adresse en utilisant le nom
  if ((ptr_hote = gethostbyname(machine))== NULL)
    {
      perror("error : impossible de trouver le serveur à partir de son nom");
      exit(1);
    }
  
  
  // initialisation de la structure adresse_locale avec les infos recuperee
  
  bcopy((char*)ptr_hote->h_addr, (char*)&adresse_locale.sin_addr, ptr_hote->h_length);
  adresse_locale.sin_family = ptr_hote->h_addrtype; // ou AF_INET
  adresse_locale.sin_addr.s_addr = INADDR_ANY; // ou AF_INET
  
  //2 façons de defnir le service que l'on va utiliser à distance 
  /*
  //solution 1
  if ((ptr_service = getservbyname("irc","tpc")) == NULL)
  {
  perror("erreur : impossible de récupérer le numéro de port du service desire");
  exit(1);
  }
  */
  
  //solution 2 utiliser un nouveau numéro de port 
  
  adresse_locale.sin_port= htons(5000);
  printf(" numero de port pour la connexion au serveur : %d \n",ntohs(adresse_locale.sin_port));
  // ntohs(ptr_service->s_port);
  
  //creation de la socket
  if ((socket_descriptor = socket(AF_INET, SOCK_STREAM,0))<0)
    {
      perror("erreur : impossible de creer la socket de connexion avec le client");
      exit(1);
    }
  
  //association du socket socket_descriptor à la structure d'adresse adresse_locale
  if((bind(socket_descriptor, (sockaddr*)(&adresse_locale),sizeof(adresse_locale)))<0)
    {
      perror("erreur : impossible de lier la socket a l'adresse de connexion");
      exit(1);
    }

  //init de la file d'écoute
  listen(socket_descriptor,5);
  //attente des connexions et tdt des donnees reçues
  for(;;)
    {
      longueur_adresse_courant = sizeof(adresse_client_courant);
      printf("erreur avant accept\n");
      //adresse_client_courant sera renseigné par accept via les infos du connect
      if ((nouv_socket_descriptor=accept(socket_descriptor,(sockaddr*)(&adresse_client_courant),&longueur_adresse_courant))<0)
	{
	  perror("erreur : impossible d'accepter la connexion avec le client");
	  exit(1);
	}

      //tdt du message
      printf("reception d'un message.\n");
      renvoi(nouv_socket_descriptor);
      close(nouv_socket_descriptor);

    }
      close(socket_descriptor);
}	 
	 
	 
