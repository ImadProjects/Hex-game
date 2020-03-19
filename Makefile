CFLAGS =  -std=c99 -c -ggdb
COMP=gcc
GSL_PATH?=/usr/local/gsl


build: server alltests players

server: server.o graph.o
	$(COMP) -std=c99 -I ${GSL_PATH}/include --coverage -g -O0 -L ${GSL_PATH}/lib -o install/server graph.o server.o -lgsl -lgslcblas -lm


alltests: server.o graph.o
	$(COMP) -std=c99  -I ${GSL_PATH}/include -L ${GSL_PATH}/lib   -o install/alltests graph.o server.o -lgsl -lgslcblas -lm
	$(COMP)  -std=c99 -I ${GSL_PATH}/include  -L ${GSL_PATH}/lib  --coverage  src/graph.c src/server.c  -lgsl -lgslcblas -lm

server.o: src/server.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include   -o server.o src/server.c

graph.o: src/graph.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include  -o graph.o src/graph.c 
players: player1.so player2.so



player1.so: 
	$(COMP) -I ${GSL_PATH}/include  -fPIC -c  src/player.c  -o player1_dyn.o 
	$(COMP)  -I ${GSL_PATH}/include -L ${GSL_PATH}/lib  -shared graph.o player1_dyn.o  -o install/player1.so -lgsl -lgslcblas -lm

player2.so: 
	gcc -std=c99 -I ${GSL_PATH}/include  -fPIC -c  src/player.c -o player2_dyn.o 
	gcc -std=c99 -I ${GSL_PATH}/include -L ${GSL_PATH}/lib  -shared graph.o player2_dyn.o -o install/player2.so  -lgsl -lgslcblas -lm




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
	clear