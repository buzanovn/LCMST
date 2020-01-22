#ifndef LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_VERTEX_H
#define LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_VERTEX_H

#include <cstdlib>
#include <vector>

class Vertex {
private:
    int x;
    int y;
public:
    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    Vertex(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

inline int vertexDistance(Vertex &v1, Vertex &v2) {
    return abs(v1.getX() - v2.getX()) + abs(v1.getY() - v2.getY());
}

inline double vertexAngle(Vertex &v1, Vertex &v2) {
    double a;
    a = atan2(v1.getY() - v2.getY(), v1.getX() - v2.getX());
    return a < 0 ? a + 2 * M_PI : 0;
}

typedef std::vector<Vertex> Vertices;

#endif //LEAF_CONSTRAINED_MINIMUM_BINARY_SPANNING_TREE_VERTEX_H
