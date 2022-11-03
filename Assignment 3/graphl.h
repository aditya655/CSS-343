#include "nodedata.h"
#include<fstream>
#include<iostream>

using namespace std;

int const MAXNODES_L = 101;

class GraphL{
    private:
    int size;
    struct EdgeNode;
    struct GraphNode{
        EdgeNode* edgeHead;
        NodeData* data;
        bool visited;
    };

    GraphNode nodeArray[MAXNODES_L];

    struct EdgeNode{
        int adjGraphNode;
        EdgeNode* nextEdge;
    };

    void makeEmpty();
    void depthFirstSearchHelper(int v);

    public: 
    GraphL();
    ~GraphL();

    void buildGraph(ifstream&);
    void depthFirstSearch();
    void displayGraph();
};