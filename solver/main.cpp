#include <vector>
#include <cmath>
#include <iostream>
#include <filesystem>
#include "lib/Solver.h"
#include "lib/Graph.h"

namespace fs = std::filesystem;

int processTask(const char *inFilePath, const char *outFilePath) {
    auto *g = new Graph(inFilePath);
    auto *s = new Solver(g);
    s->solve(g);
    s->report(outFilePath);
    delete g;
    delete s;
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Provide input and output text files as the only two arguments" << std::endl;
        exit(1);
    }

    fs::directory_entry in, out;
    in = fs::directory_entry(argv[1]);
    out = fs::directory_entry(argv[2]);
    if (in.is_directory()) {
        if (!out.exists()) {
            fs::create_directories(out);
        }
        for (const auto & inputFilePath : fs::directory_iterator(fs::path(in))) {
            fs::path outputFilePath = out / inputFilePath.path().filename();
            processTask(inputFilePath.path().c_str(), outputFilePath.c_str());
        }
    } else if (fs::is_regular_file(in) && fs::is_regular_file(out)) {
        return processTask(in.path().c_str(), out.path().c_str());
    } else {
        std::cout << "Provide either two files or two directories" << std::endl;
        exit(1);
    }
}

