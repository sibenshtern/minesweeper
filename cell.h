#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H


#include "Graph_lib/Simple_window.h"

using namespace Graph_lib;

class Tile;

class Cell : Graph_lib::Button {
public:
    Cell(Point xy, Tile &t, int size);
    void attach(Graph_lib::Window &window) override;

    Point Center() const { return Point{loc.x + width / 2, loc.y + height / 2}; }
    const int kSize;
protected:
    const Tile *kTile{nullptr};
};

class Tile {
public:
    Tile(Cell &c) : kCell{&c} {}

    virtual bool kIsMined() const = 0;
    virtual void Open() = 0;
    virtual ~Tile() = default;
protected:
    const Cell *kCell = nullptr;
    bool is_opened{false};
};

class MinedTile : Tile {
public:
    MinedTile(Cell &cell);
    void Open() override;
    bool kIsMined() const override { return true; }
};

class EmptyTile : Tile {
public:
    EmptyTile(Cell &cell, int mines_around);

    void Open() override;
    bool kIsMined() const override { return false; }
    bool kIsMinesAround() const { return mines_around_count == 0; }
private:
    int mines_around_count;
};


#endif //MINESWEEPER_CELL_H
