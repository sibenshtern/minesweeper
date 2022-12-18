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

    std::vector<std::pair<int, int>> mines_coords;
private:
    Graph_lib::Vector_ref<Cell> cells;
    Graph_lib::Vector_ref<Graph_lib::Image> images;
    Graph_lib::Vector_ref<Tile> tiles;
    int opened_cells = 0;
};

// Generate board with values and mines
std::vector<std::vector<char>> *GenerateBoard(int, int, Board &);

class GameOver : public Graph_lib::Window {
public:
    GameOver(std::string s) :
            Window{Point{200, 200}, 400, 300, "Exit"}, button{Point{150, 150}, 100, 40, "Exit", cb_next} {
        message.set_label(s);
        message.set_font_size(40);
        attach(button);
        attach(message);
    }

    Graph_lib::Button button;

    void wait_for_button() {
        while (!button_pushed && Fl::wait());
        button_pushed = false;
    }

private:
    Graph_lib::Text message{Point{100, 100}, ""};
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