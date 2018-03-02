#include <bits/stdc++.h>

using namespace std;

class Hashmap {
private:
  struct Elem {
    int key;
    string item;
  };
  Elem* table[9];
  bool tombstone[9];
  int size;

  // find index of element with matching key and return the index
  // otherwise return -1
  int getIndex(int key) {
    int index = key % 9;
    int count = 0;
    while(count < 9) {
      if( (table[index] && table[index]->key == key) ||
          (!table[index] && !tombstone[index]))
        break;
        
      index = (index + 1) % 9; // linear probing
      ++count;
    }
    
    if(count == 9) return -1; // not found after probing entire table
    else return index;
  }

public:
  Hashmap() { 
    for(int i = 0; i < 9; ++i) {
      table[i] = NULL;
      tombstone[i] = false;
    }
    size = 0;
  }
  virtual ~Hashmap() {
    if(size != 0) {
      for(int i = 0; i < 9; ++i) {
        if(table[i] != NULL) delete table[i];
      }
    }
  }

  // returns true if insertion is successful, false otherwise
  bool insert(int key, string item) {
    if(size == 9) return false;

    int insertIdx = key % 9;
    while(table[insertIdx] != NULL)
      insertIdx = (insertIdx + 1) % 9; // linear probing
    
    table[insertIdx] = new Elem;
    table[insertIdx]->key = key;
    table[insertIdx]->item = item;
    tombstone[insertIdx] = false; // clears tombstone flag
    ++size;
    return true;
  }

  // if key is found, return true and pass the value of item out
  // otherwise return false
  bool find(int key, string& item) {
    if(size == 0) return false;
    int index = getIndex(key);
    if(index == -1) return false;
    item = table[index]->item;
    return true;
  }

  // removes the element with matching key, otherwise do nothing
  void remove(int key) {
    if(size > 0) {
      int index = getIndex(key);
      if(index != -1) { // if found, delete
        delete table[index];
        table[index] = NULL;
        tombstone[index] = true; // mark tombstone to prevent linear probing from stopping prematurely
      }
    }
  }
};


int main() {
  Hashmap H;
  H.insert(14, "apple"); 
  H.insert(5, "durian");
  H.insert(24, "pineapple");
  H.remove(5);

  string fruit;
  if(H.find(24, fruit))
    cout << "Fruit found for key 24 is " << fruit << endl;
  else
    cout << "Fruit not found for key 24" << endl;
  return 0;
}
