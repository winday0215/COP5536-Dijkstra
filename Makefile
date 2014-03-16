all: dijkstra.cpp graph.cpp
	g++ dijkstra.cpp graph.cpp
clean:
	rm *.out
