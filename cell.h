#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H


#include "Graph_lib/Simple_window.h"

using namespace Graph_lib;

class Tile;

class Cell : public Graph_lib::Button {
public:
    static constexpr int size = 100;
    Cell(Point xy, Tile &t);
    void attach(Graph_lib::Window &window) override;
    void AttachTile(Tile &tile);

    Point Center() const { return Point{loc.x + width / 2, loc.y + height / 2}; }
    const int kSize;
protected:
    Tile *kTile{nullptr};
};

class Tile {
public:
    Tile() = default;

    void Attach(const Cell &cell);

    virtual bool kIsMined() const = 0;
    virtual void Open() = 0;
    virtual ~Tile() = default;
protected:
    const Cell *kCell = nullptr;
    bool is_opened{false};
};

class MinedTile : public Tile {
public:
    MinedTile() = default;
    void Open() override;
    bool kIsMined() const override { return true; }
};

class EmptyTile : public Tile {
public:
    EmptyTile(int mines_around);

    void Open() override;
    bool kIsMined() const override { return false; }
    bool kIsMinesAround() const { return mines_around_count == 0; }
private:
    int mines_around_count;
};

std::vector<std::pair<int, int>> GenerateMinesCoords(int, int);


#endif //MINESWEEPER_CELL_H
