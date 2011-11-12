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
  char folder_name[100];
  int pid=getpid();
  if (argc != 2)
    {
      perror("usage : client<adresse-serveur>");
      exit(1);
    }
  prog = argv[0];
  host = argv[1];
  
      final_socket = client_request_connect(socket_descriptor, host,adresse_locale,ptr_host);

  menu(final_socket,folder_name);

  close(final_socket);
  printf("connexion avec le serveur fermee, fin du client%d .\n",pid);
 
  exit(0);

} 
