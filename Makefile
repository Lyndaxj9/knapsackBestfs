#Makefile

BestFirstSearch: BestFirstSearch.o
	g++ BestFirstSearch.o -g -o BestFirstSearch

BestFirstSearch.o: BestFirstSearch.cpp
	g++ -g -c BestFirstSearch.cpp

clean:
	-rm -f *.o BestFirstSearch
