/*
 * Auteur(s): WANG Jue
 */

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void (*sig_avant)(int);		/* pour la question 4.3 */

int state =0;

void sigint_m1(int n){
    printf("This is message 1\n");
}

void sigint_m2(int n){
    printf("This is message 2\n");
}
//change state
void sigquit(int n){
    if(state){
        signal(SIGINT,sigint_m2);
        state=0;
    }else{
        signal(SIGINT,sigint_m1);
        state=1;
    }


}

void travail() {
  /* Je travaille tres intensement !    */
  /* Ne cherchez pas a comprendre ;-) */
  /* Il n'y a rien a modifier ici     */
  const char msg[] = "-\\|/";
  const int sz = strlen(msg);
  int i = 0;

  for (;;) {
    write(STDOUT_FILENO, "\r", 1);
    usleep(100000);
    write(STDOUT_FILENO, " => ", 4);
    write(STDOUT_FILENO, &msg[i++], 1);
    if (i == sz) i = 0;
  }
}
void travail() __attribute__((noreturn));
/* Petit raffinement pour le compilateur: cette fonction ne termine pas */


int main() {
  printf("PID: %d\n", getpid());
  signal(SIGINT,sigint_m1);
  signal(SIGQUIT,sigquit);

  /* ? ? ? ? ? ? */

  travail();
}

