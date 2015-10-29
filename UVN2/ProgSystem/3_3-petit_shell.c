/*
 * Auteur(s):
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define TABSIZE 512

int main() {
  int pid, longueur;
  char tab[TABSIZE], *s;
  char dest[25];

  for (;;) {
    fputs("petit_shell...> ", stdout);	/* Affichage d'un prompt */
    s = fgets(tab, TABSIZE, stdin);

    if (s == NULL) {
      fprintf(stderr, "Fin du Shell\n");
      exit(EXIT_SUCCESS);
    }

    longueur = strlen(s);
    tab[longueur - 1] = '\0';

    pid = fork();
    switch(pid){
        //error
        case -1:
            printf("ERROR:===can't create a child process=====\n");
            break;
        //child
        case 0:
            printf("I'm child! parent->uid=%d\n",getppid());
            strcpy(dest, "");
            strcat(dest,"/bin/");
            strcat(dest,s);
            printf("your commend is:%s\n",dest);
            int erroecode = execlp(dest,s,NULL);
            printf("ERROR to execute bash:%d\n",erroecode);
            printf("child is continue, because the error with execute\n");
            break;
        //parent
        default:
            wait(NULL);
            printf("I'm parent! puid=%d\n",pid);


    }
    //printf("pid=%d",pid);
    /* Actions:
     *
     * Si dans pere alors
     *   wait(NULL);
     * sinon alors
     *   execution de la commande recuperee dans tab;
     *   message d'erreur: fprintf(stderr, "Erreur dans le exec\n")
     * fin si
     */

  }
}


