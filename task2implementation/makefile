CC=g++
CFLAGS= -c -Wall -std=c++14
EXENAME= task2

default: main.o
	$(CC) main.o -o $(EXENAME)
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
clean:
	del *o $(EXENAME)
run:
	./$(EXENAME)

