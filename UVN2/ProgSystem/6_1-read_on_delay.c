/*
 * Auteur(s):
 *  WANG Jue
 * Programme a appeler avec ou sans l'option "true"
 * Lancer "top" auparavant (pour terminer taper "q").
 *
 * Avec l'option "true", le flag O_NONBLOCK est positionne ce qui rend le
 * read non bloquant (il rend -1 et errno est positionne a EAGAIN).  On
 * constate alors que la charge cpu monte...  On n'arrete pas d'appeler
 * read.
 *
 * Sans l'option "true", la charge cpu n'augmente pas, le read est bloquant.
 * Le process s'endort en attendant que des caracteres soient tapes au
 * clavier.
 *
 * On peut aussi lancer ce programme avec ou sans l'option "true" a l'aide
 * de la commande strace : strace read_on_delay [true].
 *
 * Sous Solaris on utilisera truss au lieu de strace
*/

#include <sys/fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

void delete_nonblock(int sigid){

    int flag;
    flag = fcntl(0, F_GETFL, 0);
    if (flag < 0) {
      perror("Fcntl F_GETFL");
      exit(EXIT_FAILURE);
    }
    //lags &= ~O_NONBLOCK
    flag = fcntl(0,F_SETFL,flag&~O_NONBLOCK);
    if (flag < 0) {
      perror("Fcntl F_SETFL");
      exit(EXIT_FAILURE);
    }
    wait(NULL);
}

void add_nonblock(int sigid){
    int flag;
    flag = fcntl(0, F_GETFL, 0);
    if (flag < 0) {
      perror("Fcntl F_GETFL");
      exit(EXIT_FAILURE);
    }
    flag = fcntl(0,F_SETFL,flag|O_NONBLOCK);
    if (flag < 0) {
      perror("Fcntl F_SETFL");
      exit(EXIT_FAILURE);
    }
    wait(NULL);
}

int main(int argc, char **argv) {
  int flag, r;
  char buf[10]="";

  signal(SIGINT,delete_nonblock);
  signal(SIGQUIT,add_nonblock);
  if ((argc > 1) && (strcmp(argv[1], "true") == 0)) {
    flag = fcntl(0, F_GETFL, 0);
    printf("flag:%d",flag);
    if (flag < 0) {
      perror("Fcntl F_GETFL");
      exit(EXIT_FAILURE);
    }
    //printf("old->flag=%d",flag);
    /* positionner maintenant le flag avec O_NONBLOCK */
    flag = fcntl(0,F_SETFL, flag|O_NONBLOCK);

    if (flag < 0) {
      perror("Fcntl F_SETFL");
      exit(EXIT_FAILURE);
    }
  }

  for (;;) {
    r = read(0, buf, 10);
    if ((r > 0) && (strncmp(buf, "quit", 4) == 0)) {
      exit(EXIT_SUCCESS);
    }
  }

}
