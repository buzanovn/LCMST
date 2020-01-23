#ifndef LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_SOLVER_H
#define LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_SOLVER_H

#include "Graph.h"

class Solver {
private:
    Graph *g;
    Graph *currentGraph;
    Graph *bestGraph;
    int leafConstraint;
    Clusters clusters;
    int clusterCount;
    double angle;
public:
    explicit Solver(Graph *graph);

    void solve(Graph *g);

    int removeLastVertexFromCluster(int vIdx, int clusterIdx);

    void conquer(int startVertexIdx, int lClusterIdx, int rClusterIdx);

    void divide(int centerVertexIdx);

    void report(const char* fPath);

    void reportIterationScore();

    int iteration;

    void setClusterCount(int cc);
};


#endif //LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_SOLVER_H
