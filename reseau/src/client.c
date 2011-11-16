/* FICHIER CLIENT */
#include "common/network.h"
#include "common/messages.h"
#include "common/gestion_menu.h"




void main(int argc, char **argv)
{
  int socket_descriptor, final_socket;
  sockaddr_in adresse_locale;
  hostent * ptr_host;
  char * prog;
  char * host;
  char folder_name[100];
  if (argc != 2)
    {
      perror("usage : client<adresse-serveur>");
      exit(1);
    }
  prog = argv[0];
  host = argv[1];
  
  //mise en place de la connexion avec le serveur.
  final_socket = client_request_connect(socket_descriptor, host,adresse_locale,ptr_host);
  //Lancement de la routine du menu
  menu(final_socket,folder_name);
  client_deconnect(final_socket);

}
