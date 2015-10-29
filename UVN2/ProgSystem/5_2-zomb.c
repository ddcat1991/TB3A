/*
 * Auteur(s):
 */

#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
sig_atomic_t child_exit_status;

void travail() {
  /* Je travaille tres intensement !    */
  /* Ne cherchez pas a comprendre ;-) */
  /* Il n'y a rien a modifier ici     */
  for (;;) {
    printf("%s", random() > RAND_MAX>>1 ? "." : "\b \b");
    fflush(stdout);
    usleep(100000);
  }
}
void travail() __attribute__((noreturn));
/* Petit raffinement pour le compilateur: cette fonction ne termine pas */

void clean_zommbies(){
    int status;
    wait(&status);
    child_exit_status=status;
}

int main() {
  int pid, longueur;
  char tab[256];

  int r;
  signal(SIGCLD,clean_zommbies);
  pid = fork();

  if (pid != 0) {	/* Processus Pere */
    travail();
  } else {		/* Processus Fils */
    sleep(5);
    printf("Ahrg!!! je suis le fils et je meurs\n");
    exit(EXIT_SUCCESS);
  }
}

