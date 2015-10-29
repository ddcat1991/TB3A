#!/bin/sh
rm my-mandel-basic-mpi-block.o
rm my-mandel-basic-mpi-block
echo "compli begin"
mpicc -c my-mandel-basic-mpi-block.c
mpicc my-mandel-basic-mpi-block.o -o my-mandel-basic-mpi-block -lm
echo "compli fin"
