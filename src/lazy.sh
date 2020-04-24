#!/bin/bash

rm *.o

gcc -c -g graph.c test_resistances.c resistance.c pile.c graph_aux.c -lgsl -lgslcblas -lm -lgcov

gcc -g graph.o test_resistances.o resistance.o pile.o graph_aux.o -lgsl -lgslcblas -lm -lgcov

./a.out
