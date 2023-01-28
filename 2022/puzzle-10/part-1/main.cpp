#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../../utils/InputReader.hpp"
#include "../../utils/StringUtils.hpp"

struct CPUState {
    int cycleCount;
    int xRegister;
    int cycleCheck;
};

int signalStrengthFor(CPUState& state) {
    if (state.cycleCount == state.cycleCheck) {
        state.cycleCheck += 40;
        return state.cycleCount * state.xRegister;
    } else {
        return 0;    
    }
}

int main(int argc, char* argv[]) {
    InputReader reader(argc, argv);

    CPUState state;
    state.cycleCount = 1;
    state.xRegister = 1;
    state.cycleCheck = 20;

    int signalStrength = 0;
    std::vector<std::string> split;

    auto read = [&](const std::string& line) {
        if (line.starts_with("noop")) {
            signalStrength += signalStrengthFor(state);
            state.cycleCount++;
        } else {
            split.clear();
            StringUtils::split(line, split, ' ');

            try {
                int value = stoi(split[1]);

                signalStrength += signalStrengthFor(state);
                state.cycleCount++;

                signalStrength += signalStrengthFor(state);
                state.cycleCount++;

                state.xRegister += value;            
            } catch (const std::invalid_argument& e) {
            }
        }
    };

    int result = reader.readLines(read);

    std::cout << signalStrength << std::endl;

    return result;
}
