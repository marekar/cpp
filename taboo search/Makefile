all: main

main: worker.o main.o problem.o
	g++ worker.o problem.o main.o -o main

worker.o: worker.cpp worker.h
	g++ -c -Wall worker.cpp

problem.o: problem.cpp problem.h
	g++ -c -Wall problem.cpp
	
main.o: main.cpp
	g++ -c -Wall main.cpp

clean:
	rm -rf *o main
