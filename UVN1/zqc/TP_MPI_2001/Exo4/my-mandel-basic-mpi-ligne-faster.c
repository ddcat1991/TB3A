#include <stdio.h>
#include "mpi.h"

#if defined(__GNUC__) && (__GNUC__ >= 3)
#define ATTRIBUTE(x) __attribute__(x)
#else
#define ATTRIBUTE(x) /**/
#endif

#define MIN(_x, _y) ((_x) > (_y) ? (_y) : (_x))
#define ABS(_x) ((_x) >= 0 ? (_x) : -(_x))


/* N'hesitez pas a changer MAXX .*/
#define MAXX  500
#define MAXY (MAXX * 3 / 4)

#define NX (2 * MAXX + 1)
#define NY (2 * MAXY + 1)

#define NBITER 550
#define DATATAG 150

static int mandel(double, double);

int dump_ppm(const char *, int[NX][NY]);
int cases[NX][NY];


int main(int argc, char *argv[])
{
  MPI_Status status;
  int i,j, num, rank, size, nbslaves;
  char inputstr [100],outstr [100];

  /* Start up MPI */

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  nbslaves = size -1;

  printf("nbslave %d \n",size);

  if (rank == 0) {

    int res[NY];
    int k;
    int count_fini;
    int *curren_line = (int *)malloc(nbslaves*sizeof(int));
    //init current_ligne
    int m;
    for(m=0;m<nbslaves;m++){
        curren_line[m]=m;
    }



    /* Begin User Program  - the master */

   /*
   for(i = -MAXX; i <= MAXX; i+=nbslaves) {
      for(k=1;k<=nbslaves;k++){
            if(i+k-1>=MAXX)
                break;
        MPI_Recv(&res, NY, MPI_INT, k, DATATAG, MPI_COMM_WORLD, &status);
        memcpy(cases[i+MAXX+k-1], res, NY*sizeof(int));

      }
    }*/
    count_fini=0;
    while(1){
        MPI_Recv(&res, NY, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        //distinguish type of the message


        if(status.MPI_TAG==DATATAG+1){
        //finish
            printf("souce:%d\n",status.MPI_SOURCE);
            printf("tag:%d\n",status.MPI_TAG);
            count_fini++;
            if(count_fini==nbslaves)
                break;

        }
        if(status.MPI_TAG==DATATAG){
            //status.MPI_SOURCE
            memcpy(cases[curren_line[status.MPI_SOURCE-1]], res, NY*sizeof(int));
            curren_line[status.MPI_SOURCE-1]+=nbslaves;
        }
    }

    dump_ppm("mandel-ligne.ppm", cases);
    printf("Fini.\n");
  }

  else {

    /* On est l'un des fils */
    double x, y;
    int i, j, res, rc;
    int res_Y[NY];
    for(i = -MAXX+rank-1; i <= MAXX; i=i+nbslaves) {

      for(j = -MAXY; j <= MAXY; j++) {
            x = 2 * i / (double)MAXX;
            y = 1.5 * j / (double)MAXY;
            res_Y[j+MAXY] = mandel(x, y);

      }
         MPI_Send(&res_Y, NY , MPI_INT, 0, DATATAG, MPI_COMM_WORLD);
    }
    //indicate this  is the last message of the slave
    res=1;
    MPI_Send(&res_Y, NY , MPI_INT, 0, DATATAG+1, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}



/* function to compute a point - the number of iterations
   plays a central role here */

int
mandel(double cx, double cy)
{
  int i;
  double zx, zy;
  zx = 0.0; zy = 0.0;
  for(i = 0; i < NBITER; i++) {
    double zxx = zx, zyy = zy;
    zx = zxx * zxx - zyy * zyy + cx;
    zy = 2 * zxx * zyy + cy;
    if(zx * zx + zy * zy > 4.0)
      return i;
  }
  return -1;
}

/* the image commputer can be transformed in a ppm file so
   to be seen with xv */

int
dump_ppm(const char *filename, int valeurs[NX][NY])
{
  FILE *f;
  int i, j, rc;

  f = fopen(filename, "w");
  if(f == NULL) { perror("fopen"); exit(1); }
  fprintf(f, "P6\n");
  fprintf(f, "%d %d\n", NX, NY);
  fprintf(f, "%d\n", 255);
  for(j = NY - 1; j >= 0; j--) {
    for(i = 0; i < NX; i++) {
      unsigned char pixel[3];
      if(valeurs[i][j] < 0) {
	pixel[0] = pixel[1] = pixel[2] = 0;
      } else {
	unsigned char val = MIN(valeurs[i][j] * 12, 255);
	pixel[0] = val;
	pixel[1] = 0;
	pixel[2] = 255 - val;
      }
      rc = fwrite(pixel, 1, 3, f);
      if(rc < 0) { perror("fwrite"); exit(1); }
    }
  }
  fclose(f);
  return 0;
}

