#include <iostream>
#include <vector>

#include "input_data.h"

using namespace std;

vector<int> partition_data(vector<int> input_data, int window_size) {
    vector<int> totals;

    for (int i = 0; i < input_data.size(); ++i) {
        // Make sure we don't try to calculate a window past the end of the data
        if (i + window_size > input_data.size()) {
            break;
        }

        int window_total = 0;

        for (int j = i; j-i < window_size; ++j) {
            window_total += input_data[j];
        }

        totals.push_back(window_total);
    }

    return totals;
}

int count_increases(vector<int> depth_data) {
    uint32_t last_depth = *depth_data.begin();
    uint32_t total_inc = 0;

    for (int depth : depth_data) {
        total_inc += depth > last_depth ? 1 : 0;
        last_depth = depth;
    }

    return total_inc;
}

int main() {
    vector<int> data = partition_data(depth_map, 3);
    int total_inc = count_increases(data);
    cout << "Total Depth Increases: " << total_inc << endl;
    return 0;
}