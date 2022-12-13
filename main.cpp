#include <iostream>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

#include "minesweeper.h"

using namespace Graph_lib;

int main() {
    try {
        Minesweeper win{Point{100, 100}};
        return gui_main();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "Oops, something went wrong..." << "\n";
    }
}