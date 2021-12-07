#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

const int INVALID_WINDOW_SUM = -1;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string inputLine;

        int windowIncreases = 0;
        int previousDepth = 0;
        int previousWindowSum = INVALID_WINDOW_SUM;

        std::vector<int> readings;

        while (getline(inputFile, inputLine)) {
            try {
                int reading = stoi(inputLine);
                readings.push_back(reading);
            } catch (const std::invalid_argument& e) {
                continue;            
            }
        }

        for (size_t i = 0; i < readings.size() - 2; ++i) {
            int startDepth = readings[i];
		    int endDepth = readings[i + 2];

		    int windowSum;

		    if (previousWindowSum != INVALID_WINDOW_SUM) {
			    windowSum = previousWindowSum - previousDepth + endDepth;

			    if (windowSum > previousWindowSum) {
				    windowIncreases += 1;
			    }
		    } else {
			    int middleDepth = readings[i + 1];
			    windowSum = (startDepth + middleDepth + endDepth);
		    }

		    previousWindowSum = windowSum;
		    previousDepth = startDepth;
        }

        std::cout << windowIncreases << std::endl;
    }
}
