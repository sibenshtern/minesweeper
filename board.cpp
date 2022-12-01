#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>

#include "Graph_lib/Graph.h"
#include "Graph_lib/GUI.h"

#include "cell.h"
#include "board.h"

Board::Board(Graph_lib::Point xy) : Graph_lib::Widget{xy, size, size, "Minesweeper", nullptr} {
    // TODO: write constructor
}

void Board::show() {
    for (int i = 0; i < cells.size(); ++i)
        cells[i].show();
}

void Board::hide() {
    for (int i = 0; i < cells.size(); ++i)
        cells[i].hide();
}

void Board::move(int dx, int dy) {
    for (int i = 0; i < cells.size(); ++i)
        cells[i].move(dx, dy);
}

void Board::attach(Graph_lib::Window &window) {
    for (int i = 0; i < cells.size(); ++i)
        window.attach(cells[i]);

    own = &window;
}

std::vector<std::vector<char>> *GenerateBoard(int mines_num, int board_size) {
    auto *head = new std::vector<std::vector<char>>(board_size, std::vector<char>(board_size, '0'));
    std::vector<std::pair<int, int>> mines_coords;

    auto mines = GenerateMinesCoords(mines_num, board_size);

    for (auto el: mines)
        (*head)[el.first][el.second] = 'm';

    for (auto [r, c]: mines) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++)
                if ((r + i >= 0 && r + i < board_size) &&
                    (c + j >= 0 && c + j < board_size) &&
                    (i != 0 || j != 0) &&
                    (*head)[r + i][c + j] != 'm')
                    (*head)[r + i][c + j] += 1;
        }
    }

    return head;
}
