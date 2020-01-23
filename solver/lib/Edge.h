#ifndef LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_EDGE_H
#define LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_EDGE_H

#include <vector>

class Edge {
private:
    int lv;
    int rv;
    int weight;
public:
    [[nodiscard]] int getLv() const {
        return lv;
    }

    [[nodiscard]] int getRv() const {
        return rv;
    }

    [[nodiscard]] int getWeight() const {
        return weight;
    }

    Edge(int lv, int rv, int weight) {
        this->lv = lv;
        this->rv = rv;
        this->weight = weight;
    }

    bool operator==(Edge& o) const {
        return (this->lv == o.lv && this->rv == o.rv) || (this->rv == o.lv && this->lv == o.rv);
    }
};

typedef std::vector<Edge> Edges;
#endif //LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_EDGE_H
