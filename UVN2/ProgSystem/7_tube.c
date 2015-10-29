/*
 * Author: WANG Jue
*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#define TABSIZE 512
int main(){
    char tab[TABSIZE],*s;
    s = fgets(tab, TABSIZE, stdin);

    int pipefd[2];
    char buf;
    pid_t cpid;
    //get input from screen
    int length_s = strlen(s);
    s[length_s - 1] = '\0';
    printf("input:%s,length:%d\n",s,(int)strlen(s));
    printf("==========================================\n");
    //create pipe
    if(pipe(pipefd)==-1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    switch(cpid){
        case -1:
            perror("can't fork");
            exit(EXIT_FAILURE);
            break;
        case 0:
            //child
            printf("I'm child\n");
            //close write end
            close(pipefd[1]);
            while(read(pipefd[0],&buf,1)>0){
                //write(STDOUT_FILENO,"c:",2);
                write(STDOUT_FILENO,&buf,1);
                }
            write(STDOUT_FILENO,"\n",1);
            close(pipefd[0]);
            exit(EXIT_SUCCESS);
            break;

        default:
            //parent
            printf("I'm parent\n");
            //sleep(2);
            //close read end
            close(pipefd[0]);
            write(pipefd[1],s,strlen(s));
            close(pipefd[1]);
            wait(NULL);
            exit(EXIT_SUCCESS);
    }
    return 0;
}
