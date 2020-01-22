#include <algorithm>
#include <iostream>
#include "Solver.h"

Solver::Solver(Graph *graph) {
    this->g = graph;
    this->cost = 0;
    this->iteration = 1;

    this->leafConstraint = this->g->getNumVertices() / 10;

    int l = 3;
    while (l < this->leafConstraint) {
        l <<= 1;
    }
    l >>= 1;
    this->clusterCount = l;
    this->angle = 2 * M_PI / l;
    this->clusters.resize(l);
}

void Solver::solve() {
    this->divide(0);
    this->reportIterationScore();
    this->iteration += 1;
    int minClusterIdx = 0;
    int minimalCost = cost;
    for (size_t i = 1; i < g->getNumVertices(); ++i) {
        divide(i);
        this->reportIterationScore();
        this->iteration += 1;
        if (cost < minimalCost) {
            minimalCost = cost;
            minClusterIdx = i;
        }
    }
    divide(minClusterIdx);
    this->g_solution = this->g;
}

int Solver::removeLastVertexFromCluster(int vIdx, int clusterIdx) {
    int lastVertexIdx = this->clusters[clusterIdx].back().vIdx;
    int weight = this->g->addEdge(vIdx, lastVertexIdx);
    this->cost += weight;
    this->clusters[clusterIdx].pop_back();
    return lastVertexIdx;
}

void Solver::conquer(int startVertexIdx, int lClusterIdx, int rClusterIdx) {
    if (lClusterIdx == rClusterIdx) {
        int prevIdx = startVertexIdx;
        while (!this->clusters[lClusterIdx].empty()) {
            prevIdx = this->removeLastVertexFromCluster(prevIdx, lClusterIdx);
        }
        return;
    }
    int minClusterIdx = -1;
    for (int i = lClusterIdx; i <= rClusterIdx; i++) {
        if (minClusterIdx != -1) {
            if (this->clusters[i].empty()) {
                continue;
            }
            int fromStartToClusterCentre = this->g->vDistance(startVertexIdx, this->clusters[i].back().vIdx);
            int fromStartToMinClusterCentre = this->g->vDistance(startVertexIdx,
                                                                 this->clusters[minClusterIdx].back().vIdx);
            if (fromStartToClusterCentre < fromStartToMinClusterCentre) {
                minClusterIdx = i;
            }
        } else {
            if (!this->clusters[i].empty()) {
                minClusterIdx = i;
            }
        }
    }
    if (minClusterIdx == -1) return;
    startVertexIdx = this->removeLastVertexFromCluster(startVertexIdx, minClusterIdx);
    conquer(startVertexIdx, lClusterIdx, (lClusterIdx + rClusterIdx) / 2);
    conquer(startVertexIdx, (lClusterIdx + rClusterIdx) / 2 + 1, rClusterIdx);
}


void Solver::divide(int centerVertexIdx) {
    this->cost = 0;
    this->g->edges.clear();
    clearClusters(this->clusters);
    for (size_t i = 0; i < this->g->getNumVertices(); i++) {
        if ((int) i == centerVertexIdx) {
            continue;
        }
        int clusterIdx = this->g->vAngle(i, centerVertexIdx) / this->angle;
        auto cV = ClusterVertex(this->g->vDistance(i, centerVertexIdx), i);
        this->clusters[clusterIdx].push_back(cV);
    }
    for (auto &c : this->clusters) {
        std::sort(c.rbegin(), c.rend());
    }
    int step = this->clusterCount / 3;
    for (int i = 0; i < this->clusterCount; i += step) {
        this->conquer(centerVertexIdx, i, i + step - 1);
    }
}

void Solver::report(const char *fPath) {
    std::ofstream outputFile(fPath);
    outputFile << "c Вес дерева = " << this->cost
               << ", число листьев = " << this->g_solution->getNumLeafs()
               << ',' << std::endl;
    outputFile << "c число вершин и ребер" << std::endl;
    outputFile << "p edge " << this->g_solution->getNumVertices()
               << ' ' << this->g_solution->getNumEdges()
               << std::endl;
    outputFile << "c ребра" << std::endl;
    for (auto &e : this->g_solution->edges) {
        outputFile << "e " << e.getLv() + 1
                   << ' ' << e.getRv() + 1
                   << std::endl;
    }
    outputFile.close();
}

void Solver::reportIterationScore() {
    std::cout << "Iteration: " << this->iteration
              << " Score: " << this->cost
              << std::endl;
}
