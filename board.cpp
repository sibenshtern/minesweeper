#include <iostream>
#include <vector>
#include <random>
#include <unordered_set>

#include "Graph_lib/Graph.h"
#include "Graph_lib/GUI.h"

#include "cell.h"
#include "board.h"

Board::Board(Graph_lib::Point xy, Graph_lib::Callback callback)
        : Graph_lib::Widget{xy, size, size, "Minesweeper", nullptr} {
    std::vector<Tile> tiles;

    auto board = GenerateBoard(10, N);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            Tile *tile;
            if ((*board)[i][j] == 'm')
                tile = new MinedTile();
            else
                tile = new EmptyTile{(*board)[i][j]};
            cells.push_back(new Cell{Point{margin + j * Cell::size, margin + (N - 1 - i) * Cell::size}, *tile, callback});
        }
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


void Board::OpenCell(Cell &cell)
{
    if (!cell.kTile) throw std::runtime_error("Cell doesn't exist");
    if (cell.kTile->IsOpened()) return;

    cell.kTile->Open();

    if (cell.kTile->kIsMined()) 
    {
        GameOver();
        return;
    }
    int n = &cell - &cells[0];
    int x = n % N;
    int y = n / N;
    for (int i = -1; i < 2; i++) 
        for (int j = -1; j < 2; j++)
            if ((x + i > -1 && x + i < N) &&
                (y + j > -1 && y + j < N) &&
                (i != 0 || j != 0))
                if (dynamic_cast<EmptyTile &>(*cell.kTile).kIsMinesAround() == 0) 
                    OpenCell(cells[(x + i) + N * (y + j)]);
}


void Board::Mark(Cell &cell)
{
    if (!cell.kTile) throw std::runtime_error("cell doesn't on board");
    cell.kTile->ChangeState();
}