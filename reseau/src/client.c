#include "network.h"
#include "messages.h"
#include <sys/time.h>


int receve_and_merge(int sock,char file[]);

int main(int argc, char **argv)
{
  int socket_descriptor, final_socket;
  sockaddr_in adresse_locale;
  hostent * ptr_host;
  servent * ptr_service;
  char buffer[256];
  char * prog;
  char * host;
  char* mesg;
  int longueur;

  if (argc != 2)
    {
      perror("usage : client<adresse-serveur>");
      exit(1);
    }

  prog = argv[0];
  host = argv[1];
  mesg = argv[2];

  printf("nom de l'executable : %s \n", prog);
  printf("adresse du serveur : %s \n", host);
  // printf("message envoye : %s \n", mesg);


  
  final_socket = client_request_connect(socket_descriptor, host,adresse_locale,ptr_host); 

 
  /* MESSAGE_DATA reponse; */
    receve_and_merge(final_socket,"out.pdf");
    // receve_and_merge(final_socket,"out.txt");
 
  // Reponse=receive_data(result,reponse);
  //write(1, reponse.data.tab, sizeof(reponse.data.tab));
  //fprintf(stderr,"%s",reponse.data.tab);
  // printf("#%s#\n",reponse.data.tab);
 
 
  printf("\nfin de la reception.\n");
  close(final_socket);
  printf("connexion avec le serveur fermee, fin du programme.\n");
 
  exit(0);

} 
int receve_and_merge(int sock,char outfile_name[]){
  int /*outfile,*/nblu,nbec,res;
  int nb_f;
  int reste;
  struct stat statbuf ;
  int filesize;
  FILE* outfile;
  
  
   
  if( (outfile= fopen(outfile_name,"wb"))<0 )
    {
      fprintf(stdout,"read : %s",strerror(errno));
      exit(EXIT_FAILURE);
    }

  char buffer[TAILLEMAXDATA];
  MESSAGE_DATA reponse;
  int fin =(-1);

  while(fin!=0)
    {
  
      reponse.data.ID_data=0;
      reponse.data.offset=0;
      reponse.data.taille=0;
      reponse.data.MF=0;
  
      reponse=receive_data(sock,reponse);
      fprintf(stderr,"Paquet numero %d, offset %d de taille: %d \n",reponse.data.ID_data,reponse.data.offset,reponse.data.taille);
      if((  nbec=fwrite(reponse.data.tab,1,reponse.data.taille,outfile))== -1)
        {
          fprintf(stdout,"write %s",strerror(errno));
          exit(EXIT_FAILURE);
        }

      //      fprintf(stderr,"contenu(taille%d)#####%s###### \n",nbec,reponse.data.tab);
      if (reponse.data.MF==0)
	fin=0;
    }
  fclose(outfile);
  
  stat(outfile_name,&statbuf);
  filesize = (long)(statbuf.st_size); 

  fprintf(stderr,"taille du nouveau fichier : %d\n",filesize);

  return 0;///§!!!!!!
}
