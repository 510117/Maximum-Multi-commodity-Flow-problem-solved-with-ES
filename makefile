CPPFLAG = -fopenmp -g -Wall -Wextra -O3

all: a.out

a.out: EA.o EA2.o Greedy.o Graph.o config.o main.cpp 
	g++ $(CPPFLAG) main.cpp EA.o EA2.o Graph.o config.o Greedy.o

EA.o: EA.h EA.cpp
	g++ -c $(CPPFLAG) EA.h EA.cpp

EA2.o: EA2.h EA2.cpp
	g++ -c $(CPPFLAG) EA2.h EA2.cpp

Greedy.o: Greedy.h Greedy.cpp
	g++ -c $(CPPFLAG) Greedy.h Greedy.cpp

Graph.o: Graph.h Graph.cpp config.o
	g++ -c $(CPPFLAG) Graph.h Graph.cpp

config.o: config.h config.cpp
	g++ -c $(CPPFLAG) config.h config.cpp

clean:
	rm -f a.out
	find . -type f -name '*.o' -delete
	find . -type f -name '*.h.gch' -delete