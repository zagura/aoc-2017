/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:  Advent of Code 2020 - Day 11
 *
 *        Version:  0.1.1
 *        Created:  11.12.2020
 *
 *         Author:  Michał Zagórski (zagura), <zagura6@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <queue>
#include <algorithm>

constexpr char occupied = '#';
constexpr char empty = 'L';
constexpr char floor = '.';
const std::array<std::pair<int, int>, 8> neighbours = {{
    { -1, -1 }, // upper-left
    { -1, 0 }, // up
    { -1, 1 },  // upper-right
    { 0, -1 }, // left
    { 0, 1 },  // right
    { 1, -1 },
    { 1, 0 },
    { 1, 1}
}};

using std::string;
template <class T>
bool fits(const int& index, const T& vec) {
    return (index >= 0 && index < static_cast<int>(vec.size()));
}
std::vector<string> get_next(const std::vector<string>& prev_seatmap, /* inout */ bool& changed) {
    std::vector<string> seatmap = prev_seatmap;
    changed = false;
    for (size_t row = 0; row < seatmap.size(); row++) {
        for(size_t column = 0; column  < seatmap[row].size(); column++) {
            char place = seatmap[row][column];
            if (place != floor) {
                int neigh_count = 0;
                for (const auto& el: neighbours) {
                    int new_row = row + el.first;
                    int new_column = column + el.second;
                    if (fits(new_row, seatmap) && fits (new_column, seatmap[row])) {
                        if (prev_seatmap[new_row][new_column] == occupied)
                            neigh_count++;
                    }
                }
                char new_state = seatmap[row][column];
                if (new_state == empty and neigh_count == 0) {
                    new_state = occupied;
                } else if (new_state == occupied and neigh_count >= 4) {
                    new_state = empty;
                }
                seatmap[row][column] = new_state;
                if (new_state != prev_seatmap[row][column]) {
                    changed = true;
                }
            }
        }
    }
    return seatmap;
}


int main(int argc, char* argv[]) {
    std::ifstream input { "input.in" };
    if (argc == 2) {
        input = std::ifstream { argv[1] };
    }
    if (!input.good()) {
        ::fprintf(stderr, "Cannot open input file\n");
        return 2;
    }
    std::vector<std::string> seatmap {};
    for (std::string line; getline(input, line);) {
        seatmap.push_back(line);
    }
    bool changed = true;
    int iteration = 0;
    while (changed) {
        changed = false;
        std::vector<string> changed_seatmap;
        changed_seatmap = get_next(seatmap, changed);
        seatmap.clear();
        seatmap = changed_seatmap;
        iteration++;
        if (iteration % 100 == 0) {
            printf("Iteration: %d\n", iteration);
        }
//        for (auto l: seatmap) {
//            std::cout<<l << std::endl;
//        }
//        std::cout <<std::endl;
//        getchar();
    }
    // count occupied seats
    size_t occupied_count = 0;
    for(const auto& line: seatmap) {
        occupied_count += std::count_if(line.begin(), line.end(), [](char c) { return c == occupied;});
    }

    ::printf("Task 1 result: %zu\n", occupied_count);
    return 0;
}

