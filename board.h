#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include "Graph_lib/Simple_window.h"
#include "cell.h"

class Board : public Graph_lib::Widget {
public:
    static constexpr int margin = 30;
    static constexpr int N = 20; // size of board, board will have size N * N
    static constexpr int size = Cell::size * N + 2 * margin; // TODO: calculate size of board (find formula)

    Board (Point xy, Graph_lib::Callback callback);

    void show() override;
    void hide() override;
    void move(int dx, int dy) override;

    void OpenCell(Cell &cell);

    // Places a flag on a cell, making it checked
    void Mark(Cell &cell);

    void attach(Graph_lib::Window &window) override;
private:
    Graph_lib::Vector_ref<Cell> cells;
};

// Generate board with values and mines
std::vector<std::vector<char>> *GenerateBoard(int, int);
void GameOver() {}

#endif //MINESWEEPER_BOARD_H
