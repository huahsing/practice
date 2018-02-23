#include <bits/stdc++.h>

using namespace std;

struct Node {
  int key;
  Node *next;
};

class List {
private:
  Node *head;
  int size; // tracks the size of the list
  
public:
  List() { head = NULL; size = 0; }
  void insert(int key);
  bool remove(int key);
  
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

  Node *prev=NULL, *cur=head;
  // traversal to find insertion point, cur will point to the found
  // insertion point
  while(cur && key > cur->key)
  {
      prev = cur;
      cur = cur->next;
  }

  // insert
  n->next = cur;
  if(prev != NULL)
    prev->next = n;
  else
    head = n;

  ++size;
}


bool List::remove(int key)
{
  bool found = false;
  
  Node *prev=NULL, *cur=head;
  // traverse to find deletion point (cur)
  while(cur && !found)
  {
    if(cur->key == key)
    {
      found = true;
    }
    else
    {
      prev = cur;
      cur = cur->next;
    }
  }

  if(found)
  {
    if(prev != NULL)
      prev->next = cur->next;
    else // we have removed the first node
      head = cur->next;

    delete cur;
    --size;
  }

  return found;
}




// testing
int main()
{
    List l;
    
    cout << "inserting 25" << endl;
    l.insert(25);
    l.print();
    
    cout << "inserting 7" << endl;
    l.insert(7);
    l.print();
    
    cout << "inserting 37" << endl;
    l.insert(37);
    l.print();
    
    cout << "inserting 58" << endl;
    l.insert(58);
    l.print();
    
    cout << "inserting 14" << endl;
    l.insert(14);
    l.print();
    
    cout << "inserting 3" << endl;
    l.insert(3);
    l.print();
    
    cout << "inserting 96" << endl;
    l.insert(96);
    l.print();
    
    cout << "removing 58" << endl;
    l.remove(58);
    l.print();
    
    cout << "removing 96" << endl;
    l.remove(96);
    l.print();
    
    cout << "inserting 46" << endl;
    l.insert(46);
    l.print();
    
    cout << "removing 25" << endl;
    l.remove(25);
    l.print();
    
    cout << "removing 3" << endl;
    l.remove(3);
    l.print();
    
    return 0;
}