#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include "Graph_lib/Simple_window.h"
#include "cell.h"

class Board : public Graph_lib::Widget {
public:
    static constexpr int margin = 30;
    static constexpr int size = 1060; // TODO: calculate size of board (find formula)
    static constexpr int N = 20;

    Board (Point xy);

    void show() override;
    void hide() override;
    void move(int dx, int dy) override;

    void OpenCell(Cell &cell);
    void Mark(Cell &cell);

    void attach(Graph_lib::Window &window) override;
private:
    Graph_lib::Vector_ref<Cell> cells;
};

std::vector<std::vector<char>> *GenerateBoard(int, int);
void GameOver() {}

#endif //MINESWEEPER_BOARD_H
