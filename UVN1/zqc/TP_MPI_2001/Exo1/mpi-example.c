#include <stdio.h>
#include <string.h>
#include "mpi.h"


int main(int argc, char *argv[])
{
  MPI_Status status;
  int i,j, num, rank, size, tag,   nbslaves;
  char inputstr[100], outstr[100];

  /* Start up MPI */

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
 
  /* Arbitrarily choose 201 to be our tag.  */

  tag = 201;

  nbslaves = size -1;

  if (rank == 0) {

    /* Begin User Program  - the master */
    printf("Number of arguments in the command line %d  \n", argc);

    printf("I'll convert  %s using %d slaves \n", argv[1], nbslaves);

    /* send data to slave tasks */
    for( i=1 ; i < nbslaves+1 ; i++ ) {

      /* prepare the data to be sent 
	 There should be a better way with C string functions ....  */

      if (i == nbslaves) {

	for (j=(strlen(argv[1]) / nbslaves) * (i-1); j <= strlen(argv[1]); j++) {
	  outstr[j - ((strlen(argv[1]) / nbslaves) * (i-1))] = argv[1][j];
	}
	outstr[j+1] = '\0';

      }
      else {
        for (j=(strlen(argv[1]) / nbslaves) * (i-1);
             j <= ((strlen(argv[1])  / nbslaves) * i) -1; j++) {
	  outstr[j - ((strlen(argv[1]) / nbslaves) * (i-1))] = argv[1][j];
	}
	outstr[j+1] = '\0';
      }


      printf("Process sending %s to %d\n", outstr, i);
      MPI_Send(outstr, strlen(outstr), MPI_CHAR, i, tag, MPI_COMM_WORLD); 
    }
    for( i=1 ; i < nbslaves+1 ; i++ ) {
      MPI_Recv(&inputstr, 100, MPI_CHAR, i, tag+1, MPI_COMM_WORLD, &status);
      printf("Process receiving %s from node %d \n", inputstr, i);
    }
  }

  else {
    /* Slave */

    MPI_Recv(&inputstr, 100, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);

    /* Do upper-case translation with data */
    for (i=0; inputstr [i] != '\0' && (i < 100); i++) {
      /*
       * The function toupper() converts ASCII characters to upper case.
      */
      outstr[i] = toupper(inputstr[i]);
    }
    outstr[i+1] = '\0';

    MPI_Send(outstr, strlen(outstr)+1 , MPI_CHAR, 0, tag+1, MPI_COMM_WORLD); 
  }

  MPI_Finalize();
  return 0;
}
