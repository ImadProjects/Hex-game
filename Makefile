CFLAGS =  -std=c99 -c -ggdb 
COMP=cc
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
	cc -std=c99  -fPIC -g -I/opt/gsl-2.6/include -shared src/player.c src/graph.c -lm -lgsl -lgslcblas -ldl -L/opt/gsl-2.6/lib -L/opt/gsl-2.6/lib64 -o install/player1.so

player2.so:
	cc -std=c99  -fPIC -g -I/opt/gsl-2.6/include -shared src/player.c src/graph.c -lm -lgsl -lgslcblas -ldl -L/opt/gsl-2.6/lib -L/opt/gsl-2.6/lib64 -o install/player2.so



test:

install: server players

clean:	
	rm -rf *.o server 
	rm -f install/server
	rm -f install/alltests install/*.so 
	rm  -f *gcov
	rm -f *gcno
	rm -f *gcda
	rm -f a.out
	rm -rf install/*.dSYM
	clear