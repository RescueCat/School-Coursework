CC = cc
COPS =
LINT = lint
LOPS = -x -u
LIBTHREAD = -lpthread
POSIXPTHREAD = -D_POSIX_PTHREAD_SEMANTICS
RTLIB = -lrt

all: countertest

countertest: countertest.c counter.c
	$(CC) $(COPS) -o countertest countertest.c counter.c $(LIBTHREAD)

clean:
	rm -f *.o core countertest
