#ifndef HASHCUCKOO_HPP
#define HASHCUCKOO_HPP

#include <string>
#include <cmath>

using namespace std;

struct node
{
    int key;
};

class HashTable
{
private:
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    node* *table1;
    node* *table2;

    node* createNode(int key);
public:
    HashTable(int bsize);  // Constructor

    // hash function to map values to key
    unsigned int hashFunction0(int key);

    unsigned int hashFunction1(int key);

    // inserts a key into hash table
    void insertItemCuckoo(int key);

    void printTable();

    node* Lookup(int key);
    void Delete(int key);
};

#endif
