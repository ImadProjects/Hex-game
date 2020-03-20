#!/bin/bash

#compile les fichiers en entrée en un executable avec les flags nécéssaires pour la gsl
gcc -Wall -g -c $1.c $2.c $3.c -lgsl -lgslcblas -lm -lgcov

gcc -Wall -g $1.o $2.o $3.o -lgsl -lgslcblas -lm -lgcov
