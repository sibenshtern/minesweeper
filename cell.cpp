#include <stdexcept>
#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>
#include "cell.h"

using u32 = uint_least16_t;
using engine = std::mt19937;

using namespace Graph_lib;

Cell::Cell(Point xy, Tile &tile, Callback callback)
        : Button{xy, size, size, "", callback}, kSize{size}, kTile{&tile} {
}

void Cell::attach(Window &window) {
    Button::attach(window);
}

void Cell::AttachTile(Tile &tile) {
    if (kTile)
        throw std::runtime_error("Cell::AttachTile(): cell already have tile");
    kTile = &tile;
}

void Tile::Attach(const Cell &cell) {
    if (kCell)
        throw std::runtime_error("Tile::Attach(): Tile already add to Cell");
    kCell = &cell;
}

void MinedTile::Open() {
    // TODO: draw mine picture (prefer SVG) and end the game (need to be checked in Minesweepers)
}

EmptyTile::EmptyTile(int mines_around)
        : mines_around_count{mines_around} {};

void EmptyTile::Open() {
    is_opened = true;
    // TODO: place mines_around_count on button and make it disabled
}

std::vector<std::pair<int, int>> GenerateMinesCoords(int mines_num, int board_size) {
    std::random_device os_seed;
    const u32 seed = os_seed();

    engine generator(seed);
    std::uniform_int_distribution<u32> distribute(0, board_size * board_size - 1);

    std::unordered_set<int> coords;

    while (coords.size() < mines_num)
        coords.insert(distribute(generator));

    std::vector<std::pair<int, int>> coords_xy;

    for (int xy: coords)
        coords_xy.push_back(std::pair(xy / board_size, xy % board_size));

    return coords_xy;
}
