#!/bin/sh
echo "compli begin"
mpicc -c my-mandel-basic-mpi.c
mpicc my-mandel-basic-mpi.o -o my-mandel-basic-mpi -lm
echo "compli fin"
