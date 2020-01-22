#include <vector>
#include <cmath>
#include <iostream>
#include <experimental/filesystem>
#include "lib/Solver.h"
#include "lib/Graph.h"

namespace fs = std::experimental::filesystem;

int processTask(const char *inFilePath, const char *outFilePath) {
    auto *g = new Graph(inFilePath);
    auto *s = new Solver(g);
    s->solve();
    s->report(outFilePath);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Provide input and output text files as the only two arguments" << std::endl;
        exit(1);
    }

    const char *in, *out;
    in = argv[1];
    out = argv[2];
    if (fs::is_directory(in)) {
        for (const auto & e : fs::directory_iterator(fs::path(in))) {
            processTask(e.path().c_str(), "zhopa.txt");
        }
    } else if (fs::is_regular_file(in) && fs::is_regular_file(out)) {
        return processTask(in, out);
    } else {
        std::cout << "Provide either two files or two directories" << std::endl;
        exit(1);
    }
}

