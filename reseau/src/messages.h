//DATE LIMITE 17 novembre
#ifndef H_MESSAGES
#define H_MESSAGES

#define TAILLEMAXDATA 256
#define TAILLEMAXCOMMANDE 100
#define MTU 1500




struct commande {
  int Id_commande;
  char tab [TAILLEMAXCOMMANDE];
};
typedef struct commande COMMANDE;


struct data {
  int ID_data;
  int offset; 
  int taille;
  int Frag;
  int MF;
  char tab [TAILLEMAXDATA];

};
typedef struct data DATA;

 
struct message_c{
  int ID_message;

  COMMANDE commande;
};
typedef struct message_c MESSAGE_COMMANDE ;

struct message_d{
  int ID_message;
  DATA data;
};
typedef struct message_d MESSAGE_DATA;




#endif
