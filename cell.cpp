#include <stdexcept>
#include "cell.h"

using namespace Graph_lib;

Cell::Cell(Point xy, Tile &tile, int size)
        : Button{xy, size, size, "", nullptr}, kSize{size}, kTile{&tile} {}

void Cell::attach(Window &window) {
    Button::attach(window);
}

MinedTile::MinedTile(Cell &cell) : Tile{cell} {};

void MinedTile::Open() {
    // TODO: draw mine picture (prefer SVG) and end the game (need to be checked in Minesweepers)
}

EmptyTile::EmptyTile(Cell &cell, int mines_around)
        : Tile{cell}, mines_around_count{mines_around} {};

void EmptyTile::Open() {
    is_opened = true;
    // TODO: place mines_around_count on button and make it disabled
}