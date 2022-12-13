#ifndef MINESWEEPER_MINESWEEPER_H
#define MINESWEEPER_MINESWEEPER_H

#include "board.h"

using Graph_lib::Point;
using Graph_lib::Address;

class Minesweeper : public Graph_lib::Window {
public:
    static constexpr int kLeftMouse = 1;
    static constexpr int kRightMouse = 3;

    Minesweeper(Point xy);
private:
    Board board;

    static void callback_clicked(Address, Address widget) {
        auto &btn = Graph_lib::reference_to<Cell>(widget);
        dynamic_cast<Minesweeper &>(btn.window()).Clicked(btn);
    }

    void Clicked(Cell &c);
};


#endif //MINESWEEPER_MINESWEEPER_H
