#include <bits/stdc++.h>

using namespace std;

struct Node {
  int key;
  Node *left;
  Node *right;
};

class BST {
private:
  Node *root;
  void _postOrderDestroy(Node *parent);
  bool isLeaf(Node& node);
  bool hasOneChild(Node& node);
  Node* _insert(Node *parent, int key); // helper for recursion
  Node* _remove(Node *parent, int key, bool& removed);
  Node& _minNode(Node& parent);
  Node& _maxNode(Node& parent);
  void _print(Node *parent, int depth);
  
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

void BST::_postOrderDestroy(Node *parent)
{
  if(parent == NULL) return;
  _postOrderDestroy(parent->left);
  _postOrderDestroy(parent->right);
  delete parent;
}

bool BST::isLeaf(Node& node)
{
  return (!node.left && !node.right);
}

bool BST::hasOneChild(Node& node)
{
  return (node.left && !node.right || !node.left && node.right);
}

Node* BST::_insert(Node *parent, int key)
{
  if(parent == NULL)
  {
    parent = new Node;
    parent->left = NULL;
    parent->right = NULL;
    parent->key = key;
  }
  else
  {
    if(key < parent->key)
      parent->left = _insert(parent->left, key);
    else
      parent->right = _insert(parent->right, key);
  }
  
  return parent;
}

Node* BST::_remove(Node *parent, int key, bool &removed)
{
  Node *retNode;
  
  if(parent == NULL) 
  {
    removed = false;
    retNode = NULL;
  }
  else
  {
    if(parent->key == key)
    {
      // check for 3 different cases: 'is leaf' vs 'has one child' vs 'has two children'
      if(isLeaf(*parent))
      {
        retNode = NULL;
        delete parent;
      }
      else if(hasOneChild(*parent))
      {
        if(parent->left)
          retNode = parent->left;
        else
          retNode = parent->right;
        
        delete parent;
      }
      else // have two children: either replace with min successor or max predecessor
      {
         // using min successor method
         Node& nodeToDelete = _minNode(*parent->right);
         // copy the value(s)
         parent->key = nodeToDelete.key;
         // delete the min successor node
         bool tmpflag;
         parent->right = _remove(parent->right, nodeToDelete.key, tmpflag);
         retNode = parent;
      }
      
      removed = true;
    }
    else if(key > parent->key)
    {
      parent->right = _remove(parent->right, key, removed);
      retNode = parent;
    }
    else // key < parent->key
    {
      parent->left = _remove(parent->left, key, removed);
      retNode = parent;
    }
  }
  
  return retNode;
}

Node& BST::_minNode(Node& parent)
{
  Node *left = &parent;
  while(left->left) left = left->left;
  return *left;
}

Node& BST::_maxNode(Node& parent)
{
  Node *right = &parent;
  while(right->right) right = right->right;
  return *right;
}

void BST::_print(Node *parent, int depth)
{
  cout << setw(4);
  if(!parent) { cout << "\\0" << endl; return; }
  cout << parent->key;
  _print(parent->right, depth+1);
  for(int i = 0; i <= depth; i++) cout << "    ";
  _print(parent->left, depth+1);
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
  return removed;
}

int BST::minKey()
{
  return _minNode(*root).key;
}

int BST::maxKey()
{
  return _maxNode(*root).key;
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