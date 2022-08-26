#ifndef GRAPH_H
#define GRAPH_H

#include "heap.h"
#include "hash.h"
#include <list>  

using namespace std;
class graph
{
private:
    class node
    {
    public: 

        class edge
        {
        public: 
            int cost;
            node* dest;

            edge(int cost, node* destination): cost{cost}, dest{destination} {}
        };

        string id;
        int pathLength;
        list<edge> adjList;
        node *prevVert;

        node(const string &id): id{id}, pathLength{-1}, prevVert{nullptr} {}
        void printPath(ofstream &out) const;
        
    };

    list<node*> vertexList; //each node will have a vist of a vertex and pointer(s)
    hashTable hashVert; 

public:
    graph(); //constructor ,,,this will load input file and make the graph 
    void dijkstra(const string &);
    bool isVert(const string &);
    void printGraphPaths(ofstream &);
};

#endif //GRAPH_H