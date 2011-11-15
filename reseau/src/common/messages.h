#ifndef H_MESSAGES
#define H_MESSAGES
#define TAILLEMAXDATA 512
#define TAILLEMAXCOMMANDE 5000

/* Sont définis içi toutes les structure pour définir les messages utilisés sur les différents canaux. */

typedef enum {DOWNLOAD=1,UPLOAD=2,COMMANDE=3,QUIT=4,SHUTDOWN=5,ACK=6}MessageClient; 
struct message{
  long long  int ID_message;
  MessageClient type;
  char tab [TAILLEMAXCOMMANDE] ;
};
typedef struct message MESSAGE ;


struct data {
  long long  int ID_data;
  long long  int offset; 
  long long  int taille;
  int Frag;
  int MF;
  char tab [TAILLEMAXDATA];

};
typedef struct data DATA;




struct message_d{
  long long  int ID_message;
  DATA data;
};
typedef struct message_d MESSAGE_DATA;





#endif
