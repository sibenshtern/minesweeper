#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H

#include "Graph_lib/Simple_window.h"
#include "cell.h"
#include <string>

class Board : public Graph_lib::Widget {
public:
    static constexpr int margin = 30;
    static constexpr int size = 1060; // TODO: calculate size of board (find formula)
    static constexpr int N = 10;
    static constexpr int MinesNum = 10;

    Board (Point xy, Graph_lib::Callback callback);

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
    int OpenedCells = 0;
};

std::vector<std::vector<char>> *GenerateBoard(int, int);

class GameOver : public Graph_lib::Window {
public:
    GameOver(std::string s)
        : Window{Point{200, 200}, 200, 200, "You " + s},
        but{Point{90, 100}, 70, 20, "You " + s, cb_next }
        {
            attach(but);
        }

    Graph_lib::Button but;
    void wait_for_button ()
    {
        while (!button_pushed && Fl::wait());
        button_pushed = false;
        //Fl::program_should_quit(1);
        //Fl::wait();
    }

private:
  bool button_pushed{ false };

  static void cb_next (Graph_lib::Address, Graph_lib::Address addr) // callback for next_button
  {
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<GameOver&>(pb->window()).next();
  }

  void next () { button_pushed = true; }
};

#endif //MINESWEEPER_BOARD_H