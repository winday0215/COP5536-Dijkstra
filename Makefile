all: dijkstra.cpp graph.cpp fheap.cpp scheme.cpp
	g++ dijkstra.cpp graph.cpp fheap.cpp scheme.cpp
clean:
	rm *.out
