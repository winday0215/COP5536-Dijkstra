#include "graph.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
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
  vertexarray[dest].childlist.push_back(newedge2);
  vertexarray[source].childsize++;
  vertexarray[dest].childsize++;
}

//check if an edge from source s to destination e exist
bool Graph::edgeexist(int s, int e){
  
  //s can't be equal to e
  if( s == e){
    return true;
  }
  int temp;
  
  //make sure s<e
  if (s > e){
    temp = s;
    s = e;
    e = temp;
  }

  string key;
  stringstream ss;
  ss << s;
  stringstream ss1;
  ss1 << e;
  key = ss.str() +":" + ss1.str();

  //check is edge <s,e> exist
  pair<map<string, bool>::iterator, bool> ret;
  ret = edges.insert(pair<string,bool> (key,true)); 
  if(ret.second == false){
    return true;
  }
  return false;
}

//use DFS to check if this graph is all connected
bool Graph::connected(){
    int stack[numvertices]; //stack
    bool visited[numvertices];
    bool tempvisited[numvertices];
    int pos, componentcount = 0;
    int vertexcount = 0, tempvcount;
    int v, w;
    int i,j,k,l;
    int start;
    vector< vector<int> > component;

    for(j=0;j<numvertices; j++){
      visited[j] = false;
      tempvisited[j] = false;
    }

    while(vertexcount < numvertices){
      pos = 0;
      tempvcount = 0;
      for(i =0; i<numvertices; i++){
    	  if(visited[i] == false){
	        start = i;
	        break;
	      }		  
      }

      //DFS
	    tempvisited[i] = true;//check from vertex i
      stack[pos++] = i;

      while(pos){
        v = stack[--pos];//pop from stack
        tempvcount++;

        list<Graphedge>::iterator it;
        for(it = vertexarray[v].childlist.begin();
            it != vertexarray[v].childlist.end();
            ++it){
            w = (*it).dest;
            if(tempvisited[w] == false){
              tempvisited[w] = true;
              stack[pos++] = w; //push into stack
            }
        }
      }
      vertexcount += tempvcount;
      //cout << "vertexcount " << vertexcount << endl;
      //copy connected component to component[][]
      k=0;
      vector<int> eachcomponent;
      for(i=0; i<numvertices;i++){
        if(tempvisited[i] == true){
          eachcomponent.push_back(i);
        }
      }

      component.push_back(eachcomponent);
      componentcount++;
      //copy visited nodes back to visited
      for(k=0; k<numvertices; k++){
	      if(tempvisited[k] == true && visited[k] == false){
	        visited[k] = true;
          tempvisited[k] = false; //reset tempvisited
	      }
      }
  }
//connect each connected component
  if(componentcount > 1){
     for(i=0; i<componentcount-1; i++){
        long w = rand()%1000 + 1;
        insertedge(component[i][0], component[i+1][0],w);
    }
  }

  return true;
}

//generate random graph
void Graph::randomgraph(int nvertex, int nedge, long weight){
  int edgecount = 0;
  bool success = false;
  int fedgecount = 0, i=1;

    while(edgecount < nedge){
      if(edgecount - fedgecount==100000){
  //      cout <<i<< "th 100000"<< endl;
        i++;
        fedgecount = edgecount;
      }
      int i,j;
      long w;
      w = rand() % weight + 1;
      
      do{
         i = rand() % nvertex;
         j = rand() % nvertex;
      }while(edgeexist(i,j));
      
      insertedge(i,j,w);
      edgecount++;
    }
    //check if every node of this graph can reach all other nodes
    success = connected();
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

