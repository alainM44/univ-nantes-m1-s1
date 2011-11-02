#include "network.h"


int send_data (int sock_descriptor, MESSAGE_DATA message)
{
  if  ( write(sock_descriptor,(char *)&message,sizeof(message)) <0)
    {
      fprintf(stderr,"errr write");
      //perror("write\n");
      fprintf(stderr, "Erreur write %s.\n",strerror(errno));

    }  

  return 0;
}
 
MESSAGE_DATA receive_data (int sock_descriptor,MESSAGE_DATA message)
{
  if ( read(sock_descriptor,(char *)&message,sizeof(message)) <0)
    perror("read\n");
  return message;
}

int  client_request_connect( int socket_descriptor, char* host, sockaddr_in adresse_locale,  hostent * ptr_host)
{
 
  if((ptr_host = gethostbyname(host)) == NULL)
    {
      perror("impossible de trouver le serveur a partir de son adresse.");
      exit(1);
    }
    
  bcopy((char*)ptr_host->h_addr, (char*)&adresse_locale.sin_addr, ptr_host->h_length);
  adresse_locale.sin_family = AF_INET;
  adresse_locale.sin_port = htons(5000);
  printf("numero de port pour la connexion au serveur : %d \n", ntohs(adresse_locale.sin_port));

  if ((socket_descriptor =socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("impossible de creer la socket de connexion avec le serveur.");
      exit(1);
    }
  

  if((connect(socket_descriptor, (sockaddr*)(&adresse_locale), sizeof(adresse_locale))) < 0)
    {
      perror("impossible de se connecter au serveur.");
      exit(1);
    }
  //  printf("connexion etablie avec le serveur. \n");
  //  sleep(3);
  return socket_descriptor;

}


int server_answer_connect( int sock_descriptor,char nom_machine[],sockaddr_in adresse_locale,  hostent * ptr_host)
{
  int  longueur_adresse_courant;
  gethostname(nom_machine,TAILLE_MAX_NOM);

  //recuperation de la structure  d'adresse en utilisant le nom
  if ((ptr_host = gethostbyname(nom_machine))== NULL)
    {
      perror("error : impossible de trouver le serveur à partir de son nom");
      exit(1);
    }
  
  // initialisation de la structure adresse_locale avec les infos recuperee
  bcopy((char*)ptr_host->h_addr, (char*)&adresse_locale.sin_addr, ptr_host->h_length);
  adresse_locale.sin_family = ptr_host->h_addrtype; // ou AF_INET
  adresse_locale.sin_addr.s_addr = INADDR_ANY; // ou AF_INET
  adresse_locale.sin_port=htons(5000);
  if ((sock_descriptor =socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("impossible de creer la socket de connexion avec le serveur.");
      exit(1);
    }
  
  if((bind(sock_descriptor, (sockaddr*)(&adresse_locale),sizeof(adresse_locale)))<0)
    {
      perror("erreur : impossible de lier la socket a l'adresse de connexion");
      exit(1);
    }

  //init de la file d'écoute
  listen(sock_descriptor,5);
    
  printf("Serveur en écoute : 5. \n");
  return sock_descriptor;
}

int client_deconnect( int sock_descriptor){
  close(sock_descriptor);
  printf("connexion avec le serveur fermee, fin du programme.\n");
  return 0;
}

int serveur_deconnect(int i){

  return 0;
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
      fprintf(stderr,"Pas de fragmentation de %s taille : %d pour une division de %d\n",file_to_frag,filesize,TAILLEMAXDATA);
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

/* int send_data (int sock_descriptor, MESSAGE_DATA message); */
/* MESSAGE_DATA receive_data (int sock_descriptor,MESSAGE_DATA data); */

void send_commande (int sock_descriptor, MESSAGE message){

  if  ( write(sock_descriptor,(char *)&message,sizeof(message)) <0)
    {
      fprintf(stderr,"errr write");
      //perror("write\n");
      fprintf(stderr, "Erreur write %s.\n",strerror(errno));

    }  
  
}
void receive_serveur (int sock_descriptor,MESSAGE message,bool*fin){
  
  char out_name [100];
  if ( read(sock_descriptor,(char *)&message,sizeof(message)) <0)
    perror("read de receive \n");
      fprintf(stderr, "Attente de reception%s.\n",strerror(errno));

  switch(message.type)
    {
      //down
    case 0 :// fprintf(stderr,"#%s#",message.tab);
            frag_and_send(sock_descriptor,message.tab);
	    
      break;
      //upload
    case 1 : 
 //init de out_name
      /* strcpy(out_name,path); */
      /* out_name[strlen(path)]='/'; */
      /* out_name[strlen(path)+1]='\0'; */
      /* fprintf(stderr,"outname1 #%s#\n",out_name); */
      /* fprintf(stderr,"param #%s#\n",param); */
      /* strcat(out_name,param); */
      /* out_name[strlen(out_name)]='\0'; */

       fprintf(stderr,"messtabserveur #%s#\n",message.tab); 

      receve_and_merge(sock_descriptor,message.tab);


      break;
    case 3 : *fin=true; 

      break;
    
    default  :  fprintf(stderr,"defaut");
      sleep(2);
      *fin=true; 
      break;
    }


}
