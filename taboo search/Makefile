all: main

main: worker.o main.o problem.o problem_instance.o
	g++ worker.o problem.o main.o problem_instance.o -o main

worker.o: worker.cpp worker.h
	g++ -c -Wall worker.cpp

problem.o: problem.cpp problem.h
	g++ -c -Wall problem.cpp
	
main.o: main.cpp
	g++ -c -Wall main.cpp

problem_instance.o: problem_instance.h problem_instance.cpp
	g++ -c -Wall problem_instance.cpp
clean:
	rm -rf *o main
