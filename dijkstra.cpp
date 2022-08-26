
#include "graph.h"
#include <iostream> 
#include <fstream> 
#include <chrono>

using namespace std;
int main() {

    graph jDijkstra;
    string startV;
    do //make sure they enter a valid vertex
    {
        cout << "Enter name of starting vertex: ";
        cin >> startV;
    }
    while(!jDijkstra.isVert(startV));

    clock_t start = clock();
    jDijkstra.dijkstra(startV);
    clock_t end = clock();
    double time = ((double) (end - start)) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time << '\n';
    string outfile;
    cout << "Enter name of output file: ";
    cin >> outfile;
    ofstream(output);
    output.open(outfile);

    jDijkstra.printGraphPaths(output);
    output.close();
    return 0;
}