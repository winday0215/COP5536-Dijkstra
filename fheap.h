#include <iostream>
using namespace std;

struct Fheapnode {
  Fheapnode *parent;
  Fheapnode *left, *right; //left and right pointer, form a circular linked list
  Fheapnode *child;//point to a child
  int key; //key value
  int numchild; //number of children
  int vindex; //vertex index this node associated with
  int marked;
};

class Fheap {
  public:
    Fheap(int n);
    ~Fheap();

    int deletemin();
    int insert(int vindex, int key);
    int dcreasekey(int vindex, int newkey);

  private;
    Fheapnode *trees[20];
    Fheapnode *nodes[5000];
    int maxnodes, maxtrees, itemcount, treesum;
    long compcount;

    void meld(Fheapnode *treelist);
};
