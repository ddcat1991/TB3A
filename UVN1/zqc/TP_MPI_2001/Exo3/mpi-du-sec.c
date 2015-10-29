#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#include <dirent.h>

int main(int args, char *argv[]){
  MPI_Status status;
  int i,j, num, rank, size, tag, next, from, nbslaves;
  FILE *fp;
  DIR *dirp;
  int notover;
  int  receivedsize;

  int partialsize, totalsize;
  char instr [100], base[256], cmd[256], buf[256];
  struct dirent *direntp;
}
