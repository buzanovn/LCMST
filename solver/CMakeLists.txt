cmake_minimum_required(VERSION 3.12)
project(leaf-constrained-minimum-binary-spanning-tree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++14")

add_executable(
        leaf-constrained-minimum-binary-spanning-tree
        main.cpp lib/Solver.cpp lib/Solver.h lib/Graph.cpp lib/Graph.h lib/Vertex.h lib/Edge.h lib/Cluster.h
)