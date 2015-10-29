/*
 * Auteur(s):
 *  WANG Jue
 * Cet programme refait ce que fait la commande "ls". Il donne des
 * informnations sur les caracteristiques de fichiers dont le nom est passe
 * en parametre.
 *
 * Utilisation de la primitive stat(2) et de la fonction getpwuid(3).
 */
#include<stdio.h>
#include <stdlib.h>
int main(int argc,char **argv){

    if(argv[1]==NULL){
        printf("the number of input parameter is not right\n");
        return 0;
    }else{
        char *value;
        value = getenv(argv[1]);
        printf("%s=%s\n",argv[1],value);
    }
   return 0;
}
