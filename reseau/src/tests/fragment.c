#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../messages.h"




int main (int argc, const char*argv[]){
  int file,fileout,nblu,nbec;
  char num[200];
  //  char data[200];
  char buffer[MTU];
  int nb_f;
  int reste;
  char fileout_name [30];
  struct stat statbuf ;
  int filesize;

  strcpy(fileout_name,"out.jpg");
  stat(argv[1],&statbuf);  /// the_file, le fichier a lire
  filesize = (long)(statbuf.st_size); 
  
  if (argc!=2)
    {
      fprintf(stderr,"Nombre d'argument insuffisant\n");
      exit(EXIT_FAILURE);
    }
  //init des variables
  if (( nb_f= filesize/MTU )<=1)
    {
      fprintf(stderr,"Pas de fragmentation taille : %d \n",filesize);
      exit(EXIT_FAILURE);
    }
  reste = filesize-nb_f*MTU;

  
  fprintf(stderr,"Fichier de %d .On va fragmenter en %d paquets il restera un paquet de %d ocets\n",filesize,nb_f,reste);
  file=open(argv[1],O_RDWR);
  fileout = open(fileout_name,O_WRONLY| O_CREAT);
  lseek(fileout,0,SEEK_SET);
  DATA data ;        
      sprintf(data.tab, "%s", "\0");
  for (int i=1;i<=nb_f;i++)
    {

      //   nblu=read(file,data.tab,MTU);
      if((      nblu=read(file,data.tab,MTU))==-1 )
        {
          fprintf(stdout,"read : %s",strerror(errno));
          exit(EXIT_FAILURE);
        }

      data.ID_data=i;
      data.offset=nblu+1
;      fprintf(stderr,"data %d contenant %d octets  ",data.ID_data,nblu);
      if((  nbec=write(fileout,data.tab,MTU))== -1)
        {
          fprintf(stdout,"write %s",strerror(errno));
          exit(EXIT_FAILURE);
        }
      fprintf(stderr,"%d o écrits \n",nbec);

      //      nbec = write(fileout,data.tab,MTU);
      //      strcpy(data.tab,"\0");
      /*   { */
      //          fprintf(stdout,"strcpy %s",strerror(errno)); */
      /*     exit(EXIT_FAILURE); */
      /*   } */
      sprintf(data.tab, "%s", "\0");

      //      data.tab="\0";
    }
  
  
  read(file,data.tab,reste);
      fprintf(stderr,"reste %d contenant %d octets  ",data.ID_data,nblu);
  data.ID_data=nb_f;
  data.offset=nblu+1;
  //	fprintf(stderr,"%s %d contenant %d octets\n",,data.ID_data,nblu);
nbec= write(fileout,data.tab,reste);
  fprintf(stderr,"%d o écrits \n",nbec);
  

  close(fileout);

  // on creer la copie


  return EXIT_SUCCESS;
}
