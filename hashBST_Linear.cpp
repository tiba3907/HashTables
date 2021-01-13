// CPP program to implement hashing with chaining
#include<iostream>
#include "hashBST_Linear.hpp"
#define TABLE_SIZE  10009
using namespace std;

node* HashTable::createNode(int key, node* next)
{
    node* nw = new node;
    nw->key = key;
    nw->next = next;
    nw->left = NULL;
    nw->right = NULL;
    return nw;
}


HashTable::HashTable(int bsize)
{
    table = new node*[TABLE_SIZE];
    for(int i=0;i<TABLE_SIZE;i++)
        table[i] = NULL;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(int key)
{
    return (key % TABLE_SIZE);
}

//function to search linear
node* HashTable::searchItemLinear(int key)
{
    //Compute the index by using the hash function
    int count=0;
    int index = hashFunction(key);
      //finding the node with given key

      while(table[index] != NULL)
      {
           if(count++>TABLE_SIZE)  //to avoid infinite loop
              return NULL;
          //if node found return its value
          if(table[index]->key == key)
              return table[index];
          index++;
          index %=TABLE_SIZE;
        }

}

//function to search BST
node* searchItemBSTHelper(node* root,int key){

//base case
  if(root==NULL || root->key==key) return root;
// If the key  is smaller than the root's key, then it lies in left subtree
    else if(key<(root->key))

      return searchItemBSTHelper(root->right,key);

      // If the key is greater than the root's key, then it lies in right subtree
    else if(key>(root->key))
    {
      return searchItemBSTHelper(root->left,key);
    }
    return root;
}

node* HashTable::searchItemBST(int key){
  int index =hashFunction(key);
  node* temp = new node;
  temp=searchItemBSTHelper(table[index],key);
  return temp;
}



//function to insert linear
void HashTable::insertItemLinear(int key)
{
  int count = 0;
  node* temp =createNode(key, NULL);
  int index = hashFunction(key);

        //find next free space
        while(table[index] != NULL && table[index]->key != key
               && table[index]->key != -1  && count++<TABLE_SIZE)
        {
            index++;
            index %= TABLE_SIZE; //to loop all the way through the table
        }
        if(table[index] == NULL)
        {
          table[index] = temp;
        }

}

node* addNodeHelper(node* root,int key){
  //base case
  node* nw = new node;
  nw->key = key;
  nw->next = NULL;
  nw->left = NULL;
  nw->right = NULL;
  if(root == NULL || root->key == -1){
    root = nw;
    return root;
  }
  // If the key to be added is smaller than the root's key, then it lies in left subtree
  else if(root->key > key)
    root->right =addNodeHelper(root->right,key);

  // If the key to be added is greater than the root's key, then it lies in right subtree
  else if(root->key < key){
    root->left = addNodeHelper(root->left,key);
  }
  return root;
}

void HashTable::insertItemBST(int key)
{
  int index = hashFunction(key);
      if(table[index]==NULL){
        table[index] =createNode(key, NULL);
      }

      else{
        addNodeHelper(table[index],key);
      }
}

void HashTable::deleteNodeLinear(int key){
  int count=0;
  int index = hashFunction(key);
    //finding the node with given key
    while(table[index] != NULL)
    {    int count =0;
         if(count++>TABLE_SIZE)  //to avoid infinite loop
            cout<<"key not in table"<<endl;
        //if node found set key = -1
        if(table[index]->key == key){
            table[index]->key = -1;
            return;
          }
        index++;
        index %=TABLE_SIZE;
      }
}
node * minValueNode(node* root)
{
    node* current = root;

    // loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

//takes in root
node* deleteNodeHelper(node* root, int key)
{
    // base case
    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if (key < root->key)
        root->right = deleteNodeHelper(root->right, key);

    // If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if (key > root->key)
        root->left = deleteNodeHelper(root->left, key);

    // if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            node *temp = new node;
            temp=root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = new node;
            temp = root->left;
            delete root;
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        node* temp =  new node;
        temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNodeHelper(root->right, temp->key);
    }
    return root;
  }
//deletes node at index using recursion
void HashTable::deleteNodeBST(int key){
  int index= hashFunction(key);
  deleteNodeHelper(table[index],key);

}
//display Hashtable using linear Probing
void HashTable::printTableLinear()
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i <<"|| ";
        if(table[i]!=NULL && table[i]->key!=-1)
          cout<<table[i]->key;
        cout<<endl;
    }

 }


//Printing nodes
 void printNodeHelper(node * root){
     if(root==NULL  || root->key == -1) return;
     printNodeHelper(root->left);
     cout<<root->key<<" ";
     printNodeHelper(root->right);
 }

 //display Hashtable using BST chaining
 void HashTable::printTableBST()
 { //goes to each index and then goes down the binary search tree on that index
   for (int i = 0; i < TABLE_SIZE; i++) {
       cout << i <<"|| ";
       printNodeHelper(table[i]);
       cout<<endl;
     }
 }
