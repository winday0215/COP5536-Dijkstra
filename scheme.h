#include<iostream>
#include "graph.h"
#include "fheap.h"

class scheme{
  public:
    int d[5000];
    bool s[5000];
    bool f[5000];

    scheme(Graph *g);
    ~scheme();

    void fheapscheme(int v);
    void simplescheme(int v);
};
