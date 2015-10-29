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
    int pipefd[2];
    char buf;
    pid_t cpid;

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
            dup2(pipefd[0],STDIN_FILENO);

            while(read(STDIN_FILENO,&buf,1)){

                write(STDOUT_FILENO,&buf,1);

            }
            break;

        default:
            //parent
            printf("I'm parent\n");
            //sleep(2);
            //close read end
            close(pipefd[0]);
            dup2(pipefd[1],STDOUT_FILENO);
            while(read(STDIN_FILENO,&buf,1)){
                write(STDOUT_FILENO,&buf,1);
            }

    }
    if(cpid==0){
    //close child
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }

    if(cpid>0){
    //close parent
        close(pipefd[1]);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
