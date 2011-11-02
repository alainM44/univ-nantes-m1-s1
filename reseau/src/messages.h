//DATE LIMITE 17 novembre
#ifndef H_MESSAGES
#define H_MESSAGES

#define TAILLEMAXDATA 256
#define TAILLEMAXCOMMANDE 100
#define MTU 1500




/* struct commande { */
/*   int Id_commande; */
/*  ; */
/* }; */
/* typedef struct commande COMMANDE; */


struct data {
  int ID_data;
  int offset; 
  int taille;
  int Frag;
  int MF;
  char tab [TAILLEMAXDATA];

};
typedef struct data DATA;

typedef enum {DAT=0,COM=1,QUIT=2}MessageClient; 

struct message{
  int ID_message;
  MessageClient type;
  char tab [TAILLEMAXCOMMANDE] ;
};
typedef struct message MESSAGE ;




struct message_d{
  int ID_message;
  DATA data;
};
typedef struct message_d MESSAGE_DATA;





#endif
