#ifndef LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_GRAPH_H
#define LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_GRAPH_H


#include <fstream>
#include <cmath>
#include "Vertex.h"
#include "Edge.h"
#include "Cluster.h"

/**
 * Implementation of Graph structure, G = (V, E)
 */
class Graph {
public:
    /**
     * Vector of vertices V of graph G
     */
    Vertices vertices;
    /**
     * Vector of edges E of graph G
     */
    Edges edges;

    /**
     * Number of vertices
     * @return |V|
     */
    size_t getNumVertices();

    /**
     * Number of edges
     * @return |E|
     */
    size_t getNumEdges();

    /**
     * Number of leafs (vertices with deg(v) == 1)
     * @return
     */
    int getNumLeafs();

    int addEdge(int &lV, int &rV);

    void addVertex(int x, int y);

    explicit Graph(const char *fPath);

    double vAngle(int lV, int rV);

    int vDistance(int lV, int rV);
};


#endif //LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_GRAPH_H
