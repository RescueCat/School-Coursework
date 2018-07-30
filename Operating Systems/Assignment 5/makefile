CC = cc
COPS =-D_GNU_SOURCE
LINT = lint
LOPS = -x -u
NETLIBS = -lnsl
LIBTHREAD = -lpthread

all: client server

server: server.c restart.c uici.c uiciname.c
	$(CC) $(COPS) -o server server.c restart.c uici.c uiciname.c $(NETLIBS) $(LIBTHREAD)

client: client.c restart.c uici.c uiciname.c
	$(CC) $(COPS) -o client client.c restart.c uici.c uiciname.c $(NETLIBS)

clean:
	rm -f *.o serverp client


