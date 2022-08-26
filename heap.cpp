#include "hash.h"
#include "heap.h"
#include <iostream>
#include <stdio.h> 
#include <string> 

using namespace std;

heap::heap(int capacity) : capacity{capacity}, mapIdNode{capacity * 2}, currentSize{0} //make a hashtable which can handle capacity of heap
{
    data.resize(capacity+1); //data vector w size capacity
}

//insert a node at the bottom of the tree, then percolate up until in right position
int heap::insert(const std::string &id, int key, void *pv){
    if(currentSize == capacity) //if filled return 1
    {
        return 1;
    }

    if(mapIdNode.contains(id)) //id is already in heap
    {
        return 2;
    }
    //if id not in heap and there is space left, increase current size and put in characteristics of node
    ++currentSize;
    int pos = currentSize;
    data[pos].id = id;
    data[pos].key = key;
    data[pos].pData = pv;
    mapIdNode.insert(id, &data[pos]); //insert the id at the end, and it then has a pointer
    percolateUp(pos);    //then we percolate up    
    return 0;
}

int heap::setKey(const std::string &id, int key){
    if(!(mapIdNode.contains(id)))
    {
        return 1; 
    }

    int pos = getPos(static_cast<node*>(mapIdNode.getPointer(id))); //get the position of item
    data[pos].key = key;
    if(pos != 1 && data[pos].key< data[pos/2].key) //if we are less than parent and not at root, perc up
    {
        percolateUp(pos); 
    }
    else
    {
        percolateDown(pos);
    }

    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if(currentSize == 0) //nothing to be deleted
    {
    return 1;
    }
    //node characteristics of min at data[1]
    if(pId)
    {
        *pId= data[1].id;
    }
    if(pKey)
    {
        *pKey= data[1].key;
    }
    if(ppData)
    {
        {*(static_cast<void **> (ppData)) = data[1].pData;}
    }
    mapIdNode.remove(data[1].id); //remove it
    data[1] = data[currentSize]; //swap with last element
     
    percolateDown(1); //percolate down from root
    data[currentSize] = node(); //last node empty
    --currentSize; 
    return 0; 
}

int heap::remove(const std::string &id, int *pKey, void *ppData){

    if(!mapIdNode.contains(id))
        {
            return 1;
        } 
    int pos = getPos(static_cast<node*>(mapIdNode.getPointer(id)));
    if(pKey)
    {
        *pKey= data[pos].key;
    }
    if(ppData)
    {
            *(static_cast<void **> (ppData)) = data[pos].pData;
    }
    node minItem = data[pos];

    mapIdNode.remove(minItem.id);
    data[pos] = data[currentSize];
    mapIdNode.setPointer(data[pos].id, &data[pos]);
    --currentSize;

    if(pos != 1 && data[pos].key < data[pos/2].key)
        {
            percolateUp(pos);
        }
    else
        {
            percolateDown(pos);
        }

    return 0;  
}

//getPos, percolateUp, percolateDown from textbook
int heap::getPos(node *pn) 
{
    int pos = pn - &data[0];
    return pos;
}

void heap::percolateUp(int pos)
{
    data[0] = (data[pos]); //placeholder

    for(; data[0].key < data[pos/2].key; pos /= 2)
    {
        data[pos] = (data[pos/2]);
        mapIdNode.setPointer(data[pos].id, &data[pos]);
    }

    data[pos] = data[0];
    mapIdNode.setPointer(data[pos].id, &data[pos]);
}

void heap::percolateDown(int pos)
{
    int child{0};
    data[0] = data[pos]; 

    for(; pos * 2 <= currentSize; pos = child)
    {
        child = pos * 2;
        if(child != currentSize && data[child+1].key < data[child].key)
        {
            ++child;
        }  
        if(data[child].key < data[0].key)
        {
            data[pos] = data[child];
            mapIdNode.setPointer(data[pos].id, &data[pos]);
        }
        else
            break;
    }

    data[pos] = data[0];
    mapIdNode.setPointer(data[pos].id, &data[pos]);
}


