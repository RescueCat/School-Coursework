CFLAGS = gcc -g
OBJ = cs3743p2Driver.o cs3743p2.o 

# Automatic substitution using suffix rules to
# make .o files from either .c or .cpp files
%.o: %.c
	${CFLAGS} -c $< 

%.o: %.cpp
	${CFLAGS} -c $<

# Build p2 based on the required .o files
p2: ${OBJ}
	${CFLAGS} -o p2 ${OBJ}

clean:
	rm ${OBJ}
