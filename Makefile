CFLAGS = -Wall -Wextra -std=c99 -c -ggdb
COMP=gcc
GSL_PATH?=


build: server alltests players

server: server.o graph.o
	$(COMP) -I${GSL_PATH} -o install/server graph.o server.o -lgsl -lgslcblas -lm

alltests: server.o graph.o
	$(COMP) -I${GSL_PATH} -o install/alltests graph.o server.o -lgsl -lgslcblas -lm
	$(COMP) -I${GSL_PATH} --coverage  src/graph.c src/server.c  -lgsl -lgslcblas -lm

server.o: src/server.c
	$(COMP) $(CFLAGS) -o server.o src/server.c

graph.o: src/graph.c
	$(COMP) $(CFLAGS) -I${GSL_PATH} -o graph.o src/graph.c
players: player1.so player2.so


player1.so: 
	$(COMP) -fPIC -c src/player.c -o player1_dyn.o 
	$(COMP)  -shared -o install/player1.so player1_dyn.o

player2.so: 
	gcc -fPIC -c src/player.c -o player2_dyn.o 
	gcc -shared -o install/player2.so player2_dyn.o




test:

install: server players

clean:	
	rm -rf *.o server 
	rm -f install/*.so 
	rm -f install/server
	rm -f install/alltests
	rm  -f *gcov
	rm -f *gcno
	rm -f *gcda
	rm -f a.out