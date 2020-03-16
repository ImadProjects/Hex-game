CFLAGS = -Wall -Wextra -std=c99 -c -ggdb
COMP=gcc
GSL_PATH?=/net/ens/renault/save/gsl-2.6/install make


build: server alltests

server: server.o
	$(COMP) -o server server.o
server.o: src/server.c
		$(COMP) $(CFLAGS) -o server.o src/server.c

alltests:

test:

install: server
	cp server install/

clean:	
	rm -rf *.o server 