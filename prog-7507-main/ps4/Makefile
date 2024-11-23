CC=gcc
CFLAGS=-std=c11 -Werror -Wall -g
LDLIBS=-lm
SOURCES= bmp.c main.c transformations.c
OUTPUT=all

# targets
all: $(OUTPUT)

$(OUTPUT): bmp.o main.o transformations.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	$(CC) $(CFLAGS) bmp.o main.o transformations.o $(LDLIBS) -o $(OUTPUT)

bmp.o: bmp.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

transformations.o: transformations.c
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@


clean: 
	rm -rf $(OUTPUT) *.o tests
