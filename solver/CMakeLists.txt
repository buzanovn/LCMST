cmake_minimum_required(VERSION 3.12)
project(cluster-solver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_VERBOSE_MAKEFILE on )

add_executable(
        cluster-solver
        main.cpp lib/Solver.cpp lib/Solver.h lib/Graph.cpp lib/Graph.h lib/Vertex.h lib/Edge.h lib/Cluster.h
)
target_link_libraries(${PROJECT_NAME} stdc++fs)