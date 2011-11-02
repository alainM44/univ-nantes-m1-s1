#include "network.h"
#include "messages.h"
#include "gestion_menu.h"



int main(int argc, char **argv)
{
  int socket_descriptor, final_socket;
  sockaddr_in adresse_locale;
  hostent * ptr_host;
  servent * ptr_service;
  char buffer[256];
  char * prog;
  char * host;
  char* mesg;
  int longueur;
  char folder_name[30];
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


  
  final_socket = client_request_connect(socket_descriptor, host,adresse_locale,ptr_host); 
  
  create_main_folder("CLIENT",folder_name);
  // folder_name[strlen(folder_name)]='\0';
  fprintf(stderr,"cli#%s#\n",folder_name);
  menu(final_socket,folder_name);
  //  receve_and_merge(final_socket,"out.pdf");
   
 
 
  //printf("\nfin de la reception.\n");
  close(final_socket);
  printf("connexion avec le serveur fermee, fin du programme.\n");
 
  exit(0);

} 
