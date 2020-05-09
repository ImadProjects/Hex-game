CFLAGS =  -std=c99 -c -ggdb 
COMP=cc
GSL_PATH?=/usr/local/gsl


build: precommit server test players

precommit: 
	chmod +x ./src/scripts/install-hooks.bash
	./src/scripts/install-hooks.bash

server: server.o graph.o pile.o graph_aux.o
	$(COMP) -std=c99 -I ${GSL_PATH}/include -rdynamic --coverage -g -O0 -L ${GSL_PATH}/lib -o install/server graph.o pile.o graph_aux.o server.o -lgsl -lgslcblas -lm -ldl



test: test_graph.o graph.o pile.o graph_aux.o resistance.o alltests.o test_resistances.o
	$(COMP) -std=c99 -g -I ${GSL_PATH}/include -L ${GSL_PATH}/lib   -o install/alltests graph.o test_graph.o pile.o graph_aux.o resistance.o alltests.o test_resistances.o -lgsl -lgslcblas -lm -ldl
	$(COMP)  -std=c99 -g -I ${GSL_PATH}/include  -L ${GSL_PATH}/lib  --coverage  src/graph.c src/test_graph.c src/pile.c src/graph_aux.c src/resistance.c src/alltests.c src/test_resistances.c -lgsl -lgslcblas -lm -ldl



alltests: alltests.o graph.o pile.o graph_aux.o resistance.o test_graph.o test_resistances.o
	$(COMP) -std=c99  -I ${GSL_PATH}/include -L ${GSL_PATH}/lib   -o install/alltests graph.o alltests.o pile.o graph_aux.o test_graph.o test_resistances.o resistance.o -lgsl -lgslcblas -lm -ldl
	$(COMP)  -std=c99 -I ${GSL_PATH}/include  -L ${GSL_PATH}/lib  --coverage  src/graph.c src/alltests.c pile.o graph_aux.o test_graph.o test_resistances.o  resistance.o -lgsl -lgslcblas -lm -ldl

server.o: src/server.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include   -o server.o src/server.c

graph.o: src/graph.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include  -o graph.o src/graph.c 

path: src/path.c
	$(COMP)  -I ${GSL_PATH}/include  -Wall src/graph.c src/graph_aux.c src/pile.c src/dynamic_array.c src/path.c -lgsl -lgslcblas -lm -ldl

graph_aux.o: src/graph_aux.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include  -o graph_aux.o src/graph_aux.c 

pile.o: src/pile.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include  -o pile.o src/pile.c 

path.o : src/path.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include  -o path.o  src/path.c

graph_minimax.o : src/graph_minimax.c
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include  -o graph_minimax.o 
	
test_graph.o: src/test_graph.c
	$(COMP) $(CFLAGS) -g -I ${GSL_PATH}/include   -o test_graph.o src/test_graph.c


test_resistances.o: src/test_resistances.c
	$(COMP) $(CFLAGS) -g -I ${GSL_PATH}/include   -o test_resistances.o src/test_resistances.c

alltests.o:
	$(COMP) $(CFLAGS) -g -I ${GSL_PATH}/include   -o alltests.o src/alltests.c

resistance.o:
	$(COMP) $(CFLAGS) -I ${GSL_PATH}/include   -o resistance.o src/resistance.c

players: player1.so player2.so minimax.so

player1.so: 
	cc -std=c99  -fPIC -g -I ${GSL_PATH}/include -shared src/graph_aux.c src/player1.c src/graph.c src/pile.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/player1.so

player2.so:
	cc -std=c99  -fPIC -g -I${GSL_PATH}/include -shared src/graph_aux.c src/player2.c src/graph.c src/pile.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/player2.so


player3.so: #segmentation fault
	cc -std=c99  -fPIC -g -I${GSL_PATH}/include -shared src/graph_aux.c src/player_resistances.c src/graph.c src/pile.c src/resistance.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/player_resistance.so

minimax.so:
	cc -std=c99  -fPIC -g -I ${GSL_PATH}/include -shared  src/path.c src/pile.c src/graph.c src/graph_aux.c src/dynamic_array.c src/graph_minimax.c src/Minimax.c -lm -lgsl -lgslcblas -ldl -L${GSL_PATH}/lib -L${GSL_PATH}/lib64 -o install/minimax.so

mem_check:
	#valgrind  --leak-check=full  install/alltests 
	valgrind  --leak-check=full  install/server -m 8

install: server players

show:
	install/server -p 1

clean:	
	rm -rf *.o server 
	rm -f install/server
	rm -f install/alltests install/*.so 
	rm  -f *gcov
	rm -f *gcno
	rm -f *gcda
	rm -f a.out
	rm -rf install/*.dSYM
	
