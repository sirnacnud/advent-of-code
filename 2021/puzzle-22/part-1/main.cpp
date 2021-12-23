#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <set>

struct Cuboid {
	std::pair<int, int> xRange;
	std::pair<int, int> yRange;
	std::pair<int, int> zRange;
};

const std::pair<int, int> VALID_RANGE = {-50, 50};

std::pair<int, int> parseRange(const std::string& string) {
	std::pair<int, int> range;

	std::size_t start = string.find("=");
	std::size_t separator = string.find("..");
	
	if (start != std::string::npos && separator != std::string::npos) {
		size_t length = separator - (start + 1);
		std::string first = string.substr(start + 1, length);
		std::string second = string.substr(separator + 2);

		range.first = stoi(first);
		range.second = stoi(second);
	}

	return range;
}

bool parseProcedure(const std::string& line, Cuboid& cuboid) {
	bool on = line.starts_with("on");

	std::stringstream ss(line);
    std::string s;

    int index = 0;
    std::pair<char, char> pair;

    while (index < 3 && getline(ss, s, ',')) {
        if (index == 0) {
            cuboid.xRange = parseRange(s);
        } else if (index == 1) {
        	cuboid.yRange = parseRange(s); 
        } else {
            cuboid.zRange = parseRange(s);
        }

        index++;
    }

    return on;
}

bool doRangesOverlap(std::pair<int, int> rangeOne, std::pair<int, int> rangeTwo) {
	return (rangeTwo.first <= rangeOne.second && rangeTwo.second >= rangeOne.first);
}

void applyProcedureSetBased(std::set<std::tuple<int, int, int>>& cubes, bool on, Cuboid& cuboid) {
	if (!doRangesOverlap(VALID_RANGE, cuboid.xRange) || !doRangesOverlap(VALID_RANGE, cuboid.yRange) || !doRangesOverlap(VALID_RANGE, cuboid.zRange)) {
		return;
	}

	for (int x = cuboid.xRange.first; x <= cuboid.xRange.second; ++x) {
		for (int y = cuboid.yRange.first; y <= cuboid.yRange.second; ++y) {
			for (int z = cuboid.zRange.first; z <= cuboid.zRange.second; ++z) {
				std::tuple<int, int, int> cube = std::make_tuple(x, y, z);
				if (on) {
					cubes.insert(cube);
				} else {
					cubes.erase(cube);
				}
			}
		}
	}
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string line;
    	std::set<std::tuple<int, int, int>> cubes;

        while (getline(inputFile, line)) {
        	Cuboid cuboid = {};
        	bool on = parseProcedure(line, cuboid);
        	applyProcedureSetBased(cubes, on, cuboid);
        }

        std::cout << cubes.size() << std::endl;
    }
}