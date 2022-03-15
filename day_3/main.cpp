#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

#include "input_data.h"
//#include "sample_data.h"

using namespace std;

uint32_t get_common_bit(const vector<uint32_t> &input, const int &position, bool most_common = true) {
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

    if (most_common) {
        return one > zero ? 0x1 : one == zero ? -1 : 0x0;
    } else {
        return one < zero ? 0x1 : one == zero ? -1 : 0x0;
    }

}

uint32_t flip_bits(uint32_t input) {
    bitset<BIT_COUNT> output(input);
    output.flip();
    return static_cast<uint32_t>(output.to_ulong());
}

vector<uint32_t> oxygen_generator_rating(const vector<uint32_t> &input, int bit_position) {
    if (input.size() <= 1) {
        return input;
    }

    uint32_t common_bit = get_common_bit(input, bit_position);

    if (common_bit == -1) {
        common_bit = 1;
    }

    vector<uint32_t> tmp;
    copy_if(input.begin(), input.end(), back_inserter(tmp),
            [bit_position, common_bit](int i) {
                uint32_t shifted = (i >> BIT_COUNT - bit_position) & 0x01;
                return shifted == common_bit;
            });

    return oxygen_generator_rating(tmp, ++bit_position);
}

vector<uint32_t> co2_scrubber_rating(const vector<uint32_t> &input, int bit_position) {
    if (input.size() <= 1) {
        return input;
    }

    uint32_t least_common_bit = get_common_bit(input, bit_position, false);

    if (least_common_bit == -1) {
        least_common_bit = 0;
    }

    vector<uint32_t> tmp;
    copy_if(input.begin(), input.end(), back_inserter(tmp),
            [bit_position, least_common_bit](int i) {
                uint32_t shifted = (i >> BIT_COUNT - bit_position) & 0x01;
                return shifted == least_common_bit;
            });

    return co2_scrubber_rating(tmp, ++bit_position);
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

    uint32_t oxygen = oxygen_generator_rating(report_data, 1)[0];
    cout << "Oxygen Value: " << oxygen << endl;

    uint32_t co2_scrubber = co2_scrubber_rating(report_data, 1)[0];
    cout << "Scrubber Value: " << co2_scrubber << endl;

    uint32_t life_support = co2_scrubber * oxygen;
    cout << "Life Support Rating: " <<  life_support << endl;

    return 0;
}
