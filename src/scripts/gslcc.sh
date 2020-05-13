#!/bin/bash

gcc -Wall -g alltests.c graph.c graph_aux.c pile.c resistance.c test_resistances.c test_graph.c -lgsl -lgslcblas -lm -lgcov

#gcc -Wall -g $1.o $2.o $3.o -lgsl -lgslcblas -lm -lgcov
