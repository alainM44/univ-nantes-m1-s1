#include "network.h"
#include "messages.h"


void renvoi (int sock);
void frag_and_send(int sock,char file[]);

int main (int argc, char ** argv){
  int sd, longueur_adresse_courant, socket_descriptor;
  sockaddr_in adresse_locale, adresse_client_courant ;// structure d'adresse locale
  hostent* ptr_host;
  char nom_machine [TAILLE_MAX_NOM+1];
  int nouv_socket_descriptor;

  fprintf(stderr,"lauching server \n");
  /* Le serveur se met en place  */
  if ((sd = server_answer_connect(socket_descriptor,nom_machine,adresse_locale,ptr_host)) <  0   )
    
    {
      perror("connexion avec le client impossible");
      exit(1);
    }
    

  /* Le serveur se met en écoute */
  longueur_adresse_courant = sizeof(adresse_client_courant);
  for(;;){
    
    if ((nouv_socket_descriptor=accept(sd,(sockaddr*)(&adresse_client_courant),&longueur_adresse_courant))<0)
      {
	perror("erreur : impossible d'accepter la connexion avec le client");
	exit(1);
      }
    fprintf(stderr,"connexion d'un client\n");
    renvoi(nouv_socket_descriptor);

    
  }
  close(sd);
  close(nouv_socket_descriptor);
  fprintf(stderr,"end server\n");
  return 0;
}

void renvoi (int sock){
  int i;
  MESSAGE_DATA message;
  frag_and_send(sock,"Rapport.pdf");
      // frag_and_send(sock,"test.txt");

  if( (i= close(sock)) <0  )
    fprintf(stderr,"close sock %s",strerror(errno)); 
  exit (EXIT_SUCCESS);
}




void frag_and_send(int sock, char file_to_frag[])
{
  FILE* file;
   int nblu,nbec,res;
  int nb_f;
  int reste;
  struct stat statbuf ;
  int filesize;

  
  stat(file_to_frag,&statbuf);  /// the_file, le fichier a lire
  filesize = (long)(statbuf.st_size); 

  //init des variables
  if (( nb_f= filesize/TAILLEMAXDATA )<1)
    {
      fprintf(stderr,"Pas de fragmentation taille : %d pour une division de %d\n",filesize,TAILLEMAXDATA);
      exit(EXIT_FAILURE);
    }
  reste = filesize-nb_f*TAILLEMAXDATA;

  
  fprintf(stderr,"Fichier %s de %d .On va fragmenter en %d paquets il restera un paquet de %d ocets\n",file_to_frag,filesize,nb_f,reste);

  if( (file=fopen(file_to_frag,"rb"))<0 )
    {
      fprintf(stdout,"open : %s",strerror(errno));
      exit(EXIT_FAILURE);
    }


  MESSAGE_DATA message;

  message.data.ID_data=0;
  message.data.offset=1;
  message.data.MF=0;
  message.data.taille=0;
 
  for (int i=1;i<=nb_f;i++)
    {
      if( (nblu=fread(message.data.tab,1,TAILLEMAXDATA,file))==-1 )
        {
          fprintf(stdout,"read : %s",strerror(errno));
          exit(EXIT_FAILURE);
        }
      message.data.taille=nblu;
      message.data.ID_data=i;
      message.data.offset+=nblu;
      message.data.MF=1;
      message.ID_message=i;

      fprintf(stderr,"message numéro %d contenant %d octets\n ",message.data.ID_data,nblu);
      //  fprintf(stderr,"test");           
      if( (res= send_data(sock,message)) ==-1)
        {
          fprintf(stderr,"sed_data %s",strerror(errno));
          exit(EXIT_FAILURE);
        }

      fprintf(stderr,"paquet %d envoyé offset : %d  \n",message.data.ID_data,message.data.offset);
    }


  //on lit le reste


  if((nblu=fread(message.data.tab,1,reste,file))<0)
    fprintf(stderr,"sed_data %s",strerror(errno)); 
  
  //  fprintf(stderr,"reste %d contenant %d octets  ",mesedata.ID_data,nblu);
  message.data.ID_data+=1;
  message.data.offset+=nblu;
  message.data.taille=nblu;
  message.data.MF=0;
  message.ID_message=nb_f+1;

  if( ( res= send_data(sock,message)) ==-1)
    {
      fprintf(stdout,"sed_data %s",strerror(errno));
      exit(EXIT_FAILURE);
    }
  
  //  fprintf(stderr,"%d o écrits \n",nbec);
  fprintf(stderr,"Dernier paquet %d, contenant %d o envoyés (reste %d) offset : %d  \n",message.data.ID_data,nblu,reste,message.data.offset);  


  fclose(file);
  fprintf(stderr,"FIN FRAG");


}
  
	  
