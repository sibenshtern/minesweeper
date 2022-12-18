#include "board.h"

Board::Board(Graph_lib::Point xy, Graph_lib::Callback callback)
        : Graph_lib::Widget{xy, size, size, "Minesweeper", nullptr} {
    auto board = GenerateBoard(kMinesNum, N, *this);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if ((*board)[i][j] == 'm')
                tiles.push_back(new MinedTile());
            else
                tiles.push_back(new EmptyTile{(*board)[i][j] - '0'});
            cells.push_back(new Cell{Point{margin + j * Cell::size, margin + (N - 1 - i) * Cell::size}, tiles[tiles.size() - 1], callback});
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

std::vector<std::vector<char>> *GenerateBoard(int mines_num, int board_size, Board &board) {
    auto *head = new std::vector<std::vector<char>>(board_size, std::vector<char>(board_size, '0'));

    if (mines_num >= board_size * board_size)
        throw std::runtime_error("too much mines");

    std::vector<std::pair<int, int>> mines_coords;

    auto mines = GenerateMinesCoords(mines_num, board_size);
    board.mines_coords = mines;

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
    if (cell.get_tile().IsMarked())
        cell.DetatchImage(cell.get_image());


    if (cell.get_tile().IsOpened())
        return;

    cell.get_tile().Open();
    opened_cells += 1;

    if (cell.get_tile().IsMined()) {
        for (auto [y, x] : mines_coords)
            try {
                cells[x + N * y].DetatchImage(cells[x + N * y].get_image());
                dynamic_cast<MinedTile &>(cells[x + N * y].get_tile()).Open();
            } catch (std::exception &e) {
                std::cerr << e.what() << "\n";
            }
        Fl::redraw();
        End("You failed");
        return;
    }

    int n = Where(cell);
    cell.Open();

    if (opened_cells + kMinesNum == N * N) {
        End("You winner");
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
            else if (dynamic_cast<EmptyTile &>(cell.get_tile()).IsMinesAround())
                continue;
            else if (!(i != 0 && j != 0 &&
                       !dynamic_cast<EmptyTile &>(cells[(x + i) + N * (y + j)].get_tile()).IsMinesAround()))
                OpenCell(cells[(x + i) + N * (y + j)]);
}

void Board::Mark(Cell &cell) {
    auto center = cell.Center();
    if (cell.get_tile().IsMarked())
        cell.DetatchImage(cell.get_image());
    else {
        cell.set_image(new Image{Point{center.x - 48, center.y - 48}, "flag.png", Suffix::png});
        cell.AttachImage(cell.get_image());
    }
    cell.get_tile().ChangeState();
}

void Board::End(std::string s) {
    GameOver win{s};
    for (int i = 0; i < cells.size(); ++i)
        cells[i].deactivate();

    win.wait_for_button();
}
