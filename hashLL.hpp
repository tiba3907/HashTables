#ifndef HASHLL_HPP
#define HASHLL_HPP

#include <string>
#include <cmath>
#include <ctime>
using namespace std;

struct node
{
    int key;
    struct node* next;
};

class HashTable
{
private:
    int tableSize;  // No. of buckets (linked lists)

    // Pointer to an array containing buckets
    node* *table;
    node* createNode(int key, node* next);
public:
    HashTable(int bsize);  // Constructor

    // hash function to map values to key
    unsigned int hashFunction1(int key);
    unsigned int hashFunction2(int key);

    // inserts a key into hash table
    void insertItemLL(int key);

    void printTable();

    node* Lookup(int key);
    void Delete(int key);
};

#endif
