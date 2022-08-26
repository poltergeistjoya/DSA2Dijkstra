#include "graph.h"
#include <iostream> 
#include <fstream> 
#include <chrono>
using namespace std;

graph::graph(): hashVert{50000}//graph constructor
{
    string inFile;
    cout << "Enter graph input file: ";
    cin >> inFile;
    ifstream input;
    input.open(inFile, ifstream::in); 
    if(!input.is_open()){
            fprintf(stderr, "ERROR opening input file: %s\n", strerror(errno));
            cout << "please enter a valid input file.";
        }
    string v1, v2, costStr;
    int cost;
    //now make the graph and load in each edge in input file
    while(input >> v1) //while there is valid input
    {
        input >> v2;
        input >> costStr;
        cost = stoi(costStr);

        node *vp1{nullptr};
        if(!hashVert.contains(v1)) //if node doesn't exist in Hash table, put in
        {
            vp1 = new node{v1};
            vertexList.push_back(vp1); //add to end of vector
            hashVert.insert(v1, vp1);
        }
        else //if it does exist get pointer
        {
            vp1 = static_cast<node*>(hashVert.getPointer(v1));
        }

        node *vp2{nullptr};
        if(!hashVert.contains(v2)) //if node doesn't exist in Hash table, put in
        {
            vp2 = new node{v2};
            vertexList.push_back(vp2); 
            hashVert.insert(v2, vp2);
        }
        else //if it does exist get pointer associated w it
        {
            vp2 = static_cast<node*>(hashVert.getPointer(v2));
        }
        //after the nodes are added to the graph and a new edge is made, add v2 and cost from v1->v2 to v1's adjacency list
        vp1->adjList.push_back(node::edge{cost, vp2}); //v1's pointer now will also "point" to new v2
    }
}

void graph::dijkstra(const string &startV)
{   //take vertices and make heap for the const time functionality of deletemin
    heap heapVert(vertexList.size());
    //initializations for first vertex
    node *startVP = static_cast<node *>(hashVert.getPointer(startV));
    startVP->pathLength = 0;
    heapVert.insert(startV, 0, startVP); 

    while(1)
    {
        //initializations 
        string vID{""}; 
        int length{0};
        void* vptr{nullptr};
        //as long as heap has size greater than 0, we look at each edge
        if(heapVert.deleteMin(&vID, &length, &vptr) != 1) 
        {
            node &vertex = *static_cast<node *>(vptr);
            for(const node::edge &edge : vertex.adjList)
            {
                node &dVert = *(edge.dest);
                // we save the first path that we find
                if(dVert.pathLength == -1) 
                {
                    dVert.pathLength = length + edge.cost;
                    dVert.prevVert = static_cast<node *>(vptr);
                    heapVert.insert(dVert.id, dVert.pathLength, &dVert);
                }
                //if we find a better path we rewrite 
                else  
                {
                    if(length + edge.cost < dVert.pathLength)
                    {
                        dVert.pathLength = length + edge.cost;
                        dVert.prevVert = static_cast<node *>(vptr);
                    }
                    heapVert.setKey(dVert.id, dVert.pathLength); 
                }
            }
        }
        else
            break; 
    }
}

bool graph::isVert(const string &v){
    return (hashVert.contains(v));
}

void graph::printGraphPaths(ofstream &out)
{

    for( const node *vertex : vertexList )
    {
        out << vertex->id << ": ";
        //if djikstra can't reach we do not get a path
        if(vertex->pathLength == -1) 
            out << "NO PATH\n";
        else //use printPath
        {
            out << vertex->pathLength << " [";
            vertex->printPath(out); 
            out << "]\n";
        }
    }
    
}

//if a previous vertex exists, we recurse until we can't and spit out id
void graph::node::printPath(ofstream &out) const
{
    if(prevVert) 
    {
        prevVert->printPath(out); 
        out << ", ";
    }
    out << id;
}

