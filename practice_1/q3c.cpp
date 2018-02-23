#include <bits/stdc++.h>

using namespace std;

struct Node {
  int key;
  Node *next;
  Node *prev;
};

class List {
private:
  Node *head;
  Node *tail;
  Node *median;
  int size; // tracks the size of the list
  
public:
  List() { head = tail = median = NULL; size = 0; }
  void insert(int key);
  bool remove(int key);
  int findMedianKey();
  
  // debug/test
  void print()
  {
    Node *cur = head;
    if(cur==NULL) cout << "Empty List" << endl;
    else
    {
      cout << cur->key;
      cur = cur->next;
      while(cur)
      {
        cout << " -> " << cur->key;
        cur = cur->next;
      }
      cout << endl;
    }
  }
};

void List::insert(int key)
{
  // create new node
  Node *n = new Node;
  n->key = key;
  int pos = 0;

  Node *cur=head;
  // traversal to find insertion point, cur will point to the found
  // insertion point
  while(cur && key > cur->key)
  {
    cur = cur->next;
    ++pos;
  }

  // insert
  n->next = cur;
  // update link of node following newly inserted node
  if(cur != NULL)
  {
    n->prev = cur->prev;
    cur->prev = n;
  }
  else
  {
    n->prev = tail; // tail was NULL if this is first node inserted
    tail = n;
  }
  // n’s links properly updated, following node’s links also updated
  // update links of preceding node, accessible using n->prev
  if(n->prev != NULL)
    n->prev->next = n;
  else // we have inserted at the head
    head = n;

  ++size;

  // if the new size is odd, then median pointer will be 
  // right-shifted if insertion point is greater than or equal to 
  // floor of (size/2)
  if(size%2 == 1 && pos >= size/2)
  {
    if(median == NULL) // this must have been the first insertion
      median = head;
    else // guaranteed to have 3 or more nodes (thus valid median)
      median = median->next;
  }
  // if the new size is even, then median pointer will be 
  // left-shifted if insertion point is less than (size/2) 
  else if(size%2 == 0 && pos < size/2)
  {
    // guaranteed to have 2 or more nodes (thus valid median)
    median = median->prev;
  }
  // else no need to shift median pointer
}

bool List::remove(int key)
{
  bool found = false;
  int pos = 0;
  
  Node *cur=head;
  // traverse to find deletion point (cur)
  while(cur && !found)
  {
    if(cur->key == key)
      found = true;
    else
    {
      cur = cur->next;
      ++pos;
    }  
  }

  if(found)
  {
    // update link of preceding node
    if(cur->prev != NULL)
      cur->prev->next = cur->next;
    else // we have removed the first node
      head = cur->next;

    // update link of following node
    if(cur->next != NULL)
      cur->next->prev = cur->prev;
    else // we have removed the last node
      tail = cur->prev;

    // if median is pointing to cur, we can still follow the links 
    // to preceding or following node correctly, 
    // as cur->next and cur->prev have not been modified

    // if the size is odd, then median pointer will be 
    // left-shifted if deletion point is greater than or equal to 
    // floor of (size/2)
    if(size%2 == 1 && pos >= size/2)
      median = median->prev;
    // if the size is even, then median pointer will be 
    // right-shifted if deletion point is less than (size/2) 
    else if(size%2 == 0 && pos < size/2)
      median = median->next;


    delete cur;
    --size;
  }

  return found;
}

// O(1) complexity
int List::findMedianKey()
{
  if(median != NULL)
  {
    if(size % 2 == 1)
      return median->key;
    else
      return ((median->key + median->next->key) / 2);
  }

  return -1;
}






// testing
int main()
{
    List l;
    
    cout << "inserting 25" << endl;
    l.insert(25);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "inserting 7" << endl;
    l.insert(7);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "inserting 37" << endl;
    l.insert(37);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "inserting 58" << endl;
    l.insert(58);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "inserting 14" << endl;
    l.insert(14);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "inserting 3" << endl;
    l.insert(3);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "inserting 96" << endl;
    l.insert(96);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "removing 58" << endl;
    l.remove(58);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "removing 96" << endl;
    l.remove(96);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "inserting 46" << endl;
    l.insert(46);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "removing 25" << endl;
    l.remove(25);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    cout << "removing 3" << endl;
    l.remove(3);
    l.print();
    cout << "median = " << l.findMedianKey() << endl;
    
    return 0;
}