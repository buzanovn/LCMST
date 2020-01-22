#ifndef LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_CLUSTER_H
#define LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_CLUSTER_H

#include <utility>
#include <vector>

class ClusterVertex {
public:
    int dist;
    int vIdx;

    ClusterVertex(int dist, int vIdx) {
        this->dist = dist;
        this->vIdx = vIdx;
    }

    ClusterVertex() {
        this->dist = -1;
        this->vIdx = -1;
    };
};

inline bool operator<(const ClusterVertex &cv1, const ClusterVertex &cv2) {
    return std::pair<int, int>(cv1.dist, cv1.vIdx) < std::pair<int, int>(cv2.dist, cv2.vIdx);
}

typedef std::vector<ClusterVertex> Cluster;
typedef std::vector<Cluster> Clusters;

inline void clearClusters(Clusters clusters) {
    for (auto &c : clusters) {
        c.clear();
    }
}

#endif //LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_CLUSTER_H
