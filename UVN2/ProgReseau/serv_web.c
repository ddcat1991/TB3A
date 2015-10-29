#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>


#define BUFSIZE 512
#define BACKLOG 5
enum TypeFichier { NORMAL, REPERTOIRE, ERREUR };

const char* OK200 = "HTTP/1.1 200 OK\r\n\r\n";
const char* ERROR403 = "HTTP/1.1 403 Forbidden\r\n\r\nAccess denied\r\n";
const char* ERROR404 = "HTTP/1.1 404 Not Found\r\n\r\nFile or directory not found\r\n";


/* Fonction typeFichier()
 * argument: le nom du fichier
 * rend une valeur de type enumeration delaree en tete du fichier
 * NORMAL, ou REPERTOIRE ou ERRREUR
 */
enum TypeFichier typeFichier(char *fichier) {
  struct stat status;
  int r;

  r = stat(fichier, &status);
  if (r < 0)
    return ERREUR;
  if (S_ISREG(status.st_mode))
    return NORMAL;
  if (S_ISDIR(status.st_mode))
    return REPERTOIRE;
  /* si autre type, on envoie ERREUR (a fixer plus tard) */
  return ERREUR;
}


/* envoiFichier()
 * Arguments: le nom du fichier, la socket
 * valeur renvoyee: true si OK, false si erreur
 */
#define BUSIZE 1048;
bool envoiFichier(char *fichier, int soc) {
  int fd,r;
  char buf[BUFSIZE];
  ssize_t nread;

  /* A completer.
   * On peut se poser la question de savoir si le fichier est
   * accessible avec l'appel systeme access();
   * Si oui, envoie l'entete OK 200 puis le contenu du fichier
   * Si non, envoie l'entete ERROR 403
   */
   //F_OK means the file is exist
   if(access(fichier,R_OK)==-1){
        printf("File is not accessible.\n");
        write(soc,ERROR403,strlen(ERROR403));
        return false;
   }else{
        write(soc,OK200,strlen(OK200));
        sprintf(buf, "<html><title>File %s</title><h1>Contenue:%s</h1><body><pre>", fichier,fichier);
        write(soc, buf, strlen(buf));

        fd = open(fichier,O_RDONLY);
        if(fd==-1){
            // duo yu de daima
            printf("can't open file%s",fichier);
            write(soc,ERROR403,strlen(ERROR403));
            return false;
        }
        while(1){
            r=read(fd,buf,BUFSIZE);
            if(r==0)
                //finish of file
                break;
            if(r==-1){
                perror("Read File is interrupted");

            }
            write(soc,buf,r);
        }

        sprintf(buf,"</pre></body></html>");
        write(soc, buf, strlen(buf));
        //sprintf(buf, "<html><title>File %s</title><h1>Contenue</h1><p>%s</p><body>", fichier,"There is nothing");
        //write(soc, buf, strlen(buf));
        return true;
   }



}


/* envoiRep()
 * Arguments: le nom du repertoire, la socket
 * valeur renvoyee: true si OK, false si erreur
 */
bool envoiRep(char *rep, int soc) {
  DIR *dp;
  struct dirent *pdi;
  char buf[1024], nom[1024];

  dp = opendir(rep);
  if (dp == NULL)
    return false;

  write(soc, OK200, strlen(OK200));
  sprintf(buf, "<html><title>Repertoire %s</title><body>", rep);
  write(soc, buf, strlen(buf));

  while ((pdi = readdir(dp)) != NULL) {
    /* A completer
     * Le nom de chaque element contenu dans le repertoire est retrouvable a
     * l'adresse pdi->d_name. Faites man readdir pour vous en convaincre.
     * Dans un premier temps, on se contentera de la liste simple.
     * Dans une petite amelioration on poura prefixer chaque element avec
     * l'icone folder ou generic en fonction du type du fichier.
     * (Tester le nom de l'element avec le chemin complet.) */

     strcpy(nom,pdi->d_name);
     sprintf(buf,"<p>");
     write(soc,buf,strlen(buf));

     write(soc,nom,strlen(nom));
     sprintf(buf,"</p>");
     write(soc,buf,strlen(buf));
  }
  write(soc, "\n\r", 2);
  return true;
}


void communication(int soc, struct sockaddr *from, socklen_t fromlen) {
  int s;
  char buf[BUFSIZE];
  ssize_t nread;
  char host[NI_MAXHOST];
  bool result;
  char *pf;
  enum op { GET, PUT } operation;

  /* Eventuellement, inserer ici le code pour la reconnaissance de la
   * machine appelante */
  s = getnameinfo(from,fromlen,host,NI_MAXHOST,NULL,0,NI_NUMERICHOST);
  if(s!=0){
    perror("cant not getnameinfo\n");
    exit(EXIT_FAILURE);
  }
    printf("a client connect -host:%s!!\n",host);
  /* Reconnaissance de la requete */
  nread = read(soc, buf, BUFSIZE);
    printf("recu:%s\n",buf);
  if (nread > 0) {
    if (strncmp(buf, "GET", 3) == 0)
      operation = GET;
  } else {
    perror("Erreur lecture socket");
    return;
  }

  switch (operation) {
    case GET:
      pf = strtok(buf + 4, " ");
      /* ===little example for strtok()====
      printf("=========\n");
      while(pf){
        printf("%s\n",pf);
        pf = strtok(NULL," ");
      }
        exit(EXIT_SUCCESS);
      */
      /* redireciton????
      if(strcmp(pf,"/")==0){
         envoiRep(".",soc);
      }
      */


      /* On pointe alors sur le / de "GET /xxx HTTP...
       * strtok() rend l'adresse du premier caractere
       * apres l'espace et termine le mot par '\0'
       */
      pf++; /* pour pointer apres le slash */
      /* pf pointe sur le nom du fichier suivant le / de la requete.
       * Si la requete etait "GET /index.html ...", alors pf pointe sur
       * le "i" de "index.html"
       */

       //index
       if(strcmp("index.html",pf)==0){
            printf("he wants a index.html.\n");
            envoiRep(".",soc);
       }else{
           printf("he wants %s\n",pf);

      /* si le fichier est un fichier ordinaire, on l'envoie avec la fonction
       * envoiFichier().

       * Si c'est un repertoire, on envoie son listing avec la fonction
       * envoiRep().

       * Vous pouvez utiliser la fonction typeFichier() ci-dessous pour tester
       * le type du fichier.
       */

          /************ A completer ici**********/
          enum TypeFichier typef = typeFichier(pf);
          switch(typef){
            case ERREUR:
                //perror("error to know stat of the fichier\n");
                printf("File not exits\n");
                write(soc,ERROR404,strlen(ERROR404));
                break;
            case NORMAL:
                //file
                printf("This is normal file\n");
                //if true wait to send another one
                envoiFichier(pf,soc);
                break;
            case REPERTOIRE:
                //directory
                printf("This is normal directory\n");
                envoiRep(pf,soc);
                break;

        }

       }

  }

  close(soc);
}


int main(int argc, char **argv) {
  int sfd, s, ns,r;
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  struct sockaddr_storage from;
  socklen_t fromlen;

  if (argc != 2) {
    printf("Usage: %s  port_serveur\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Inserer ici le code d'un serveur TCP concurent */

  /* Construction de l'adresse locale (pour bind) */
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  //hints.ai_flags |= AI_V4MAPPED|AI_ALL;
  hints.ai_protocol = 0;
  //getaddrinfo
  memset(&result,0,sizeof(struct addrinfo));
  s= getaddrinfo(NULL,argv[1],&hints,&result);

  if(s!=0){
    //perror("Cant getaddrinfo/n");
    fprintf(stderr,"getaddrinfo %s\n",gai_strerror(s));
    exit(EXIT_FAILURE);
  }

  //create socket
  for(rp=result;rp!=NULL;rp = rp->ai_next){

    sfd = socket(AF_INET,SOCK_STREAM,0);

    //bind
    r = bind(sfd,rp->ai_addr,rp->ai_addrlen);
    //case success
    if(r==0)
        break;
  }
    if(rp==NULL){
        perror("can not bind a port\n");
        exit(EXIT_FAILURE);
    }
    freeaddrinfo(result);
    listen(sfd,BACKLOG);


    for(;;){

        ns = accept(sfd,(struct sockaddr*)&from,&fromlen);
        if(ns==-1){
            perror("accept error\n");
            exit(EXIT_FAILURE);
        }

        printf("get a conn!\n");

        //for fun
        /*
        char buf[BUFSIZE];
        sprintf(buf,"<html><title>WelCome</title>bbb</html>");

        write(ns,buf,strlen(buf));
        */
        communication(ns,(struct sockaddr *)&from,fromlen);


    }
    exit(EXIT_SUCCESS);







}
