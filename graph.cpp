#include "graph.h"
#include <time.h>
using namespace std;


//constructor
Graph::Graph(int n){
  srand(time(NULL));
  numvertices = n;
  for(int i=0; i<n;i++){
    vertexarray[i].childsize = 0;
  }
}

//destructor
Graph::~Graph(){
  for(int i=0; i<numvertices; i++){
    vertexarray[i].childlist.clear();
  }
}

void Graph::insertedge(int source, int dest, int weight){
  Graphedge newedge1, newedge2;
  newedge1.source = source;
  newedge1.dest = dest;
  newedge1.weight = weight;
  newedge2.source = dest;
  newedge2.dest = source;
  newedge2.weight = weight;

  vertexarray[source].childlist.push_back(newedge1);
  vertexarray[source].childsize++;
  vertexarray[dest].childlist.push_back(newedge2);
  vertexarray[dest].childsize++;
}

bool Graph::edgeexist(int s, int e){

  list<Graphedge>::iterator it;

  for(it = vertexarray[s].childlist.begin();
      it != vertexarray[s].childlist.end();
      ++it){
    if((*it).source == s && (*it).dest == e){
      return true;
    }
  }
  return false;
}

bool Graph::connected(){
  for(int i=0; i<numvertices; i++){
    int stack[numvertices];
    bool visited[numvertices];
    int pos = 0;
    
    for(int j=0;j<numvertices; j++){
      visited[j] = false;
    }

    int vertexcount = 0;
    visited[i] = true;
    stack[pos++] = i;

    int v, w;
    while(pos){
      v = stack[--pos];
      vertexcount++;

      list<Graphedge>::iterator it;
      for(it = vertexarray[v].childlist.begin();
          it != vertexarray[v].childlist.end();
          ++it){
          w = (*it).dest;
          if(visited[w] == false){
            visited[w] = true;
            stack[pos++] = w;
          }
      }
    }
    if(vertexcount != numvertices){
      return false;
    }
  }
  return true;
}


void Graph::randomgraph(int nvertex, int nedge, int weight){
  int edgecount = 0;
  bool success = false;

  while(!success){
    while(edgecount < nedge){
      int i = rand() % nvertex;
      int j = rand() % nvertex;
      int w = rand() % weight;

      if(i != j && edgeexist(i,j) == false){
        insertedge(i,j,w);
        edgecount++;
      } 
    }
    success = connected();
  }
}


void Graph::printgraph(){
  for(int i=0; i<numvertices; i++){
    cout <<"Vertex " << i << "children - " << vertexarray[i].childsize
      << "children list - ";
    list<Graphedge>::iterator it;
    for(it = vertexarray[i].childlist.begin(); it != vertexarray[i].childlist.end(); ++it){
      cout << "( v"<< (*it).source << ", v" << (*it).dest << ", " << (*it).weight << ")";
    }
    cout << endl;
  }
}

