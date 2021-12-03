#include <iostream>
#include <vector>

#include "input_data.h"

int main() {
    uint32_t last_depth = INT32_MIN;
    uint32_t total_inc = 0;

    for (int depth : depth_map) {
        total_inc += depth > last_depth ? 1 : 0;
        last_depth = depth;
    }

    std::cout << "Total Depth Increases: " << total_inc;
    return 0;
}