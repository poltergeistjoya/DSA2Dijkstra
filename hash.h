#ifndef _HASH_H // precompiler directives
// if _HASH_H does not exist, then define it with this code
#define _HASH_H

#include <vector>
#include <string>

class hashTable {

 public:

  // The constructor initializes the hash table.
  // Uses getPrime to choose a prime number at least as large as
  // the specified size for the initial size of the hash table.
  hashTable(int size = 0);  //initialize to 50k (avg size of dictionary) X 2

  // Insert the specified key into the hash table.
  // If an optional pointer is provided,
  // associate that pointer with the key.
  // Returns 0 on success,
  // 1 if key already exists in hash table,
  // 2 if rehash fails.
  int insert(const std::string &key, void *pv = nullptr); //void pointer

  // Check if the specified key is in the hash table.
  // If so, return true; otherwise, return false.
  bool contains(const std::string &key); //search member function

  // Get the pointer associated with the specified key.
  // If the key does not exist in the hash table, return nullptr.
  // If an optional pointer to a bool is provided,
  // set the bool to true if the key is in the hash table,
  // and set the bool to false otherwise.
  void *getPointer(const std::string &key, bool *b = nullptr);

  // Set the pointer associated with the specified key.
  // Returns 0 on success,
  // 1 if the key does not exist in the hash table.
  int setPointer(const std::string &key, void *pv);

  // Delete the item with the specified key.
  // Returns true on success,
  // false if the specified key is not in the hash table.
  bool remove(const std::string &key);

 private:

  // Each item in the hash table contains:
  // key - a string used as a key.
  // isOccupied - if false, this entry is empty,
  //              and the other fields are meaningless.
  // isDeleted - if true, this item has been lazily deleted.
  // pv - a pointer related to the key;
  //      nullptr if no pointer was provided to insert.
  class hashItem {// hashItem - private nested class 
  public:
    std::string key;
    bool isOccupied;
    bool isDeleted;
    void *pv;
  };

  int capacity; // The current capacity of the hash table.
  int filled; // Number of occupied items in the table. //when filled is greater than 1/2 capacity- rehash
  std::vector<hashItem> data; // The actual entries are here.

  // The hash function.
  int hash(const std::string &key);

  // Search for an item with the specified key.
  // Return the position if found, -1 otherwise.
  int findPos(const std::string &key);

  // The rehash function; makes the hash table bigger.
  // Returns true on success, false if memory allocation fails.
  bool rehash(); //using capcity and filled

  // Return a prime number at least as large as size.
  // Uses a precomputed sequence of selected prime numbers.
  unsigned int getPrime(int size);
};

#endif //_HASH_H

//we will make hash.cpp - import hash.h and make all the attributes for the hash table
//we will also make main.cpp