#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include "Graph_lib/Simple_window.h"
#include "cell.h"

class Board : public Graph_lib::Widget {
public:
    static constexpr int margin = 30;
    static constexpr int size = 1060; // TODO: calculate size of board (find formula)
    static constexpr int N = 10;

    Board (Point xy, Graph_lib::Callback callback);

    void show() override;
    void hide() override;
    void move(int dx, int dy) override;

    void OpenCell(Cell &cell);
    void Mark(Cell &cell);
    int Where(Cell &cell);

    void GameOver() {};

    void attach(Graph_lib::Window &window) override;
private:
    Graph_lib::Vector_ref<Cell> cells;
};

std::vector<std::vector<char>> *GenerateBoard(int, int);

#endif //MINESWEEPER_BOARD_H
