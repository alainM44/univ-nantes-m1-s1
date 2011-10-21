#include "network.h"
#include "messages.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


void renvoi (int sock);
int frag_and_send(int sock,char file[]);



int main (int argc, char ** argv){
  //  int res;
  int sd, longueur_adresse_courant,res, socket_descriptor;
  
  sockaddr_in adresse_locale, adresse_client_courant ;// structure d'adresse locale
  hostent* ptr_host;
  servent* ptr_service;
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
  fprintf(stderr,"end server\n");
  return 0;
}

void renvoi (int sock){
  char buffer[256];
  int longueur;
  MESSAGE_DATA message;
  sprintf(message.data.tab, "%s", "datatatatatatatatatat");
  //fprintf(stderr,"rep : %s. \n",message.data.tab);
  //  sprintf(buffer,"%s","reponse du serveur : connexion acceptée");
  send_data (sock,message);
  //mise en attente du prog pour simuler un delai de transmission
  //  sleep(3);
  fprintf(stderr,"rep : %s. \n",message.data.tab);
  //  write(sock,buffer,strlen(buffer)+1);
  //  fprintf(stderr,"message envoye. \n");
  close(sock);
  return;
}

int frag_and_send(int sock,char file_to_frag[])
{
  int file,nblu,nbec,res;
  char num[200];
  //  char data[200];
  char buffer[MTU];
  int nb_f;
  int reste;
  struct stat statbuf ;
  int filesize;

  
  stat(file_to_frag,&statbuf);  /// the_file, le fichier a lire
  filesize = (long)(statbuf.st_size); 
 
  //init des variables
  if (( nb_f= filesize/MTU )<=1)
    {
      fprintf(stderr,"Pas de fragmentation taille : %d \n",filesize);
      exit(EXIT_FAILURE);
    }
  reste = filesize-nb_f*MTU;

  
  fprintf(stderr,"Fichier de %d .On va fragmenter en %d paquets il restera un paquet de %d ocets\n",filesize,nb_f,reste);
  file=open(file_to_frag,O_RDWR);/////////////a securiser
  MESSAGE_DATA message;
  DATA data ;        
  sprintf(data.tab, "%s", "\0");
  for (int i=1;i<=nb_f;i++)
    {
      if( (nblu=read(file,data.tab,MTU))==-1 )
        {
          fprintf(stdout,"read : %s",strerror(errno));
          exit(EXIT_FAILURE);
        }
      
      data.ID_data=i;
      data.offset+=nblu+1;
      
      message.data=data;
      /* fprintf(stderr,"data %d contenant %d octets  ",data.ID_data,nblu);*/
      if( (res= send_data(sock,message)) ==-1)
        {
          fprintf(stdout,"sed_data %s",strerror(errno));
          exit(EXIT_FAILURE);
        }
      
      fprintf(stderr,"paquet %d envoyé offset : %d  \n",data.ID_data,data.offset);
	  
      sprintf(data.tab, "%s", "\0");
      
      //      data.tab="\0";
      
    }
  
  if((nblu=read(file,data.tab,reste))<0)
    perror("read");
  
  //fprintf(stderr,"reste %d contenant %d octets  ",data.ID_data,nblu);
  data.ID_data+=1;
  data.offset+=nblu+1;
  
  //	fprintf(stderr,"%s d%d contenant %d octets\n",,data.ID_data,nblu);
  
  message.data=data;
  /* fprintf(stderr,"data %d contenant %d octets  ",data.ID_data,nblu);*/
  if( ( res= send_data(sock,message)) ==-1)
    {
      fprintf(stdout,"sed_data %s",strerror(errno));
      exit(EXIT_FAILURE);
    }
  
  //  fprintf(stderr,"%d o écrits \n",nbec);
  fprintf(stderr,"paquet %d envoyé offset : %d  \n",data.ID_data,data.offset);  
  
}
  
	  
