#include "graph.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;


//constructor
Graph::Graph(){}
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

//insert one edge into graph
void Graph::insertedge(int source, int dest, long weight){
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

//check if an edge from source s to destination e exist
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

//use DFS to check if this graph is all connected
bool Graph::connected(){
    int stack[numvertices]; //stack
    bool visited[numvertices];
    int pos = 0;
    
    for(int j=0;j<numvertices; j++){
      visited[j] = false;
    }

    int vertexcount = 0;
    visited[0] = true;//check from vertex 0
    stack[pos++] = 0;

    int v, w;
    while(pos){
      v = stack[--pos];//pop from stack
      vertexcount++;

      list<Graphedge>::iterator it;
      for(it = vertexarray[v].childlist.begin();
          it != vertexarray[v].childlist.end();
          ++it){
          w = (*it).dest;
          if(visited[w] == false){
            visited[w] = true;
            stack[pos++] = w; //push into stack
          }
      }
    }

    //if count of reachable nodes = total number of nodes, success
    if(vertexcount != numvertices){
      return false;
    }
  return true;
}

//generate random graph
void Graph::randomgraph(int nvertex, int nedge, long weight){
  int edgecount = 0;
  bool success = false;
  int fedgecount = 0, i=1;

 // while(!success){
    while(edgecount < nedge){
      if(edgecount - fedgecount==100000){
        cout <<i<< "th 100000"<< endl;
        i++;
        fedgecount = edgecount;
      }
      int i = rand() % nvertex;
      int j = rand() % nvertex;
      long w = rand() % weight + 1;

      if(i != j && edgeexist(i,j) == false){
        insertedge(i,j,w);
        edgecount++;
      } 
    }
    //check if every node of this graph can reach all other nodes
   // success = connected();
 // }
}

int Graph::graphfromfile(string filename){
  ifstream infile(filename.c_str());
  infile.seekg(0, ifstream::end);
  if(infile.tellg() == 0){
    cerr << "File is empty" << endl;
    exit(0);
  }
  infile.clear();
  infile.seekg(0, ios::beg);

  int startpoint;
  int nedge;
  int count=0;
  vector< vector<string> > file;
  string token;
  string line;
  
  //read file
  while(getline(infile, line)){
    istringstream iss(line);
    vector<string> sline;
    while (iss >> token){
      sline.push_back(token);
    }
    file.push_back(sline);
    count++;
  }

  infile.close();

  //check if file is normal
  if(file.size() <= 2){
    cerr << "File is not usable" << endl;
    exit(0);
  }

  if(file[0].size() != 1){
    cerr << "Source node num is vague, check input file, Line 1" << endl;
    exit(0);
  }

  if(file[1].size() != 2){
    cerr << "The number of vertices and edges are vague, check input file, Line 2" << endl;
    exit(0);
  }
  //build the graph
  startpoint = atoi(file[0][0].c_str());
  numvertices = atoi(file[1][0].c_str());
  nedge = atoi(file[1][1].c_str());

  if(count-2 != nedge){
    cerr << "Total number of edges do not match given edge in Line 2." << endl;
    exit(0);
  }
  for(int i=0; i<numvertices; i++){
    vertexarray[i].childsize = 0;
  }
  vector< vector<string> >::iterator it;
  //insert edges
  for (it = file.begin() + 2;
      it != file.end();
      ++it){
    int source = atoi((*it)[0].c_str());
    int  dest = atoi((*it)[1].c_str());
    long  weight = atoi((*it)[2].c_str());
    insertedge(source, dest, weight);
  }
  return startpoint;
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

