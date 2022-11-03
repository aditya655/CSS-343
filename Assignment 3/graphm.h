#include "nodedata.h"
#include<fstream>
#include<iostream>

using namespace std;

int const MAXNODES_M = 101;

class GraphM{
    private:
    struct TableType{
        bool visited;
        int dist;
        int path;
    };
    NodeData data[MAXNODES_M];
    int C[MAXNODES_M][MAXNODES_M];
    int size;
    TableType T[MAXNODES_M][MAXNODES_M];
    
    void findData(int from, int to);
    void findPath(int from, int to);

    public: 

    GraphM();

    void buildGraph(ifstream&);
    void findShortestPath();
    bool insertEdge(int from, int to, int dist);
    bool removeEdge(int from, int to);
    void display(int from, int to);
    void displayAll();
};
