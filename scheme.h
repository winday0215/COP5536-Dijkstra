#include<iostream>
#include "graph.h"
#include "fheap.h"

class Scheme{
  public:
    long d[5000];
    bool s[5000];
    bool f[5000];

    Scheme(Graph *g);
    ~Scheme();

    void fheapscheme(int v, bool print);
    void simplescheme(int v, bool print);
};
