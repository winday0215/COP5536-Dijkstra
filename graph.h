#include <iostream>
#include <list>
using namespace std;

/*------------------------------------------
 * Graphedge defines the edge between two vertices. source is the start point of
 * the edge. dest is the destination node
 * number and weight is the weight of this edge.
 * ---------------------------------------------*/
struct Graphedge{
  int source;
  int dest;
  int weight;
};

/*-------------------
 * Graphvertex defines the vertices within a graph. childsize shows how many 
 * children this vertex has. childlist stores a linked list, 
 * which includes all the edges start-end points and weights of the edges 
 * for this vertex.
 * ----------------------*/
struct Graphvertex{
  int childsize;
  list<Graphedge> childlist;
};

/*--------------------------------
 * Graph uses numbertices to represent the number of vertex it has.
 * array vertexarray stores the index of each vertex and its children list.
 * insertedge---create an edge and insert this edge into both source and dest
 *              vertices' children list.
 * edgeexist----check if an edge source-dest exist
 * connected---check if a graph is connected from source by DFS
 * printgraph--print all the vertices and edges of the graph, start from root
 * ----------------------------------*/
class Graph{
  public:
    int numvertices; //total vertices number
    Graphvertex vertexarray[5000];//maximum vertices number is 5000
    
    Graph(int n);
    ~Graph();

    void insertedge(int source, int dest, int weight);
    bool edgeexist(int source, int dest);
    bool connected();
    void randomgraph(int i, int j, int w);
    void printgraph();
};
