//DATE LIMITE 17 novembre
#define TAILLEMAXDATA 256
#define TAILLEMAXCOMMANDE 100




struct commande {
  int Id_commande;
  char tab [TAILLEMAXCOMMANDE];

};
typedef struct commande COMMANDE;


struct data {
  int Id_data;
  int offset; 
  int Frag;
  char tab [TAILLEMAXDATA];

};
typedef struct data DATA;

 
struct message_c{
  int Id_message;

  COMMANDE commande;
};
typedef struct MESSAGE_COMMANDE ;
struct message_d {
  int Id_message;
  DATA data;
};
typedef struct message_d MESSAGE_DATA;




