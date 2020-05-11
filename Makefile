GSL_PATH?=/opt/gsl-2.6/lib
CFLAGS=-Wall -Wextra -std=c99 -I $(GSL_PATH)/include

LDFLAGS=-L $(GSL_PATH)/lib -ldl -lgsl -lgslcblas -lm

all: build 

build: server test

test:  alltests.o test_graph.o test_resistances.o alltests_resistance.o alltests_graph.o 
		$(CC) $(CFLAGS) -rdynamic --coverage -g -O0   alltests.o test_resistances.o resistance.o test_graph.o graph.o pile.o graph_aux.o -o install/alltests $(LDFLAGS)
		$(CC) $(CFLAGS) -rdynamic --coverage -g -O0   alltests_resistance.o test_resistances.o resistance.o  graph.o pile.o graph_aux.o -o install/alltests_resistance $(LDFLAGS)
		$(CC) $(CFLAGS) -rdynamic --coverage -g -O0   alltests_graph.o test_graph.o  graph.o pile.o graph_aux.o -o install/alltests_graph $(LDFLAGS)

install: server players

players: player1.so player2.so player3.so player4.so 

clean:	
	rm -rf *.o *.gcda *.gcno *.gcda server 
	rm -f install/server install/test*
	rm -f install/alltests install/*.so 
	rm  -f *gcov
	rm -f *gcno
	rm -f *gcda
	rm -f a.out
	rm -rf install/*.dSYM *.dSYM

pile.o:src/pile.c
	$(CC) $(CFLAGS) -c src/pile.c
resistance.o:src/resistance.c
	$(CC) $(CFLAGS) -c src/resistance.c

graph.o:src/graph.c
	$(CC) $(CFLAGS) -c src/graph.c

graph_aux.o:src/graph_aux.c
	$(CC) $(CFLAGS) -c src/graph_aux.c


player1.o: src/player1.c 
	$(CC) $(CFLAGS) -c -fPIC src/player1.c

player-load.o: src/player-load.c src/player-load.h
	$(CC) $(CFLAGS) -c -g src/player-load.c

server.o: src/server.c 
	$(CC) $(CFLAGS) -c src/server.c

player1.so: player1.o pile.o graph.o graph_aux.o
	$(CC) $(CFLAGS) -shared player1.o pile.o graph.o graph_aux.o -o install/vrandom.so $(LDFLAGS)

player2.so:
	cc -std=c99  -fPIC -g -I${GSL_PATH}/include -shared src/graph_aux.c src/player2.c src/graph.c src/pile.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/bloker.so

player3.so: 
	cc -std=c99  -fPIC -g -I${GSL_PATH}/include -shared src/graph_aux.c src/player_resistances.c src/graph.c src/pile.c src/resistance.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/resistance.so

player4.so:
	cc -std=c99  -fPIC -g -I ${GSL_PATH}/include -shared  src/path.c src/pile.c src/graph.c src/graph_aux.c src/dynamic_array.c src/graph_minimax.c src/minimax.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/minimax.so


server: server.o pile.o graph.o graph_aux.o
	$(CC) $(CFLAGS) -rdynamic --coverage -g -O0 -o install/server server.o pile.o graph.o graph_aux.o $(LDFLAGS)



test_graph.o: src/test_graph.c 
	$(CC) $(CFLAGS) -c src/test_graph.c

test_resistances.o: src/test_resistances.c resistance.o
	$(CC) $(CFLAGS) -c src/test_resistances.c


alltests.o: src/alltests.c 
	$(CC) $(CFLAGS) -c -rdynamic --coverage -g -O0   src/alltests.c

alltests_resistance.o: src/alltests_resistance.c 
	$(CC) $(CFLAGS) -c -rdynamic --coverage -g -O0   src/alltests_resistance.c

alltests_graph.o: src/alltests_graph.c 
	$(CC) $(CFLAGS) -c -rdynamic --coverage -g -O0   src/alltests_graph.c

