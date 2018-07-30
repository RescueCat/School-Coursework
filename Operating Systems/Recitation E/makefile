CC = cc
COPS = -D_GNU_SOURCE
LIBTHREAD = -lpthread

all: getsizeschild getsizesthread 

getsizeschild: getsizeschild.c
	$(CC) $(COPS) -o getsizeschild getsizeschild.c

getsizesthread: getsizesthread.c
	$(CC) $(COPS) -o getsizesthread getsizesthread.c $(LIBTHREAD)

runchild:
	getsizeschild getsizeschild.c getsizesthread.c

runthread:
	getsizesthread getsizeschild.c getsizesthread.c

clean:
	rm -rf core *.o getsizesthread getsizeschild
