#include <iostream>
#include <vector>
#include <random>
#include <vector>
#include <unordered_set>

using u32 = uint_least16_t;
using engine = std::mt19937;


auto GenerateMinesCoords(int mines_num, int board_size) {
    std::random_device os_seed;
    const u32 seed = os_seed();

    engine generator(seed);
    std::uniform_int_distribution<u32> distribute(0, board_size * board_size - 1);

    std::unordered_set<int> coords;

    while (coords.size() < mines_num)
        coords.insert(distribute(generator));

    std::vector<std::pair <int, int>> coords_xy;

    for (int xy : coords)
        coords_xy.push_back(std::pair(xy / board_size, xy % board_size));

    return coords_xy;
}

std::vector<std::vector<char>>* GenerateBoard (int mines_num, int board_size) {
    std::vector<std::vector<char>>* head = new std::vector<std::vector<char>> (mines_num, std::vector<char>(mines_num,'0'));
    std::vector<std::pair<int, int>> mines_coords;

    auto mines = GenerateMinesCoords(mines_num, board_size);

    for (auto el : mines)
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

    for (int i = 0; i < board_size; ++i, std::cout << "\n")
        for (int j = 0; j < board_size; ++j)
            std::cout << (*head)[i][j] << "\t";

    return head;
}

int main(){
    std::vector<std::vector<char>>* p = GenerateBoard(10, 8);
    delete p;
    return 0;
}