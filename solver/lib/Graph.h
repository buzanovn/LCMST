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
private:
    Vertices vertices;
    Edges edges;
    std::vector<std::vector<int>> adjacencyList;

    bool hasCyclesDFS(int v, std::vector<bool> &discovered, int pV);

public:
    Vertices getVertices();

    Edges getEdges();

    size_t getNumVertices();

    size_t getNumEdges();

    int getNumLeaves();

    int getNumVerticesWithDeg(int deg);

    int addEdge(int &lV, int &rV);

    void addVertex(int x, int y);

    explicit Graph(const char *fPath);

    explicit Graph(const Vertices& vertices);

    double vAngle(int lV, int rV);

    int vDistance(int lV, int rV);

    int getWeight();

    std::vector<int> getDegreeList();

    bool hasCycles();
};


#endif //LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_GRAPH_H
