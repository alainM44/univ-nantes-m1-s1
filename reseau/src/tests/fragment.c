#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys\stat.h>

int lectureNOctets(int descIn, int n, char*res);
int fragment_file(int desc);
int MTU = 1500;


int main (int argc, const char*argv[]){
  int file,fd,nblu,nbec;
  char num[200];
  char paquet[200];
  char buffer[MTU];
  int nb_f;
  int reste;
 
 struct stat statbuf ;
  int filesize;
  
  stat(argv[1],&statbuf);  /// the_file, le fichier a lire
  filesize = (long)(statbuf.st_size)/8; 
  
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

 fprintf(stderr,"On va fragmenter en %d paquets il restera un paquet de %d \n",nb_f,reste);
  file=open(argv[1],O_RDWR);
 strcpy(buffer,"");
 strcpy(paquet,"");
  for (int i=1;i<nb_f;i++)
    {
     
      sprintf(num, "%i", i);
      strcat(paquet,num);
      strcat(paquet,".txt");
      
      fd = open(paquet,O_WRONLY| O_CREAT| O_TRUNC| O_BINARY,
    S_IREAD| S_IWRITE| S_IEXEC);
      nblu=read(file,(char *)buffer,MTU);
      fprintf(stderr,"paquet : %d \n nb lu %d, buffer  %s",i,nblu,buffer);
      if(  nbec=write(fd,(char *)buffer,1500)== -1)
	{
	  fprintf(stdout,"%s",strerror(errno));
	  exit(EXIT_FAILURE);
	}
      fprintf(stderr,",nb write %d \n",nbec);
      close(fd);
      buffer[0]='\0';
      strcpy(paquet,"");
      nblu=0;
    }
  // dernier paquet du reste
      sprintf(num, "%i", nb_f);
      strcat(paquet,num);
      strcat(paquet,".txt");
      fd = open(paquet,O_CREAT|O_RDWR);
      nblu=read(file,buffer,reste);
      fprintf(stderr,"nb lu %d \n",nblu);
      if(  nbec=write(fd,buffer,sizeof(buffer))== -1)
	{
	  fprintf(stdout,"%s",strerror(errno));
	  exit(EXIT_FAILURE);
	}
      fprintf(stderr,"nb write %d \n",nbec);
      close(fd);

  close(file);

  // on creer la copie
buffer[0]='\0';

      strcpy(paquet,"");

 int fd2 = open("RESULTAT.jpg",O_CREAT|O_RDWR);
  for (int i=1;i<nb_f+1;i++)
    {buffer[0]='\0';
      sprintf(num, "%i", nb_f);
      strcat(paquet,num);
      strcat(paquet,".txt");
      fd = open(paquet,O_RDWR);
      nblu=read(file,buffer,MTU);
      fprintf(stderr,"paquet : %d \n nb lu %d, buffer taille %d",i,nblu,sizeof(buffer));
      if(  nbec=write(fd2,buffer,nblu)== -1)
	{
	  fprintf(stdout,"%s",strerror(errno));
	  exit(EXIT_FAILURE);
	}
      fprintf(stderr,",nb write %d \n",nbec);
      close(fd);
      //      strcpy(buffer,"");
buffer[0]='\0';
      strcpy(paquet,"");
    }

  return EXIT_SUCCESS;
}
