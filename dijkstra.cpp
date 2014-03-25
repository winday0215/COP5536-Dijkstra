#include "scheme.h"
#include <string>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <vector>
#include <ctime>
using namespace std;

int main(int argc, char ** argv){
  cout << "Please input command:" << endl;
  string input;
  getline(cin, input);
  string token;
  vector<string> inputparse;
  int n, startpoint;
  double numedge;

  stringstream ss(input);
  while(ss >> token){
    inputparse.push_back(token);
  }

  //create random graph
  if(!inputparse[1].compare("-r")){
    n = atoi(inputparse[2].c_str());
    double density = atof(inputparse[3].c_str());
    numedge = floor(0.5 * density * n*(n-1));
    cout << "Graph has " << n << " vertices and " << numedge << " edges" << endl;
    startpoint = atoi(inputparse[4].c_str());
    cout << "Create shortest path from vertex " << startpoint << endl;
    int nedge = (int)numedge;
    
    
    //create new graph
    Graph *g = new Graph(n);
    //random generate graph, vetices=n, edges=numedge, weight=1000
    g->randomgraph(n, nedge, 1000);
    //print graph
    //g->printgraph();
    Scheme *scheme = new Scheme(g);
    
    //use fheap scheme
    cout << "Fheap start" << endl; 
    clock_t start = clock();
    scheme->fheapscheme(startpoint,true);
    clock_t duration = clock() - start;
    //cout << "Fibonacci heap scheme cost " << duration << " microseconds" << endl;
    //use simple scheme
    cout << "Simple Scheme start" << endl; 
    clock_t sstart = clock();
    scheme->simplescheme(startpoint,true);
    clock_t sduration = clock() - sstart;
    //cout << "Simple scheme cost " << sduration << " microseconds" << endl;
    
    
    //clean
    delete scheme;
    delete g;
  }
  //read from file, operate by simple scheme
  else if(!inputparse[1].compare("-s")){
    string filename = inputparse[2];
    Graph *g = new Graph();

    //construct graph
    startpoint = g->graphfromfile(filename);

    //print graph
   // g->printgraph();
    Scheme *scheme = new Scheme(g);
    //use simple scheme
    //cout << "Cost from each node to source node " << startpoint << endl;
    scheme->simplescheme(startpoint, true);

    //clean
    delete scheme;
    delete g;
  }

  //read from file, operate by fheap
  else if(!inputparse[1].compare("-f")){
    string filename = inputparse[2];
    Graph *g = new Graph();

    //construct graph
    startpoint = g->graphfromfile(filename);

    //print graph
   // g->printgraph();
    Scheme *scheme = new Scheme(g);
    //use fheap scheme
    //cout << "Cost from each node to source node " << startpoint << endl;
    scheme->fheapscheme(startpoint, true);

    //clean
    delete scheme;
    delete g;
  }


}
