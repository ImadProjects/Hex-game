GSL_PATH?=/opt/gsl-2.6/lib
CFLAGS=-Wall -Wextra -fPIC -std=c99 -fprofile-arcs -ftest-coverage -g   -I $(GSL_PATH)/include
FLAGS=-Wall -Wextra -fPIC -std=c99 -fprofile-arcs -g  -I $(GSL_PATH)/include
LDFLAGS=-L $(GSL_PATH)/lib -ldl -lgsl -lgslcblas -lm

all: build 

build: precommit server  players

precommit: 
	chmod +x ./src/scripts/install-hooks.bash
	./src/scripts/install-hooks.bash

test:  alltests.o test_graph.o test_resistances.o test_minimax.o  path.o graph_minimax.o dynamic_array.o graph.o pile.o graph_aux.o
		$(CC) $(CFLAGS) -rdynamic --coverage -g -O0   alltests.o test_resistances.o test_minimax.o  path.o resistance.o test_graph.o graph_minimax.o dynamic_array.o graph.o pile.o graph_aux.o -o install/alltests $(LDFLAGS)

install: server players

players: player1.so player2.so player3.so player4.so 

clean:	
	rm -rf *.o *.gcda *.gcno *.gcda server 
	rm -f install/server install/test*
	rm -f install/alltest* install/*.so 
	rm  -f *gcov *gcda
	rm -f a.out
	rm -rf install/*.dSYM *.dSYM

pile.o:src/pile.c
	$(CC) $(CFLAGS) -c src/pile.c
	
resistance.o:src/resistance.c
	$(CC) $(CFLAGS) -rdynamic --coverage -g -O0 -c src/resistance.c

graph.o:src/graph.c
	$(CC) $(CFLAGS) -c src/graph.c

graph_aux.o:src/graph_aux.c
	$(CC) $(CFLAGS) -c src/graph_aux.c


player1.o: src/player1.c 
	$(CC) $(FLAGS) -c  src/player1.c


server.o: src/server.c 
	$(CC) $(FLAGS) -g -c src/server.c

player1.so: player1.o pile.o graph.o graph_aux.o
	$(CC) $(FLAGS) -fPIC -shared player1.o pile.o graph.o graph_aux.o -o install/vrandom.so $(LDFLAGS)

player2.so:
	$(CC) $(FLAGS) -fPIC -g -I${GSL_PATH}/include -shared src/graph_aux.c src/player2.c src/graph.c src/pile.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/bloker.so

player3.so: 
	cc -std=c99  -fPIC -g -I${GSL_PATH}/include -shared src/graph_aux.c src/player_resistances.c src/graph.c src/pile.c src/resistance.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/aresistance.so

player4.so:
	cc -std=c99  -fPIC -g -I ${GSL_PATH}/include -shared  src/path.c src/pile.c src/graph.c src/graph_aux.c src/dynamic_array.c src/graph_minimax.c src/minimax.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/minimax.so


server: server.o pile.o graph.o graph_aux.o
	$(CC) $(CFLAGS) -rdynamic --coverage -g -O0 -o install/server server.o pile.o graph.o graph_aux.o $(LDFLAGS)

minimax.o: src/minimax.c 
	$(CC) $(FLAGS) -std=c99 -c src/minimax.c

path.o: src/path.c 
	$(CC) $(CFLAGS) -c src/path.c

test_graph.o: src/tst/test_graph.c 
	$(CC) $(CFLAGS) -c src/tst/test_graph.c
graph_minimax.o: src/graph_minimax.c 
	$(CC) $(CFLAGS) -c src/graph_minimax.c
dynamic_array.o: src/dynamic_array.c 
	$(CC) $(CFLAGS) -c src/dynamic_array.c

test_resistances.o: src/tst/test_resistances.c resistance.o
	$(CC) $(CFLAGS)   -c src/tst/test_resistances.c

test_minimax.o: src/tst/test_minimax.c minimax.o path.o minimax.o graph_minimax.o dynamic_array.o
	$(CC) $(CFLAGS)   -c src/tst/test_minimax.c


alltests.o: src/tst/alltests.c 
	$(CC) $(CFLAGS) -c -rdynamic --coverage -g -O0   src/tst/alltests.c

alltests_resistance.o: src/tst/alltests_resistance.c 
	$(CC) $(CFLAGS) -c -rdynamic --coverage -g -O0   src/tst/alltests_resistance.c

alltests_graph.o: src/tst/alltests_graph.c 
	$(CC) $(CFLAGS) -c -rdynamic --coverage -g -O0   src/tst/alltests_graph.c

