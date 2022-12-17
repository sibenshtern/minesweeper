#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H


#include <stdexcept>
#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>

#include "Graph_lib/Simple_window.h"

using namespace Graph_lib;

class Tile;

class Cell : public Graph_lib::Button {
public:
    static constexpr int size = 100; // cell size in pixel
    Cell(Point xy, Tile &t, Callback callback);
    void attach(Graph_lib::Window &window) override;
    void AttachTile(Tile &tile);
    void Open();
    void AttachImage(Image&);
    void DetatchImage(Image&);
    Image *img = nullptr;
    Image *mine = nullptr;

    ~Cell() { delete img; delete mine; }

    Point Center() const { return Point{loc.x + width / 2, loc.y + height / 2}; }
    Tile *kTile{nullptr}; // pointer to logic tile
    void deactivate() { pw->deactivate(); }
};

class Tile {
public:
    Tile() = default;

    void Attach(Cell &cell);
    void ChangeState() { is_marked = !is_marked; }
    
    bool IsOpened() { return is_opened; }
    bool IsMarked() { return is_marked; }
    // Shows if cell is mined
    // Return true if yes, false if no
    virtual bool IsMined() const = 0;

    // Open Tile, place label to cell, change the color, disable it
    // Set is_opened = true if Tile is Empty Tile
    // Set red color to Cell if Tile is Mined Tile
    virtual void Open() = 0;
    virtual ~Tile() = default;
protected:
    Cell *kCell = nullptr;
    bool is_opened{false};
    bool is_marked{false};
};

class MinedTile : public Tile {
public:
    MinedTile() = default;
    void Open() override;
    bool IsMined() const override { return true; }
};

class EmptyTile : public Tile {
public:
    EmptyTile(int mines_around);

    void Open() override;
    bool IsMined() const override { return false; }

    // Shows if there are mines around the cell.
    // Returns true if yes, false if not
    bool IsMinesAround() const { return mines_around_count != 0; }

    // Return count of mines around the cell.
    // Interface for mines_around_count
    int MinesCount() const {return mines_around_count; }
private:
    int mines_around_count;
};

std::vector<std::pair<int, int>> GenerateMinesCoords(int, int);


#endif //MINESWEEPER_CELL_H
