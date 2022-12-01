#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#include "Graph_lib/Simple_window.h"
#include "board.h"

using Graph_lib::Point;
using Graph_lib::Address;

class Minesweeper : Graph_lib::Window {
public:
    Minesweeper(Point xy);
    // int handle(int event) override;

    // ~Minesweeper() override = default;
private:
    Board board;
    // void clicked(Cell &c);
};


#endif //MINESWEEPER_MINESWEEPER_H
