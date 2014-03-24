#include "scheme.h"
#include <climits>
using namespace std;

Graph *graph;

Scheme::Scheme(Graph *g){
  graph = g;
}

Scheme::~Scheme(){}

void Scheme::fheapscheme(int v, bool print){
  int n;
  n = graph->numvertices;

  for(int i=0; i<n; i++){
    d[i] = LONG_MAX;
  }
  for(int i=0; i<n; i++){
    s[i] = false;
  }
  for(int i=0; i<n; i++){
    f[i] = false;
  }

  d[v] = 0;
  Fheap *fheap = new Fheap(n);

  fheap->insert(v, 0);
  f[v] = true;
 
  while(fheap->numvertices() > 0){
    int vindex;
    vindex = fheap->deletemin();
    

    s[vindex] = true;
    f[vindex] = false;

    list<Graphedge> edgelist = graph->vertexarray[vindex].childlist;
    list<Graphedge>::iterator it;
    for(it = edgelist.begin();
        it != edgelist.end();
        ++it){
      int dest = (*it).dest;

      if(s[dest] == false){
        long distance = d[vindex] + (*it).weight;
        if(distance < d[dest]){
          d[dest] = distance;
          if(f[dest]){
            fheap->dcreasekey(dest, d[dest]);
          }
          else {
            fheap->insert(dest, d[dest]);
            f[dest] = true;
          }
        }
      }
    }
  }

  if(print){
    for(int i=0; i<n; i++){
      cout << "Node index  "<< i << ", distance " << d[i] << endl;
    }
  }
  
  //clean
  delete fheap;

}
void Scheme::simplescheme(int v, bool print){
  int n;
  n = graph->numvertices;

  for(int i=0; i<n; i++){
    s[i] = false;//indicate if a node is in spt
    d[i] = LONG_MAX; //distance to source node
  }

  d[v] = 0;
  int counter = 0;

  while(counter < n){
    int u;
    //find min distance
    long min = LONG_MAX;

    for(int i=0; i<n; i++){
      if(s[i] == false && d[i] <= min){
          min = d[i];
          u = i;
      }
    }

    s[u] = true; //add u into shortest path tree
    counter++; //count number of nodes in spt
    list<Graphedge> edgelist = graph->vertexarray[u].childlist;
    list<Graphedge>::iterator it;

    //add v's neighbors into d[]
    for(it = edgelist.begin();
        it != edgelist.end();
        ++it){
        int dest = (*it).dest;

        //update u's neighbor's d[]
        if(s[dest] == false){
          long distance = d[u] + (*it).weight;
          if(distance < d[dest]){
            d[dest] = distance; 
          }
        }
    }
  }
    
  if(print){
    for(int i=0; i<n; i++){
      cout << "Node index  "<< i << ", distance " << d[i] << endl;
    }
  }
}
