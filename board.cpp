#include <iostream>
#include <vector>
#include <random>
#include <vector>
#include <unordered_set>

using u32 = uint_least16_t;
using engine = std::mt19937;

template <typename T>
void print(T a) {
    for (auto el : a)
        std::cout << el << " ";
    std::cout << "\n";
}

std::vector<std::unordered_set<int>> generate_mins_coords(int mines_num) {
    std::random_device os_seed;
    const u32 seed = os_seed();

    //std::cout << seed << "\n";

    engine generator(seed);
    std::uniform_int_distribution<u32> distribute(0, mines_num - 1);

    std::unordered_set<int> x;
    std::unordered_set<int> y;

    /*for (int i = 0; i < 10; ++i)
        std::cout << distribute(generator) << " ";
    std::cout << "\n";*/

    int i_x = 0;
    while (x.size() < mines_num) {
        i_x += 1;
        x.insert(distribute(generator));
    }

    int i_y = 0;
    while (y.size() < mines_num) {
        i_y += 1;
        y.insert(distribute(generator));
    }

    //std::cout << i_x << " " << i_y << "\n";

    return std::vector<std::unordered_set<int>> {x, y};
}

std::vector<std::vector<char>>* generate_board (int mines_num, int board_size) {
    std::vector<std::vector<char>>* head = new std::vector<std::vector<char>> (mines_num, std::vector<char>(mines_num,'0'));
    std::vector<std::pair<int, int>> mines_coords;

    std::vector<std::unordered_set<int>> mins = generate_mins_coords(mines_num);

    auto it_x = mins[0].begin();
    auto it_y = mins[1].begin();
    for (; it_x != mins[0].end() && it_y != mins[1].end(); ++it_x, ++it_y)
        mines_coords.push_back({*(it_x), *(it_y)});

    for (auto el : mines_coords) {
        //std::cout << el.first << " " << el.second << "\n";
        (*head)[el.first][el.second] = 'm';
    }

    for (auto [r, c]: mines_coords) {
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if ((r + i >= 0 && r + i < board_size) && (c + j >= 0 && c + j < board_size) && (i != 0 || j != 0) && (*head)[r + i][c + j] != 'm')
                    (*head)[r + i][c + j] += 1;
            }
        }
    }

    // for (int i = 0; i < board_size; ++i, std::cout << "\n")
    //     for (int j = 0; j < board_size; ++j)
    //         std::cout << (*head)[i][j] << "\t";

    return head;
}

int main(){
    std::vector<std::vector<char>>* p = generate_board(8, 8);
    delete p;
    return 0;
}