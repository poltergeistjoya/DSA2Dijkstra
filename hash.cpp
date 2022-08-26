#include "hash.h"
#include <iostream>

using namespace std;
int primes[] = {11, 100003, 200003, 400009, 800011, 1600033, 3200003, 6400013};
unsigned int hashTable::getPrime(int size)
{
    unsigned int prime;
    for (int i = 0; i < sizeof(primes) / sizeof(int); i++)
    {
        if (primes[i] >= (size * 2))
        {
            prime = primes[i];
            break;
        }
    }
    return prime;
}
// hashtable constructor
hashTable::hashTable(int size)
{
    filled = 0;
    capacity = getPrime(size);
    data.resize(capacity); //resizes data to be size allocated by getPrime
    for(int i = 0; i <capacity; i++){
        data[i].key = "";
        data[i].isOccupied = false;
        data[i].isDeleted = false;
        data[i].pv = nullptr;
    }
}
//hashing function
int hashTable::hash(const std::string &key)
{
    unsigned int value = 0;
    char ch;
    for (int i = 0; i < key.length(); i++)
    {
        ch = key[i];
        value = 37 * value + ch;
    }
    return value % capacity; //index from 0->capacity
}

//findPos func to search for item with specified key. position if found, -1 otherwise
int hashTable::findPos(const std::string &key)
{
    int pos = hash(key); //hash item first
    //sometimes items not put in the hash pos, need to search until found
    while(data[pos].isOccupied) //if the key position is occupied, give pos
    {
        if(!data[pos].isDeleted && data[pos].key == key) //if not lazily deleted and key matches give pos, if not then traverse
        {
            return pos;
        }
        if (pos == capacity-1) 
        {
            pos = 0;
        }
        else
        {
            ++pos;
        }
    }
        
    return -1; //if key not found, return -1
}


//Check if specified key in hash table
//If so, return true; otherwise, resturn false
bool hashTable::contains(const std::string &key)
{
    if(findPos(key)== -1){ //if no position was found, it is not in the hash table
        return false;
    }
    else
    {
        return true;
    }
}
//Insert function using linear probing
//0 sucessful insert
//1 key already exists in hashtable
//2 rehash fails
int hashTable::insert(const std::string &key, void *pv)
{
    if(capacity <= filled*2)
    {
        if(rehash()==false)
        {
            return 2;
        }
    }
    int pos = hash(key); //if the pos is empty it will automatically be inserted;
    while (data[pos].isOccupied == true)
    {
        if (data[pos].key == key && !data[pos].isDeleted)
        {
        return 1;
        }
        if (pos==capacity-1){ //need to make circular so beginning entries are checked for emptiness too
            pos=0;
        }
        else{
            ++pos;
        }
    }
    //update hashTable characteristics
    ++filled; 
    data[pos].key = key;
    data[pos].isOccupied = true; 
    data[pos].isDeleted = false;
    data[pos].pv = pv;
    return 0;
}
//if filled is 1/2 of size, resize
//true on success, false if memory allocation fail
bool hashTable::rehash()
{
    int newSize = getPrime(capacity);
    std::vector<hashItem> oldData = data; //save old entries
    //try to make new hash table w resize, if fail false
    try
    {
        data.resize(newSize);
        for(int i = 0; i<data.size(); i++)//mkae sure new vector is empty
        {
            data[i].isOccupied = false;
            data[i].key = "";
            data[i].isDeleted = false;
            data[i].pv = nullptr;
        }
    }
    catch (const int bad_alloc)
    {
        return false;
    }
    //make new hash table
    filled = 0;
    capacity = newSize;

    for(int i = 0;i<oldData.size();i++)
    {//only want to reinsert data w values, not empty strings
        if(oldData[i].isOccupied && !oldData[i].isDeleted)
        {
            insert(oldData[i].key, oldData[i].pv);
        }
    }
    return true;
}

int hashTable::setPointer(const std::string &key, void *pv){
      int pos= findPos(key); 
      if(pos==-1){
          return 1;
      }
      else {
          data[pos].pv = pv;
            return 0;
      }
}

  // Get the pointer associated with the specified key.
  // If the key does not exist in the hash table, return nullptr.
  // If an optional pointer to a bool is provided,
  // set the bool to true if the key is in the hash table,
  // and set the bool to false otherwise.
  void *hashTable::getPointer(const std::string &key, bool *b){
      int pos = findPos(key); 
      if(pos == -1){
          if (b){
            *b = false;
          }
          return nullptr;
      }
        else {
        if (b){
            *b = true;
        }
        return data[pos].pv; 
       }
    }

bool hashTable::remove(const std::string &key)
{
    int pos{findPos(key)};

    if(pos == -1)
        {return false;}
    else
    {
        data[pos].isDeleted = true;
        return true;
    }
}
