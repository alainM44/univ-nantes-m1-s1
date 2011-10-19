#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

int lectureNOctets(int descIn, int n, char*res);

int main (int argc, const char*argv[]){
  int file;
  char*res;
  int p,n;

  if (argc!=4)
    {
      fprintf(stderr,"Nombre d'argument insuffisant\n");
      exit(EXIT_FAILURE);
    }
  //init des variables
  file=open(argv[1],O_RDONLY);
  p=atoi(argv[2]);
  n=atoi(argv[3]);
  res=malloc(n*sizeof(char));

  fprintf(stdout,"p : %d\nn : %d\n",p,n);
  if (file==-1){
    fprintf(stderr,"Echec ouverture du fichier : %s",strerror(errno));
    exit(EXIT_FAILURE);
  }
   
  if ( lseek(file, p, SEEK_SET)==-1)
    {
      fprintf(stderr,"Echec lecture du fichier : %s",strerror(errno));
      exit(EXIT_FAILURE);
    }
    
  if (lectureNOctets(file,n,res)==-1)
    {
      fprintf(stderr,"Echec lecture du fichier : %s",strerror(errno));
      exit(EXIT_FAILURE);
    }
  
  fprintf(stdout,"res : %s\n",res);
  close(file);
  return EXIT_SUCCESS;
}

int lectureNOctets(int descIn, int n, char*res){
  return read(descIn,res,n);
}
