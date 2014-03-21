#include <iostream>
using namespace std;

struct Fheapnode {
  Fheapnode *parent;
  Fheapnode *left, *right; //left and right pointer, form a circular linked list
  Fheapnode *child;//point to a child
  int key; //key value
  int rank; //number of children
  int vindex; //vertex index this node associated with
  int marked;
};

class Fheap {
  public:
    Fheapnode *trees[20];
    Fheapnode *nodes[5000];
    long compcount;
    int maxnodes, maxtrees, itemcount, treetable;//$treetable tracks the rank
    Fheap(int n);
    ~Fheap();

    int deletemin();
    void insert(int vindex, int key);
    void dcreasekey(int vindex, int newkey);
    void meld(Fheapnode *treelist);
    int numvertices();
};
