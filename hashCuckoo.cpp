#include <iostream>
#include <cmath>
#include "hashCuckoo.hpp"

using namespace std;

node* HashTable::createNode(int key){
  node* nw = new node;
  nw->key = key;
  return nw;
}

HashTable::HashTable(int bsize){  // Constructor
  this->tableSize= bsize;
  table1 = new node*[tableSize];
  table2 = new node*[tableSize];
  for(int i=0;i<bsize;i++){
    table1[i] = NULL;
    table2[i] = NULL;
  }
}

unsigned int HashTable::hashFunction0(int key){
  return (key%10009);
}
unsigned int HashTable::hashFunction1(int key){
  int y = (int) floor(key/10009);
  return (y%10009);
}
int x=0;
// inserts a key into hash table
void HashTable::insertItemCuckoo(int key){
  int index1 = hashFunction0(key);
  if(x>=100){
    x=0;
    return;
  }
  if(table1[index1] == NULL){
    table1[index1] = createNode(key);
  }
  else{
    node *temp = table1[index1];
    table1[index1] = NULL;
    table1[index1] = createNode(key);
    int index2 = hashFunction1(temp->key);
    if(table2[index2] == NULL){
      table2[index2] = createNode(temp->key);
    }
    else{
      node *temp2 = table2[index2];
      table2[index2] = NULL;
      table2[index2] = createNode(temp->key);
      x++;
      insertItemCuckoo(table2[index2]->key);
    }
  }
}


void HashTable::printTable(){
  cout<<"Table 1:"<<endl;
  for(int i = 0; i < tableSize; i++){
    cout<<i<<" || ";
    node *temp = table1[i];
    if(temp != NULL){
      cout<<table1[i]->key;
    }
    cout<<endl;
  }
  cout<<"Table 2:"<<endl;
  for(int j = 0; j < tableSize; j++){
    cout<<j<<" || ";
    if(table2[j] != NULL){
      cout<<table2[j]->key;
    }
    cout<<endl;
  }
}

node* HashTable::Lookup(int key){
  int index1 = hashFunction0(key);
  int index2 = hashFunction1(key);
  if(table1[index1]->key == key){
    return table1[index1];
  }
  else if(table2[index2]->key == key){
    return table2[index2];
  }
  else{
    cout<<"Value not found."<<endl;
    return NULL;
  }

}

void HashTable::Delete(int key){
  int index1 = hashFunction0(key);
  int index2 = hashFunction1(key);
  if(table1[index1]->key == key){
    delete table1[index1];
    table1[index1] = NULL;
  }
  else if(table2[index2]->key == key){
    delete table2[index2];
    table2[index2] = NULL;
  }
  else{
    cout<<"Value not found."<<endl;
    return;
  }
}
