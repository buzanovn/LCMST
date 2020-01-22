#include "Graph.h"

size_t Graph::getNumVertices() {
    return this->vertices.size();
}

size_t Graph::getNumEdges() {
    return this->edges.size();
}

double Graph::vAngle(int lV, int rV) {
    return vertexAngle(this->vertices[lV], this->vertices[rV]);
}

int Graph::vDistance(int lV, int rV) {
    return vertexDistance(this->vertices[lV], this->vertices[rV]);
};

int Graph::getNumLeafs() {
    std::vector<int> pow_v(getNumVertices(), 0);
    for (auto &i : this->edges) {
        pow_v[i.getLv()] += 1;
        pow_v[i.getRv()] += 1;
    }

    int sum = 0;
    for (auto &i : pow_v) {
        if (i == 1) {
            sum += 1;
        }
    }
    return sum;
}

Graph::Graph(const char *fPath) {
    std::fstream f;
    f.open(fPath);
    int n;
    f >> n;
    int x, y;
    for (int i = 0; i < n; i++) {
        f >> x;
        f >> y;
        addVertex(x, y);
    }
    f.close();
}

int Graph::addEdge(int &lV, int &rV) {
    auto e = Edge(lV, rV, this->vDistance(lV, rV));
    edges.push_back(e);
    return e.getWeight();
}

void Graph::addVertex(int x, int y) {
    auto v = Vertex(x, y);
    vertices.push_back(v);
};