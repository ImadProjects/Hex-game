CFLAGS =  -std=c99 -c -ggdb
COMP=gcc
GSL_PATH?=/usr/local/gsl


build: server alltests players

server: server.o graph.o
	$(COMP) -I ${GSL_PATH}/include --coverage -g -O0 -L ${GSL_PATH}/lib -o install/server graph.o server.o -lgsl -lgslcblas -lm


alltests: server.o graph.o
	$(COMP) -I ${GSL_PATH}/include   -o install/alltests graph.o server.o -lgsl -lgslcblas -lm
	$(COMP) -I ${GSL_PATH}/include   --coverage  src/graph.c src/server.c  -lgsl -lgslcblas -lm

server.o: src/server.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include   -o server.o src/server.c

graph.o: src/graph.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include   -o graph.o src/graph.c
players: player1.so player2.so


player1.so: 
	$(COMP) -I ${GSL_PATH}/include  -fPIC -c src/player.c -o player1_dyn.o 
	$(COMP)  -I ${GSL_PATH}/include  -shared -o install/player1.so player1_dyn.o

player2.so: 
	gcc -I ${GSL_PATH}/include  -fPIC -c src/player.c -o player2_dyn.o 
	gcc -I ${GSL_PATH}/include  -shared -o install/player2.so player2_dyn.o




test:

install: server players

clean:	
	rm -rf *.o server 
	rm -f install/server
	rm -f install/alltests
	rm  -f *gcov
	rm -f *gcno
	rm -f *gcda
	rm -f a.out