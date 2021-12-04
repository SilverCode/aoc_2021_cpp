#include <iostream>
#include <vector>

#include "input_data.h"

using namespace std;

void split_instruction(const string &input, string &instruction, int &value) {
    size_t token_pos = input.find(' ');
    instruction = input.substr(0, token_pos);
    value = stoi(input.substr(token_pos, input.length() - token_pos));
}

void parse_instruction(const string& instruction, int &position, int &depth, int &aim) {
    string cmd;
    int val;
    split_instruction(instruction, cmd, val);

    if (cmd == "forward") {
        position += val;
        depth += aim * val;
    } else if (cmd == "backward") {
        position -= val;
    } else if (cmd == "up") {
        aim -= val;
    } else if (cmd == "down") {
        aim += val;
    }
}

int main() {
    int position = 0;
    int depth = 0;
    int aim = 0;

    for (const string& cmd : input_commands) {
        parse_instruction(cmd, position, depth, aim);
    }

    cout << "Position: " << position << endl;
    cout << "Depth: " << depth << endl;
    cout << "Multiplied: " << position * depth << endl;

    return 0;
}
