#include "scheme.h"
using namespace std;

Graph *graph;

Scheme::Scheme(Graph *g){
  graph = g;
}

Scheme::~Scheme(){}

void Scheme::fheapscheme(int v){
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
    
   // cout << "scheme "<< vindex << ", " << d[vindex] << endl;

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

  
  //clean
  delete fheap;

}

void Scheme::simplescheme(int v){}
