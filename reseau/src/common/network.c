#include "network.h"
#include <sys/time.h>

/*****************************************************************************************************************************************/
int send_data (int sock_descriptor, MESSAGE_DATA message)
{
  if  ( write(sock_descriptor,(char *)&message,sizeof(message)) <0)
    fprintf(stderr, "Erreur write  : send_data %s.\n",strerror(errno));
  return 0;
}
/*****************************************************************************************************************************************/
MESSAGE_DATA receive_data (int sock_descriptor,MESSAGE_DATA message)
{
  if ( read(sock_descriptor,(char *)&message,sizeof(message)) <0)
      fprintf(stderr, "Erreur read : receive_data %s.\n",strerror(errno));

  return message;
}
/*****************************************************************************************************************************************/
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
  return socket_descriptor;
}
/*****************************************************************************************************************************************/
int server_answer_connect( int sock_descriptor,char nom_machine[],sockaddr_in adresse_locale,  hostent * ptr_host)
{
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
  listen(sock_descriptor,3);
    
  printf("Serveur en écoute : 3. \n");
  return sock_descriptor;
}
/*****************************************************************************************************************************************/
int client_deconnect( int sock_descriptor){
  close(sock_descriptor);
  printf("connexion avec le serveur fermee, fin du programme.\n");
  return 0;
}
/*****************************************************************************************************************************************/
int serveur_deconnect(int i){

  return 0;
}
/*****************************************************************************************************************************************/
void frag_and_send(int sock, char file_to_frag[])
{
  FILE* file;
  long  long  int nblu,res,nb_f,reste,filesize, diff,i;
  MESSAGE messageclient;
  MESSAGE_DATA message;
  struct timeval tv1,tv2;
  struct timezone tz;



  gettimeofday(&tv1, &tz);
  fsize( file_to_frag, &filesize);
  fprintf(stderr,"taille : %lld \n",filesize);

  //init des variables
  if (( nb_f= filesize/(long long int)TAILLEMAXDATA )<1)////!!!!!!!!!!!!!!!!
    {
      fprintf(stderr,"No frag %s taille : %lld for div of %d\n",file_to_frag,filesize,TAILLEMAXDATA);
      return;
      //      exit(EXIT_FAILURE);
    }
  reste = filesize-nb_f*(long long int)TAILLEMAXDATA;
  fprintf(stderr,"File %s of %lld o.\n Will be fracted in %lld data packet of %lld o more one of %llu o\n",
	  file_to_frag,
	  filesize,
	  nb_f,
	  (long long int)TAILLEMAXDATA,
	  reste);
  if( (file=fopen(file_to_frag,"rb"))<0 )
    {
      fprintf(stdout,"open : %s",strerror(errno));
      exit(EXIT_FAILURE);
    }
  message.data.ID_data=0;
  message.data.offset=(long long int)1;
  message.data.MF=0;
  message.data.taille=0;
 
  for (i=1;i<=nb_f;i++)
    {
      if( (nblu=(long long int)fread(message.data.tab,1,(long long int)TAILLEMAXDATA,file))==-1 )
        {
          fprintf(stdout,"read : %s",strerror(errno));
          exit(EXIT_FAILURE);
        }
      message.data.taille=nblu;
      message.data.ID_data=i;
      message.data.offset+=nblu;
      message.data.MF=1;
      message.ID_message=i;
      //  fprintf(stderr,"message numéro %d contenant %d octets\n ",message.data.ID_data,nblu);
      if( (res=send_data(sock,message)) ==-1)
        {
          fprintf(stderr,"sed_data %s",strerror(errno));
          exit(EXIT_FAILURE);
        }
      //                   fprintf(stderr,"paquet %lld envoyé offset : %lld  \n",message.data.ID_data,message.data.offset);
      messageclient=receive_commande(sock,messageclient);
    }
  //on lit le reste
  if((nblu=(long long int)fread(message.data.tab,1,reste,file))<0)
    fprintf(stderr,"sed_data %s",strerror(errno)); 
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
 /* fprintf(stderr,"dernier paquet %lld envoyé doffset %lld\n",message.data.ID_data,message.data.offset); */
  gettimeofday(&tv2, &tz);
  diff=(tv2.tv_sec-tv1.tv_sec)* 1000000L+  (tv2.tv_usec-tv1.tv_usec);  
  
  fprintf(stderr,"Frag's time : %lld usec\n",diff);
  fclose(file);
  return;
}
/*****************************************************************************************************************************************/
int receve_and_merge(int sock,char outfile_name[]){
  long long int nbec;
  long long int filesize;
  FILE* outfile;
  MESSAGE_DATA reponse;
  int fin =(-1);
  struct timeval tv1,tv2;
  struct timezone tz;
  long long int diff;
  gettimeofday(&tv1, &tz);
  MESSAGE messack;
  messack.type=5;
  if( (outfile= fopen(outfile_name,"wb"))<0 )
    {
      fprintf(stdout,"read : %s",strerror(errno));
      exit(EXIT_FAILURE);
    }
  while(fin!=0)
    {
      /* reponse.data.ID_data=0; */
      /* reponse.data.offset=0; */
      /* reponse.data.taille=0; */
      //            reponse.data.MF=2; 
      reponse=receive_data(sock,reponse);
      // AFFICHAGE VERBEUX
      //      fprintf(stderr,"Paquet numero %ldd, offset %d de taille: %lld \n",reponse.data.ID_data,reponse.data.offset,reponse.data.taille);
      if((  nbec=(long long int)fwrite(reponse.data.tab,1,reponse.data.taille,outfile))== -1)
        {
          fprintf(stdout,"write %s",strerror(errno));
          exit(EXIT_FAILURE);
        }
      //DEBUG
      //      fprintf(stderr,"contenu(taille%d)#####%s###### \n",nbec,reponse.data.tab);
      //      if (reponse.ID_message%500==0)
      send_commande(sock,messack);
      if (reponse.data.MF==0)
	{
	  fin=0;
	  fprintf(stderr,"Dernier paquet id %lld offset %lld \n",reponse.data.ID_data,reponse.data.offset);
	}


    }
  fclose(outfile);
  fsize( outfile_name, &filesize);
  gettimeofday(&tv2, &tz);
  diff=(tv2.tv_sec-tv1.tv_sec)* 1000000L+  (tv2.tv_usec-tv1.tv_usec);  
  fprintf(stderr,"New file %s, size : %lld o, in : %lld usec\n",outfile_name,filesize,diff);
  return 0;///§!!!!!!
}

/*****************************************************************************************************************************************/
int send_commande (int sock_descriptor, MESSAGE message){
  int res;
  if  (( res=write(sock_descriptor,(char *)&message,sizeof(message))) <0)
    {
      fprintf(stderr,"errr write");
      fprintf(stderr, "Erreur write %s.\n",strerror(errno));
    }  
  //debug
  //  fprintf(stderr, "Write de send_commande:  %do taille du message : %do .\n",res,sizeof(message));
  return res;
}
/*****************************************************************************************************************************************/
MESSAGE receive_commande (int sock_descriptor, MESSAGE message){
  int res;
  if ( (res=read(sock_descriptor,(char *)&message,sizeof(message) )) <0)
    {
      fprintf(stderr,"errr receive_commande : read");
      //perror("write\n");
      fprintf(stderr, "Erreur read %s.\n",strerror(errno));
      perror("read de receive \n");
    }
  //debug
  //  fprintf(stderr, "Read de receive_commande:  %do taille du message : %do .\n",res,sizeof(message));
  return message;
}
/*****************************************************************************************************************************************/
int receive_serveur (int sock_descriptor,MESSAGE message,bool*fin,char*path){
  char cmd[100];
  char std[1000];
  char buffer[1];
  int tube[2];
  int pos=0;
  MESSAGE messageclient;
  cmd[0]='\0';
  buffer[0]='\0';
  fprintf(stderr,"Waiting for client message...\n");
  messageclient=receive_commande(sock_descriptor,message);
  fprintf(stderr,"Message received \n");
  switch(messageclient.type)
    {
    case DOWNLOAD :
      frag_and_send(sock_descriptor,messageclient.tab);
      break;
    case UPLOAD : 
      receve_and_merge(sock_descriptor,messageclient.tab);
      break;
    case COMMANDE :  
      //prepare command to send
      message.type=3;

      strcpy(cmd,"ls ");
      strcat(cmd,path);
      fprintf(stderr,"cmd #%s#\n",cmd);
      pipe(tube);
      dup2(tube[1],STDOUT_FILENO);
      system(cmd);
      read(tube[0],std,5000); //SALE!!!
      close(tube[0]);
      close(tube[1]);
      while(std[pos]!='\0')
	pos++;
      std[pos]='\0'; 
      strcpy(messageclient.tab,std);
      messageclient.tab[strlen(std)]='\0';
      send_commande(sock_descriptor,messageclient);
      sleep(2);
      break;
    case QUIT :
      *fin=true; 
      fprintf(stderr,"quit\n");
      break;
    case SHUTDOWN :
      fprintf(stderr,"shut : ");
      *fin=true; 
      return -1;
      break;
    default  :
      //      fprintf(stderr,"defaut");
      // *fin=true; 
      break;
    }
  return 0;
}
/*****************************************************************************************************************************************/
int fsize(const char * fname, long long int * ptr)
{
  /* Cette fonction calcule la taille du fichier fname */
  FILE * f;
  int ret = 0;
  f = fopen(fname, "rb");   
  if (f != NULL)
    {
      fseeko(f, 0, SEEK_END); /* Placer le file descriptor à la fin du fichier */
      *ptr =ftello(f); /* lire l'offset de la position courante  */
      fclose(f);
    }
  else
    {
      fprintf(stderr, "Erreur  %s \n",strerror(errno));
      ret = 1;
    }
  return ret;
}
/*****************************************************************************************************************************************/
