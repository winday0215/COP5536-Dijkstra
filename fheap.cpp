#include<cmath>
#include "fheap.h"
using namespace std;

Fheap::Fheap(int n){
  maxnodes = n;
  maxtrees = 1+(int)(1.44*log(n)/log(2.0));

  for(int i=0; i<maxnodes; i++){
    nodes[i] = NULL;
  }
  for(int j=0; j<maxtrees; j++){
    trees[j] = NULL;
  }

  itemcount = 0;
  treetable = 0; //track maximum numchild
}

Fheap::~Fheap() {}

int Fheap::deletemin(){
  int r = -1;
  
  int t = treetable;
  while(t){
    t = t>>1;
    r++;
  }

  Fheapnode *minptr;
  minptr = trees[r];
  int k = minptr->key;

  //find minimum
  while(r>0){
    r--;
    Fheapnode *next;
    next = trees[r];
    if(next != NULL){
      if(next->key < k){
        k = next->key;
        minptr = next;
      }
    }
  }

  //delete minimum
  trees[minptr->rank] = NULL;
  treetable -= (1 << minptr->rank);

  //meld minimum's child
  if(minptr->child != NULL){
    meld(minptr->child);
  }

  int v = minptr->vindex;
  nodes[v] = NULL;
  delete minptr;
  itemcount--;

  return v;
}

void Fheap::insert(int vindex, int key){
  Fheapnode *newnode = new Fheapnode;

  newnode->parent = NULL;
  newnode->child = NULL;
  newnode->left = newnode;
  newnode->right = newnode;
  newnode->key = key;
  newnode->vindex = vindex;
  newnode->rank = 0;

  nodes[vindex] = newnode;
  meld(newnode); //meld this node into fheap
  itemcount++; //number of nodes ++
}

void Fheap::dcreasekey(int vindex, int newkey){
  Fheapnode *parent, *cut, *newroot, *lc, *rc;
  int pr;

  cut = nodes[vindex];
  parent = cut->parent;
  cut->key = newkey;

  if(parent == NULL){
    return;
  }

  lc = cut->left;
  rc = cut->right;
  lc->right = rc;
  rc->left = lc;
  cut->left = cut->right = cut;

  newroot = cut;

  while(parent != NULL && parent->marked == 1){
    parent->rank--;
    
    //if parent's child pointer is the cut node
    //update to child's right sibling
    if(parent->rank){
      if(parent->child == cut){
        parent->child = rc;
      }
    }
    else {
      parent->child = NULL;
    }
    
    //cut parent off from the tree
    cut = parent;
    parent = cut->parent;

     lc = cut->left;
     rc = cut->right;
     lc->right = rc;
     rc->left = lc;

     //add cut into reinsertion list
    lc = newroot->left;
    newroot->left = cut;
    lc->right = cut;
    cut->left = lc;
    cut->right = newroot;
    newroot = cut;
  }

  if(parent == NULL){
    pr = cut->rank + 1;
    trees[pr] = NULL;
    treetable -= (1 << pr);
  }
  else {
    parent->rank--;
    if(parent->rank){
      if(parent->child == cut){
         parent->child = rc;
      }
    }
    else {
       parent->child = NULL;
    }
  //mark parent as cut
  parent->marked = 1;
  }
  
  //meld new root into heap
  meld(newroot);

}

void Fheap:: meld(Fheapnode *treelist){
  Fheapnode *first, *nodeptr, *next, *lc, *rc;
  Fheapnode *newnode, *temp, *temp1;
  int rank;

  first = nodeptr = treelist;
  do {
    next = nodeptr->right;
    nodeptr->right = nodeptr;
    nodeptr->left = nodeptr;
    nodeptr->parent = NULL;
    
    newnode = nodeptr;
    rank = nodeptr->rank;
    
    do{
    
      temp = trees[rank];

      //if a tree with rank exist
      if(temp != NULL){
        treetable -= (1 << rank);
        trees[rank] = NULL;
        //choose the smaller one between temp and new node as newroot
        if(temp->key < newnode->key){
          temp1 = newnode;
          newnode = temp;
          temp = temp1;
        }
        if(rank++ >0){
          rc = newnode->right;
          lc = rc->left;
          temp->left = lc;
          temp->right = rc;
          lc->right = temp;
          rc->left = temp;
        }
        temp->parent = newnode;
        newnode->child = temp;
        newnode->rank = rank;
        temp->marked = 0; //not root anymore
      }
      else {
        trees[rank] = newnode;
        treetable += (1<< rank);
        newnode->marked = 1; //become a root of a tree 
      }
    }while(temp);
    
    nodeptr = next; //begin next round
  }while(nodeptr != first);
}
