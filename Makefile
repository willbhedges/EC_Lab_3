MyBank: main.o
	g++ -std=c++11 -g -Wall main.o -o MyBank

main.o: main.cpp
	g++ -std=c++11 -g -Wall -c main.cpp

clean: 
	rm *.o MyBank

