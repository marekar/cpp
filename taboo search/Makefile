all: main

main: worker.o main.o problem.o problem_instance.o taboo.o consts.h
	g++ worker.o problem.o main.o problem_instance.o taboo.o -std=c++11 -o main

worker.o: worker.cpp worker.h consts.h
	g++ -c -Wall -std=c++11 worker.cpp

problem.o: problem.cpp problem.h consts.h
	g++ -c -Wall -std=c++11 problem.cpp

problem_instance.o: problem_instance.h problem_instance.cpp consts.h
	g++ -c -Wall -std=c++11 problem_instance.cpp
	
main.o: main.cpp consts.h
	g++ -c -Wall -std=c++11 main.cpp

taboo.o: taboo.h taboo.cpp consts.h
	g++ -c -Wall -std=c++11 taboo.cpp
clean:
	rm -rf *o main
