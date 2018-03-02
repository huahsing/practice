#include <bits/stdc++.h>

using namespace std;

struct Node {
  int key;
  Node *left;
  Node *right;
  Node *parent;
  int height;
};

#define leftTooDeep(balance) (balance > 1)
#define rightTooDeep(balance) (balance < -1)
#define leftDeeper(balance) (balance == 1)
#define rightDeeper(balance) (balance == -1)

class AVL {
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
  Node* rotateRight(Node *n);
  Node* rotateLeft(Node *n);
  void updateNewHeight(Node *n);
  int getBalance(Node *n)
  {
    int leftHeight = n->left ? n->left->height : -1;
    int rightHeight = n->right ? n->right->height : -1;
    return leftHeight - rightHeight;
  }
  
  static int rotations;
  
public:
  AVL() { root = NULL; }
  virtual ~AVL();
  void insert(int key);
  bool remove(int key);
  int minKey();
  int maxKey();
  void print();
};

int AVL::rotations = 0;

AVL::~AVL()
{
  _postOrderDestroy(root);
} 

void AVL::_postOrderDestroy(Node *n)
{
  if(n == NULL) return;
  _postOrderDestroy(n->left);
  _postOrderDestroy(n->right);
  delete n;
}

bool AVL::isLeaf(Node& node)
{
  return (!node.left && !node.right);
}

bool AVL::hasOneChild(Node& node)
{
  return (node.left && !node.right || !node.left && node.right);
}

Node* AVL::_insert(Node *n, int key)
{
  Node *retNode;
  if(n == NULL)
  {
    n = new Node;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    n->key = key;
    n->height = 0;
    retNode = n;
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
  
  // update height
  updateNewHeight(n);
  
  if(leftTooDeep(getBalance(n)) && leftDeeper(getBalance(n->left)))
  {
    retNode = rotateRight(n); ++rotations;
  }
  else if(rightTooDeep(getBalance(n)) && rightDeeper(getBalance(n->right)))
  {
    retNode = rotateLeft(n); ++rotations;
  }
  else if(leftTooDeep(getBalance(n)) && rightDeeper(getBalance(n->left)))
  {
    n->left = rotateLeft(n->left);
    n->left->parent = n;
    updateNewHeight(n->left);
    retNode = rotateRight(n);
    ++rotations;
  }
  else if(rightTooDeep(getBalance(n)) && leftDeeper(getBalance(n->right)))
  {
    n->right = rotateRight(n->right);
    n->right->parent = n;
    updateNewHeight(n->right);
    retNode = rotateLeft(n);
    ++rotations;
  }
  else // balanced, return original node
    retNode = n;
  
  return retNode;
}

Node* AVL::_remove(Node *n, int key, bool &removed)
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
  
  // update height
  if(retNode)
  {
    updateNewHeight(retNode);
  
    if(leftTooDeep(getBalance(retNode)) && leftDeeper(getBalance(retNode->left)))
    {
      retNode = rotateRight(retNode); ++rotations;
    }
    else if(rightTooDeep(getBalance(retNode)) && rightDeeper(getBalance(retNode->right)))
    {
      retNode = rotateLeft(retNode); ++rotations;
    }
    else if(leftTooDeep(getBalance(retNode)) && rightDeeper(getBalance(retNode->left)))
    {
      retNode->left = rotateLeft(retNode->left);
      retNode->left->parent = retNode;
      updateNewHeight(retNode->left);
      retNode = rotateRight(retNode);
      ++rotations;
    }
    else if(rightTooDeep(getBalance(retNode)) && leftDeeper(getBalance(retNode->right)))
    {
      retNode->right = rotateRight(retNode->right);
      retNode->right->parent = retNode;
      updateNewHeight(retNode->right);
      retNode = rotateLeft(retNode);
      ++rotations;
    }
  }
  
  return retNode;
}

Node* AVL::_successor(Node* n)
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

Node* AVL::_predecessor(Node* n)
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

void AVL::_print(Node *n, int depth)
{
  cout << setw(4);
  if(!n) { cout << "\\0" << endl; return; }
  cout << n->key;
  _print(n->right, depth+1);
  for(int i = 0; i <= depth; i++) cout << "    ";
  _print(n->left, depth+1);
}

Node* AVL::rotateRight(Node *n)
{
  Node *origNleftChild = n->left;
  n->left = origNleftChild->right;
  if(n->left) n->left->parent = n;
  updateNewHeight(n);
  origNleftChild->right = n;
  n->parent = origNleftChild;
  return origNleftChild;
}

Node* AVL::rotateLeft(Node *n)
{
  Node *origNrightChild = n->right;
  n->right = origNrightChild->left;
  if(n->right) n->right->parent = n;
  updateNewHeight(n);
  origNrightChild->left = n;
  n->parent = origNrightChild;
  return origNrightChild;
}
  
void AVL::updateNewHeight(Node *n)
{
  int height;
  if(!n->left && !n->right) n->height = 0;
  else if (n->left && !n->right) n->height = 1 + n->left->height;
  else if(!n->left && n->right) n->height = 1 + n->right->height;
  else
    n->height = n->right->height > n->left->height ? (1+n->right->height) : (1+n->left->height);
}

//////////////////
// PUBLIC METHODS
//////////////////
void AVL::insert(int key)
{
  root = _insert(root, key);
  root->parent = NULL; // this is important as if there's balancing, the parent need to be updated after _insert returns;
  updateNewHeight(root);
}

bool AVL::remove(int key)
{
  bool removed;
  root = _remove(root, key, removed);
  if(root)
  {
    root->parent = NULL;
    updateNewHeight(root);
  }
  return removed;
}

int AVL::minKey()
{
  if(root == NULL) return -1;
  Node *n = root;
  while(n->left) n = n->left;
  return n->key;
}

int AVL::maxKey()
{
  if(root == NULL) return -1;
  Node *n = root;
  while(n->right) n = n->right;
  return n->key;
}

void AVL::print()
{
  // using custom traversal to always visit right subtree first
  _print(root, 0);
  cout << "total rotations = " << rotations << endl;;
}


//////////////////
// TEST
//////////////////
int main()
{
  AVL avl;
  
  avl.insert(75);
  avl.insert(67);
  avl.insert(88);
  avl.insert(38);
  avl.insert(61);
  avl.insert(48);
  avl.insert(57);
  avl.insert(60);
  avl.remove(38);
  avl.print();

  return 0;
}