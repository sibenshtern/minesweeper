#include <iostream>

#include "Graph_lib/Simple_window.h"
#include "minesweeper.h"

using namespace Graph_lib;

Minesweeper::Minesweeper(Point xy)
        : Window{xy, Board::size, Board::size, "Minesweepers"},
        board{Point{0, 0}, callback_clicked} {
    size_range(Board::size, Board::size, Board::size, Board::size);

    board.attach(*this);
}

void Minesweeper::Clicked(Cell &cell) {
    int button = Fl::event_button();
    std::clog << button << "\n";

    if (button == 1) {
        board.OpenCell(cell);
    }
    else if (button == 3)
        board.Mark(cell);
}
