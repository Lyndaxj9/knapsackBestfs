#Makefile

bfs: bfs.o
	g++ bfs.o -g -o bfs

bfs.o: bfs.cpp
	g++ -g -c bfs.cpp

clean:
	-rm -f *.o bfs
