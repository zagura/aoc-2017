/*
 * =====================================================================================
 *
 *       Filename:  task1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  07.12.2019
 *
 *         Author:  Michał Zagórski (zagura), <mzagorsk@student.agh.edu.pl>
 *   Organization:  AGH University of Science and Technology, Kraków
 *
 * =====================================================================================
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>

using std::getline;
using std::istringstream;
using std::stringstream;
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::array;
using std::pair;
using std::make_pair;
using std::next_permutation;

using coord = int;
struct Point;
int mul(const Point& p1, const Point& p2);
int scalar_mul(const Point& p1, const Point& p2);
struct Point {
    int x, y;
    Point(int x_param, int y_param) noexcept : x(x_param),y(y_param) {}
    int size() const {
        return (x * x) + (y * y);
    }
    bool collide(const Point& target,const Point& collider) const {
        Point vec1(target.x - x, target.y - y);
        Point vec2(collider.x - x, collider.y - y);
        int result = mul(vec1, vec2);
        if (vec1.size() < vec2.size()) {
            return false;
        }
        if (result == 0 and scalar_mul(vec1, vec2) > 0) {
            return true;
//            if (vec1.x % vec2.x == 0 and vec1.y % vec2.y == 0
//                   and (vec1.x / vec2.x) == (vec1.y / vec2.y)) {
//                return true;
//            }
        }
        return false;
    }
    bool operator==(const Point& other) const {
        return x == other.x and y == other.y;
    }
    bool operator!=(const Point& other) const {
        return x != other.x or y != other.y;
    }
    void print() {
        cout << '(' << x << ',' << y << ')';
    }
};

int mul (const Point& p1, const Point& p2) {
    return (p1.x * p2.y) - (p1.y * p2.x);
}

int scalar_mul(const Point& p1, const Point& p2) {
    return (p1.x * p2.x) + (p1.y * p2.y);
}


vector<Point> read_map() {
    vector<Point> asteroid_map;
    int y = 0;
    for (string row; getline(std::cin, row); y++) {
        int max_x = row.size();
        for (int x = 0; x < max_x; x++) {
            if (row[x] == '#') {
                asteroid_map.emplace_back(x, y);
            }
        }
    }
    return asteroid_map;
}

pair<Point,int> get_best(vector<Point>& asteroid_map) {
    Point best(0,0);
    int max_sight = 0;
    for (Point& asteroid: asteroid_map) {
        vector<Point> targets;
        int current_sight = 0;
        for (Point& target: asteroid_map) {
            if (target != asteroid) {
                bool sight = true;
                for(Point& other: asteroid_map) {
                    if (other != asteroid && other != target) {
                        if (asteroid.collide(target, other)) {
                            sight = false;
                            break;
                        }
                    }
                }
                if (sight) {
                    targets.push_back(target);
                    current_sight += 1;
                }
            }
        }
        if (current_sight > max_sight) {
            max_sight = current_sight;
            best = asteroid;
//            best.print();
//            cout << endl;
//            for (auto& t: targets) {
//                cout <<  "  ";
//                t.print();
//                cout << endl;
//            }
        }
    }
    return make_pair(best, max_sight);
}


int main() {
    vector<Point> asteroid_map = read_map();
    auto best = get_best(asteroid_map);
    cout << "Part 1: " << best.second << endl;
    return 0;
}
