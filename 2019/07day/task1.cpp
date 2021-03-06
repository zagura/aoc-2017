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
using std::next_permutation;

// modes
// 0 - position mode
// 1 - immediate mode

void add(vector<int>& vals, int begin_index, int modes) {
    int mode1 = modes % 10;
    int mode2 = (modes / 10) % 10;
    int val1 = vals.at(begin_index + 1);
    int val2 = vals.at(begin_index + 2);
    int val3 = vals.at(begin_index + 3);
    if (not mode1) {
        val1 = vals.at(val1);
    }
    if (not mode2) {
        val2 = vals.at(val2);
    }
    int result = val1 + val2;
    vals[val3] = result;
}

void multiply(vector<int>& vals, int begin_index, int modes) {
    int mode1 = modes % 10;
    int mode2 = (modes / 10) % 10;
    int val1 = vals.at(begin_index + 1);
    int val2 = vals.at(begin_index + 2);
    int val3 = vals.at(begin_index + 3);
    if (not mode1) {
        val1 = vals.at(val1);
    }
    if (not mode2) {
        val2 = vals.at(val2);
    }
    int result = val1 * val2;
    vals[val3] = result;
}

void less_than(vector<int>& vals, int i, int modes) {
    int mode1 = modes % 10;
    int mode2 = (modes / 10) % 10;
    int v1, v2, v3;
    v1 = vals.at(i+1);
    v2 = vals.at(i+2);
    v3 = vals.at(i+3);
    if (not mode1) {
        v1 = vals.at(v1);
    }
    if (not mode2) {
        v2 = vals.at(v2);
    }
    if (v1 < v2) {
        vals[v3] = 1;
    } else {
        vals[v3] = 0;
    }
}

void equal(vector<int>& vals, int i, int modes) {
    int mode1 = modes % 10;
    int mode2 = (modes / 10) % 10;
    int v1, v2, v3;
    v1 = vals.at(i+1);
    v2 = vals.at(i+2);
    v3 = vals.at(i+3);
    if (not mode1) {
        v1 = vals.at(v1);
    }
    if (not mode2) {
        v2 = vals.at(v2);
    }
    if (v1 == v2) {
        vals[v3] = 1;
    } else {
        vals[v3] = 0;
    }
}


int process_code(vector<int> vals, vector<int>& input) {
    int output = 0;
    auto input_iter = input.begin();
    for (size_t i = 0; i < vals.size();) {
        int v1 = 0;
        int v2 = 0;
        int v3 = 0;
        int mode;
        int mode1, mode2;
        int instruction = vals[i] % 100;
//        cout << "Element i " << i << endl;
        mode = vals[i] / 100;
        switch(instruction) {
            case 1:
                add(vals, i, mode);
                i += 4;
                break;
            case 2:
                multiply(vals, i, mode);
                i += 4;
                break;
            case 3:
                v1 = vals.at(i+1);
//                cout << "Get: " << endl;
                v2 = *input_iter;
                ++input_iter;
                vals[v1] = v2;
                i += 2;
                break;
            case 4:
                v1 = vals.at(i+1);
//                cout << "Output: " << vals[v1] << endl;
                output = vals[v1];
                i += 2;
                break;
            case 5:
                v1 = vals.at(i+1);
                v2 = vals.at(i+2);
                mode1 = mode % 10;
                mode2 = (mode / 10) % 10;
                if (not mode1) {
                    v1 = vals.at(v1);
                }
                if (not mode2) {
                    v2 = vals.at(v2);
                }
                if (v1 != 0) {
                    i = v2;
                } else {
                    i+= 3;
                }
                break;
            case 6:
                v1 = vals.at(i+1);
                v2 = vals.at(i+2);
                mode1 = mode % 10;
                mode2 = (mode / 10) % 10;
                if (not mode1) {
                    v1 = vals.at(v1);
                }
                if (not mode2) {
                    v2 = vals.at(v2);
                }
                if (v1 == 0) {
                    i = v2;
                } else {
                    i+= 3;
                }
                break;
            case 7:
                less_than(vals, i, mode);
                i += 4;
                break;
            case 8:
                equal(vals, i, mode);
                i += 4;
                break;
            case 99:
//                std::cout << "End of program" << std::endl;
                i = vals.size() + 1;
                break;
            default:
//                cout << "Problem: " << i << '[' << vals[i] << ']' << endl;
                i = vals.size();
        }
    }
    return output;
}

int check_permutation(array<int, 5>& phases, vector<int>& vals) {
    int input = 0;
    vector<int> inputs {};
    inputs.reserve(2);
    for (auto& phase: phases) {
        inputs[0] = phase;
        inputs[1] = input;
        input =  process_code(vals, inputs);
    }
    cout << "Permutation output " << input << endl;
    return input;
}

int main() {
    std::vector<int> vals;
    vals.reserve(200);
    std::string line;
    getline(std::cin, line);
    stringstream ss { line };
    for (std::string number; getline(ss, number, ',');) {
        vals.push_back(std::stoi(number));
    }
    std::array<int, 5> phases = {0, 1, 2, 3, 4};
    int result = 0;
    int max_result = 0;
    do {
        result = check_permutation(phases, vals);
        if (result > max_result) {
            max_result = result;
        }
    } while(std::next_permutation(phases.begin(), phases.end()));
    cout << "Task 1 result: " << max_result << endl;
//    for (auto& v: vals) {
//        cout << v << ",";
//    }
//    cout << endl;
    return 0;
}
