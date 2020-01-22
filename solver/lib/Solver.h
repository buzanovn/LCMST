#ifndef LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_SOLVER_H
#define LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_SOLVER_H

#include "Graph.h"

class Solver {
private:
    Graph *g;
    int cost;
    int leafConstraint;
    Clusters clusters;
    int clusterCount;
    double angle;

    Graph* g_solution;
public:
    explicit Solver(Graph *graph);

    void solve();

    int removeLastVertexFromCluster(int vIdx, int clusterIdx);

    void conquer(int startVertexIdx, int lClusterIdx, int rClusterIdx);

    void divide(int centerVertexIdx);

    void report(const char* fPath);

    void reportIterationScore();

    int iteration;
};


#endif //LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_SOLVER_H
