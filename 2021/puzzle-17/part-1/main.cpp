#include <iostream>
#include <fstream>
#include <sstream>

struct TargetArea {
    int minX;
    int maxX;
    int minY;
    int maxY;
};

std::pair<bool, int> simulateTrajectory(const TargetArea& targetArea, int initialVelocityX, int initialVelocityY) {
    int positionX = 0;
    int positionY = 0;
    int velocityX = initialVelocityX;
    int velocityY = initialVelocityY;
    int maxHeight = 0;
    bool hit = false;

    do {
        positionX += velocityX;
        positionY += velocityY;

        if (velocityX > 0) {
            velocityX -= 1;        
        } else if (velocityX < 0) {
            velocityX += 1;
        }

        velocityY -= 1;        

        maxHeight = std::max(positionY, maxHeight);

        hit = (positionX >= targetArea.minX && positionX <= targetArea.maxX && positionY >= targetArea.minY && positionY <= targetArea.maxY);
    } while (!hit && positionX < targetArea.maxX && positionY > targetArea.minY);

    return {hit, maxHeight};
}

TargetArea parseTargetArea(const std::string& line) {
    std::stringstream ss(line);
    std::string s;

    TargetArea targetArea = {};

    while (getline(ss, s, '.')) {
        if (!s.empty()) {
            size_t startX = s.find("x=");
            size_t startY = s.find("y=");
            if (startX != std::string::npos) {
                std::string minX = s.substr(startX + 2);
                targetArea.minX = stoi(minX);
            } else if (startY != std::string::npos) {
                std::string minY = s.substr(startY + 2);
                targetArea.minY = stoi(minY);

                size_t maxXEnd = s.find(",");
                if (maxXEnd != std::string::npos) {
                    std::string maxX = s.substr(0, maxXEnd);
                    targetArea.maxX = stoi(maxX);                
                }
            } else {
                targetArea.maxY = stoi(s);
            }
        }  
    }


    return targetArea;
}

int findMaxHeightHittingTarget(const TargetArea& targetArea) {
    int maxHeight = 0;

    for (int x = 1; x < targetArea.minX; ++x) {
        for (int y = 1; y < std::abs(0 - targetArea.minY); ++y) {
            std::pair<bool, int> result = simulateTrajectory(targetArea, x, y);
            if (result.first) {
                maxHeight = std::max(result.second, maxHeight);            
            }
        }    
    }

    return maxHeight;
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
        if (getline(inputFile, line)) {
            TargetArea targetArea = parseTargetArea(line);
            int maxHeight = findMaxHeightHittingTarget(targetArea);
            std::cout << maxHeight << std::endl;
        }
    }
}
