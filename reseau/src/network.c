#include "network.h"


int send_data (int sock_descriptor, MESSAGE_DATA message)
{
  if  ( write(sock_descriptor,(char *)&message,sizeof(message)) <0)
    {
      fprintf(stderr,"errr write");
      //perror("write\n");
      fprintf(stderr, "Erreur write %s.\n",strerror(errno));

    }  

  return 0;
}
 
MESSAGE_DATA receive_data (int sock_descriptor,MESSAGE_DATA message)
{
  if ( read(sock_descriptor,(char *)&message,sizeof(message)) <0)
    perror("read\n");
  return message;
}

int  client_request_connect( int socket_descriptor, char* host, sockaddr_in adresse_locale,  hostent * ptr_host)
{
 
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
  //  printf("connexion etablie avec le serveur. \n");
  //  sleep(3);
  return socket_descriptor;

}


int server_answer_connect( int sock_descriptor,char nom_machine[],sockaddr_in adresse_locale,  hostent * ptr_host)
{
  int  longueur_adresse_courant;
  gethostname(nom_machine,TAILLE_MAX_NOM);

  //recuperation de la structure  d'adresse en utilisant le nom
  if ((ptr_host = gethostbyname(nom_machine))== NULL)
    {
      perror("error : impossible de trouver le serveur à partir de son nom");
      exit(1);
    }
  
  // initialisation de la structure adresse_locale avec les infos recuperee
  bcopy((char*)ptr_host->h_addr, (char*)&adresse_locale.sin_addr, ptr_host->h_length);
  adresse_locale.sin_family = ptr_host->h_addrtype; // ou AF_INET
  adresse_locale.sin_addr.s_addr = INADDR_ANY; // ou AF_INET
  adresse_locale.sin_port=htons(5000);
  if ((sock_descriptor =socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("impossible de creer la socket de connexion avec le serveur.");
      exit(1);
    }
  
  if((bind(sock_descriptor, (sockaddr*)(&adresse_locale),sizeof(adresse_locale)))<0)
    {
      perror("erreur : impossible de lier la socket a l'adresse de connexion");
      exit(1);
    }

  //init de la file d'écoute
  listen(sock_descriptor,5);
    
  printf("Serveur en écoute : 5. \n");
  return sock_descriptor;
}

int client_deconnect( int sock_descriptor){
  close(sock_descriptor);
  printf("connexion avec le serveur fermee, fin du programme.\n");
  return 0;
}

int serveur_deconnect(int i){
  return 0;
}


