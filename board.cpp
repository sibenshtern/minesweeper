#include "board.h"

Board::Board(Graph_lib::Point xy, Graph_lib::Callback callback)
        : Graph_lib::Widget{xy, size, size, "Minesweeper", nullptr} {
    auto board = GenerateBoard(kMinesNum, N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            Tile *tile;

            if ((*board)[i][j] == 'm')
                tile = new MinedTile();
            else
                tile = new EmptyTile{(*board)[i][j] - '0'};
            cells.push_back(
                    new Cell{Point{margin + j * Cell::size, margin + (N - 1 - i) * Cell::size}, *tile, callback});
        }
    delete board;
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
    if (mines_num >= board_size * board_size) throw std::runtime_error("too much mines");
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

int Board::Where(Cell &cell) {
    int k = 0;
    for (; k < cells.size(); ++k) {
        if (&cells[k] == &cell) {
            break;
        }
    }

    if (k == cells.size())
        throw std::runtime_error("Board::Where(): cell not found!");

    return k;
}

void Board::OpenCell(Cell &cell) {
    if (!cell.kTile)
        throw std::runtime_error("Cell doesn't exist");
    if (cell.kTile->IsMarked())
        cell.DetatchImage(*cell.img);


    if (cell.kTile->IsOpened())
        return;

    cell.kTile->Open();
    opened_cells += 1;

    if (cell.kTile->IsMined()) {
        End("You failed");
        return;
    }

    int n = Where(cell);
    std::cout << "position " << n << "\n";
    cell.Open(17);

    if (opened_cells + kMinesNum == N * N) {
        End("You win");
    }


    int x = n % N;
    int y = n / N;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
            if (!(x + i > -1 && x + i < N))
                continue;
            else if (!(y + j > -1 && y + j < N))
                continue;
            else if (i == 0 && j == 0)
                continue;
            else if (dynamic_cast<EmptyTile &>(*cell.kTile).IsMinesAround())
                continue;
            else if (!(i != 0 && j != 0 &&
                       !dynamic_cast<EmptyTile &>(*cells[(x + i) + N * (y + j)].kTile).IsMinesAround()))
                OpenCell(cells[(x + i) + N * (y + j)]);
}

void Board::Mark(Cell &cell) {
    if (!cell.kTile)
        throw std::runtime_error("cell doesn't on board");
    cell.kTile->ChangeState();
    auto center = cell.Center();
    if (!cell.kTile->IsMarked())
        cell.DetatchImage(*cell.img);
    else {
        cell.img = new Image{Point{center.x - 48, center.y - 48}, "flag.png", Suffix::png};
        cell.AttachImage(*cell.img);
    }
}

void Board::End(std::string s) {
    GameOver win{s};
    for (int i = 0; i < cells.size(); ++i)
        cells[i].deactivate();

    win.wait_for_button();
}
