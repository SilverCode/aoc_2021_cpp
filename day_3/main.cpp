#include <iostream>
#include <vector>
#include <bitset>

#include "input_data.h"
//#include "sample_data.h"

using namespace std;

uint32_t get_common_bit(const vector<uint32_t> &input, const int &position) {
    int zero = 0;
    int one = 0;
    const int shift_count = BIT_COUNT - position;

    for (const uint32_t &num : input) {
        uint32_t shifted = num >> shift_count;
        if (shifted & 0x1) {
            one++;
        } else {
            zero++;
        }
    }

    return one > zero ? 0x1 : 0x0;
}

uint32_t flip_bits(uint32_t input) {
    bitset<BIT_COUNT> output(input);
    output.flip();
    return static_cast<uint32_t>(output.to_ulong());
}

int main() {
    uint32_t gamma_rate = 0;

    for (int i = 0; i < BIT_COUNT; ++i) {
        uint32_t bit = get_common_bit(report_data, i);
        gamma_rate = (gamma_rate xor bit) << 1; // Set the least significant bit and shift everything left
    }

    uint32_t epsilon_rate = flip_bits(gamma_rate);

    cout << "Gamma Rate: " << gamma_rate << endl;
    cout << "Epsilon Rate: " << epsilon_rate << endl;
    cout << "Power Consumption: " << epsilon_rate * gamma_rate << endl;

    return 0;
}
