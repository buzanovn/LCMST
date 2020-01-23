#include <algorithm>
#include <iostream>
#include "Solver.h"
#include <cassert>

#define MN 2
#define LEAVES_NUMBER_CONSTRAINT(numVertex) (int) floor((numVertex) / 10.0)
#define CLUSTER_COUNT(constraint) (int) (MN * pow(2, floor(log2((constraint) - MN) - 1)))

Solver::Solver(Graph *graph) {
    this->g = graph;
    this->bestGraph = this->currentGraph = nullptr;
    this->iteration = 1;
    this->leafConstraint = LEAVES_NUMBER_CONSTRAINT(this->g->getNumVertices());
    this->setClusterCount(CLUSTER_COUNT(this->leafConstraint));
}

void Solver::setClusterCount(int cc) {
    this->clusterCount = cc;
    this->angle = 2 * M_PI / this->clusterCount;
    this->clusters.resize(this->clusterCount);
}

void Solver::solve(Graph *graph) {
    this->currentGraph = new Graph(graph->getVertices());
    this->divide(0);
    this->bestGraph = this->currentGraph;
    this->reportIterationScore();
    this->iteration += 1;
    int minWeight, curWeight;
    minWeight = currentGraph->getWeight();
    for (size_t i = 1; i < currentGraph->getNumVertices(); i++) {
        this->currentGraph = new Graph(graph->getVertices());
        divide(i);
        curWeight = currentGraph->getWeight();
        this->reportIterationScore();
        this->iteration += 1;
        if (curWeight < minWeight) {
            bestGraph = currentGraph;
        }
    }

    // Make sure it is a tree
    assert(!this->bestGraph->hasCycles());

    // Make sure the tree is binary
    for (int d : this->bestGraph->getDegreeList()) {
        assert(d <= 3);
    }

    // Make sure all edges are unique
    for (size_t i = 0; i < this->bestGraph->getNumEdges(); i++) {
        for (size_t j = i + 1; j < this->bestGraph->getNumEdges(); j++) {
            assert(!(this->bestGraph->getEdges()[i] == this->bestGraph->getEdges()[j]));
        }
    }
}

int Solver::removeLastVertexFromCluster(int vIdx, int clusterIdx) {
    int lastVertexIdx = this->clusters[clusterIdx].back().vIdx;
    this->currentGraph->addEdge(vIdx, lastVertexIdx);
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
            int fromStartToClusterCentre = this->currentGraph->vDistance(startVertexIdx, this->clusters[i].back().vIdx);
            int fromStartToMinClusterCentre = this->currentGraph->vDistance(startVertexIdx,
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
    clearClusters(clusters);
    for (size_t i = 0; i < this->currentGraph->getNumVertices(); i++) {
        if ((int) i == centerVertexIdx) {
            continue;
        }
        int clusterIdx = (int) (this->currentGraph->vAngle(i, centerVertexIdx) / this->angle);
        this->clusters[clusterIdx].push_back(ClusterVertex(this->currentGraph->vDistance(i, centerVertexIdx), i));
    }
    for (auto &c : this->clusters) {
        std::sort(c.rbegin(), c.rend());
    }
    int step = this->clusterCount / MN;
    for (int i = 0; i < this->clusterCount; i += step) {
        this->conquer(centerVertexIdx, i, i + step - 1);
    }
}

void Solver::report(const char *fPath) {
    std::ofstream outputFile(fPath);
    outputFile << "c Вес дерева = " << this->bestGraph->getWeight()
               << ", число листьев = " << this->bestGraph->getNumLeaves()
               << ',' << std::endl;
    outputFile << "c число вершин и ребер" << std::endl;
    outputFile << "p edge " << this->bestGraph->getNumVertices()
               << ' ' << this->bestGraph->getNumEdges()
               << std::endl;
    outputFile << "c ребра" << std::endl;
    for (auto &e : this->bestGraph->getEdges()) {
        outputFile << "e " << e.getLv() + 1
                   << ' ' << e.getRv() + 1
                   << std::endl;
    }
    outputFile.close();
}

void Solver::reportIterationScore() {
    std::cout << "Iteration: " << this->iteration
              << " Score: " << this->currentGraph->getWeight()
              << std::endl;
}
