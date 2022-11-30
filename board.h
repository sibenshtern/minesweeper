#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include "Graph_lib/Simple_window.h"
#include "cell.h"

class Board : Graph_lib::Widget {
public:
    const int margin = 30;
    const int size = 100; // TODO: calculate size of board (find formula)

    Board (Point xy);

    void show() override;
    void hide() override;
    void move(int dx, int dy) override;

    void attach(Graph_lib::Window &window) override;
private:
    Graph_lib::Vector_ref<Cell> cells;
};


#endif //MINESWEEPER_BOARD_H
