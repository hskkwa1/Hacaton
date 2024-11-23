# Compiler and linker settings
CC = gcc 
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm -lncurses

# Object files
OBJECTS = hof.o k.o ui.o main.o

# Targets
all: game

game: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

hof.o: hof.c
	$(CC) $(CFLAGS) -c $< -o $@

k.o: k.c
	$(CC) $(CFLAGS) -c $< -o $@

ui.o: ui.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) game

