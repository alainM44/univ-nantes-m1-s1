#ifndef H_NETWORK
#define H_NETWORK
#include "messages.h"


int send_data (int sock, MESSAGE_DATA message,int size);

int receive_data (int sock,MESSAGE_DATA message, int size);

int client_request_connect(int i);

int serveur_answer_connect(int i);

int client_request_deconnect(int i);

int serveur_answer_deconnect(int i);

#endif

