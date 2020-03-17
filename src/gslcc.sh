#!/bin/bash

#compile les fichiers en entrée en un executable avec les flags nécéssaires pour la gsl
gcc -c $1.c $2.c -lgsl -lgslcblas -lm

gcc $1.o $2.o -lgsl -lgslcblas -lm
