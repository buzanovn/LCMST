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

int Graph::getNumVerticesWithDeg(int deg) {
    int sum = 0;
    for (auto &i : this->getDegreeList()) {
        if (i == deg) {
            sum += 1;
        }
    }
    return sum;
}

int Graph::getNumLeaves() {
    return this->getNumVerticesWithDeg(1);
}

std::vector<int> Graph::getDegreeList() {
    std::vector<int> deg(getNumVertices(), 0);
    for (auto &i : this->edges) {
        deg[i.getLv()] += 1;
        deg[i.getRv()] += 1;
    }
    return deg;
};

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
    adjacencyList.resize(n * (n - 1) / 2);
    f.close();
}

int Graph::addEdge(int &lV, int &rV) {
    auto e = Edge(lV, rV, this->vDistance(lV, rV));
    edges.push_back(e);
    adjacencyList[lV].push_back(rV);
    adjacencyList[rV].push_back(lV);
    return e.getWeight();
}


bool Graph::hasCycles() {
    std::vector<bool> discovered;
    discovered.resize(this->getNumVertices());
    return this->hasCyclesDFS(0, discovered, -1);
};

bool Graph::hasCyclesDFS(int v, std::vector<bool> &discovered, int pV) {
    discovered[v] = true;
    for (int aV : this->adjacencyList[v]) {
        if (!discovered[aV]) {
            if (hasCyclesDFS(aV, discovered, v)) {
                return true;
            }
        } else if (aV != pV) {
            return true;
        }
    }
    return false;
}

void Graph::addVertex(int x, int y) {
    auto v = Vertex(x, y);
    vertices.push_back(v);
}

int Graph::getWeight() {
    int sum = 0;
    for (auto e : edges) {
        sum += e.getWeight();
    }
    return sum;
}

Graph::Graph(const Vertices& vertices) {
    for (auto v : vertices) {
        this->vertices.push_back(v);
    }
    adjacencyList.resize(vertices.size() * (vertices.size() - 1) / 2);
}

Vertices Graph::getVertices() {
    return this->vertices;
}

Edges Graph::getEdges() {
    return this->edges;
};