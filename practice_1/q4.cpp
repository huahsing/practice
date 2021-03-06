#include <bits/stdc++.h>

using namespace std;

struct Node {
  int key;
  Node *left;
  Node *right;
  Node *parent;
};

class BST {
private:
  Node *root;
  void _postOrderDestroy(Node *n);
  bool isLeaf(Node& node);
  bool hasOneChild(Node& node);
  Node* _insert(Node *n, int key); // helper for recursion
  Node* _remove(Node *n, int key, bool& removed);
  Node* _successor(Node* n);
  Node* _predecessor(Node* n);
  void _print(Node *n, int depth);
  
public:
  BST() { root = NULL; }
  virtual ~BST();
  void insert(int key);
  bool remove(int key);
  int minKey();
  int maxKey();
  void print();
};

BST::~BST()
{
  _postOrderDestroy(root);
} 

void BST::_postOrderDestroy(Node *n)
{
  if(n == NULL) return;
  _postOrderDestroy(n->left);
  _postOrderDestroy(n->right);
  delete n;
}

bool BST::isLeaf(Node& node)
{
  return (!node.left && !node.right);
}

bool BST::hasOneChild(Node& node)
{
  return (node.left && !node.right || !node.left && node.right);
}

Node* BST::_insert(Node *n, int key)
{
  if(n == NULL)
  {
    n = new Node;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->key = key;
  }
  else
  {
    if(key < n->key)
    {
      n->left = _insert(n->left, key);
      n->left->parent = n;
    }
    else
    {
      n->right = _insert(n->right, key);
      n->right->parent = n;
    }
  }
  
  return n;
}

Node* BST::_remove(Node *n, int key, bool &removed)
{
  Node *retNode;
  
  if(n == NULL) 
  {
    removed = false;
    retNode = NULL;
  }
  else
  {
    if(n->key == key)
    {
      // check for 3 different cases: 'is leaf' vs 'has one child' vs 'has two children'
      if(isLeaf(*n))
      {
        retNode = NULL;
        delete n;
      }
      else if(hasOneChild(*n))
      {
        if(n->left)
          retNode = n->left;
        else
          retNode = n->right;
        
        delete n;
      }
      else // have two children: either replace with min successor or max predecessor
      {
         // using min successor method
         Node* nodeToDelete = _successor(n);
         // copy the value(s)
         n->key = nodeToDelete->key;
         // delete the min successor node
         bool tmpflag;
         n->right = _remove(n->right, nodeToDelete->key, tmpflag);
         retNode = n;
      }
      
      removed = true;
    }
    else if(key > n->key)
    {
      n->right = _remove(n->right, key, removed);
      if(n->right) n->right->parent = n;
      retNode = n;
    }
    else // key < n->key
    {
      n->left = _remove(n->left, key, removed);
      if(n->left) n->left->parent = n;
      retNode = n;
    }
  }
  
  return retNode;
}

Node* BST::_successor(Node* n)
{
  Node *successor = NULL;
  if(n->right)
  {
    successor = n->right;
    while(successor->left) successor = successor->left;
  }
  else
  {
    Node *cur = n;
    successor = cur->parent;
    while(successor && successor->right == cur)
    {
      cur = successor;
      successor = successor->parent;
    }
  }
  
  return successor;
}

Node* BST::_predecessor(Node* n)
{
  Node *predecessor = NULL;
  if(n->left)
  {
    predecessor = n->left;
    while(predecessor->right) predecessor = predecessor->right;
  }
  else
  {
    Node *cur = n;
    predecessor = cur->parent;
    while(predecessor && predecessor->left == cur)
    {
      cur = predecessor;
      predecessor = predecessor->parent;
    }
  }
  
  return predecessor;
}

void BST::_print(Node *n, int depth)
{
  cout << setw(4);
  if(!n) { cout << "\\0" << endl; return; }
  cout << n->key;
  _print(n->right, depth+1);
  for(int i = 0; i <= depth; i++) cout << "    ";
  _print(n->left, depth+1);
}

//////////////////
// PUBLIC METHODS
//////////////////
void BST::insert(int key)
{
  root = _insert(root, key);
}

bool BST::remove(int key)
{
  bool removed;
  root = _remove(root, key, removed);
  root->parent = NULL;
  return removed;
}

int BST::minKey()
{
  if(root == NULL) return -1;
  Node *n = root;
  while(n->left) n = n->left;
  return n->key;
}

int BST::maxKey()
{
  if(root == NULL) return -1;
  Node *n = root;
  while(n->right) n = n->right;
  return n->key;
}

void BST::print()
{
  // using custom traversal to always visit right subtree first
  _print(root, 0);
}


//////////////////
// TEST
//////////////////
int main()
{
  BST bst;
  int insvals[11] = { 25, 7, 37, 58, 14, 3, 96, 43, 2, 75, 84 };
  for(int i = 0; i < 11; i++)
  {
    cout << "inserting " << insvals[i] << endl;
    bst.insert(insvals[i]);
    bst.print();
  }
  
  cout << "deleting 58" << endl;
  bst.remove(58);
  bst.print();
  
  cout << "deleting 14" << endl;
  bst.remove(14);
  bst.print();
  
  cout << "deleting 2" << endl;
  bst.remove(2);
  bst.print();
  
  cout << "inserting 12" << endl;
  bst.insert(12);
  bst.print();
  
  cout << "inserting 23" << endl;
  bst.insert(23);
  bst.print();
  
  cout << "deleting 12" << endl;
  bst.remove(12);
  bst.print();
  
  cout << "deleting 7" << endl;
  bst.remove(7);
  bst.print();
  
  cout << "deleting 37" << endl;
  bst.remove(37);
  bst.print();
  
  cout << "deleting 25" << endl;
  bst.remove(25);
  bst.print();
  
  return 0;
}