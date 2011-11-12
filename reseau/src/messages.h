//DATE LIMITE 17 novembre
#ifndef H_MESSAGES
#define H_MESSAGES

#define TAILLEMAXDATA 128
#define TAILLEMAXCOMMANDE 5000







struct data {
  long long  int ID_data;
  long long  int offset; 
  long long  int taille;
    int Frag;
    int MF;
  char tab [TAILLEMAXDATA];

};
typedef struct data DATA;

typedef enum {DOWNLOAD=0,UPLOAD=1,COMMANDE=2,QUIT=3,SHUTDOWN=4,ACK=5}MessageClient; 

struct message{
  long long  int ID_message;
  MessageClient type;
  char tab [TAILLEMAXCOMMANDE] ;
};
typedef struct message MESSAGE ;




struct message_d{
  long long  int ID_message;
  DATA data;
};
typedef struct message_d MESSAGE_DATA;





#endif
