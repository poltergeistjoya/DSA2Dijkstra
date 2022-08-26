dijkstra.exe: dijkstra.o graph.o heap.o hash.o
	g++ -o dijkstra.exe dijkstra.o graph.o heap.o hash.o -std=c++11

dijkstra.o: dijkstra.cpp graph.h heap.h hash.h
	g++ -c dijkstra.cpp -std=c++11

graph.o: graph.cpp graph.h heap.h hash.h
	g++ -c graph.cpp -std=c++11

heap.o: heap.cpp heap.h hash.h
	g++ -c heap.cpp -std=c++11

hash.o: hash.cpp hash.h
	g++ -c hash.cpp -std=c++11

debug:
	g++ -g -o dijkstraDebug.exe dijkstra.cpp graph.cpp heap.cpp hash.cpp -std=c++11

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups