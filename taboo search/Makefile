all: main

main: worker.o main.o
	g++ worker.o main.o -o main

worker.o: worker.cpp worker.h
	g++ -c -Wall worker.cpp

main.o: main.cpp
	g++ -c -Wall main.cpp

clean:
	rm -rf *o main
