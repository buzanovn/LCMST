#ifndef LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_EDGE_H
#define LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_EDGE_H

#include <vector>

class Edge {
private:
    int lv;
    int rv;
    int weight;
public:
    int getLv() const {
        return lv;
    }

    int getRv() const {
        return rv;
    }

    int getWeight() const {
        return weight;
    }

    Edge(int lv, int rv, int weight) {
        this->lv = lv;
        this->rv = rv;
        this->weight = weight;
    }
};

typedef std::vector<Edge> Edges;
#endif //LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_EDGE_H
