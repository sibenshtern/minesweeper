#include "Graph_lib/Simple_window.h"
#include "minesweeper.h"

using namespace Graph_lib;

Minesweeper::Minesweeper(Point xy)
        : Window{xy, Board::size, Board::size, "Minesweepers"}, board{Point{0, 0}} {
    size_range(Board::size, Board::size, Board::size, Board::size);

    board.attach(*this);
}