#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H


#include "Graph_lib/Graph.h"
#include "Graph_lib/GUI.h"

#include "cell.h"

class Board : public Graph_lib::Widget {
public:
    static constexpr int margin = 30;
    static constexpr int N = 10; // size of board, board will have size N * N
    static constexpr int size = Cell::size * N + 2 * margin; // window size in pixels
    static constexpr int kMinesNum = 10;

    Board(Point xy, Graph_lib::Callback callback);

    void show() override;

    void hide() override;

    void move(int dx, int dy) override;

    void OpenCell(Cell &cell);

    void Mark(Cell &cell);

    int Where(Cell &cell);

    void End(std::string s);

    void attach(Graph_lib::Window &window) override;

private:
    Graph_lib::Vector_ref<Cell> cells;
    int opened_cells = 0;
};

// Generate board with values and mines
std::vector<std::vector<char>> *GenerateBoard(int, int);

class GameOver : public Graph_lib::Window {
public:
    GameOver(std::string s) :
            Window{Point{200, 200}, 200, 200, "You " + s}, button{Point{90, 100}, 70, 20, "You " + s, cb_next} {
        attach(button);
    }

    Graph_lib::Button button;

    void wait_for_button() {
        while (!button_pushed && Fl::wait());
        button_pushed = false;
    }

private:
    bool button_pushed{false};

    static void cb_next(Graph_lib::Address, Graph_lib::Address addr) // callback for next_button
    {
        auto *pb = static_cast<Graph_lib::Button *>(addr);
        dynamic_cast<GameOver &>(pb->window()).next();
        exit(0);
    }

    void next() { button_pushed = true; }
};

#endif //MINESWEEPER_BOARD_H