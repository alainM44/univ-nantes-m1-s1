#ifndef H_NETWORK
#define H_NETWORK
#include "messages.h"
#define TAILLE_MAX_NOM 256

#include <stdlib.h>
#include <stdio.h>
#include <linux/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
 #include <stdbool.h> 
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct hostent hostent;
typedef struct servent servent;


int send_data (int sock_descriptor, MESSAGE_DATA message);
MESSAGE_DATA receive_data (int sock_descriptor,MESSAGE_DATA data);
void send_commande (int sock_descriptor, MESSAGE message);
void receive_serveur (int sock_descriptor,MESSAGE message,bool*fin);



int client_request_connect( int socket_descriptor, char* host, sockaddr_in adresse_locale,  hostent * ptr_host);
int server_answer_connect(int sock_descriptor,char nom_machine[],sockaddr_in adresse_locale,  hostent * ptr_host);

int client_deconnect( int sock_descriptor);
int serveur_deconnect(int i);
void frag_and_send(int sock,char file[]);
int receve_and_merge(int sock,char file[]);

#endif

