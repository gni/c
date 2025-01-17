CC = gcc
CFLAGS = -Wall -Wextra -g

all: main

main: main.o math_functions.o
    $(CC) $(CFLAGS) -o main main.o math_functions.o

main.o: main.c math_functions.h
    $(CC) $(CFLAGS) -c main.c

math_functions.o: math_functions.c math_functions.h
    $(CC) $(CFLAGS) -c math_functions.c

clean:
    rm -f *.o main
