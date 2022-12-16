#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../utils/StringUtils.hpp"

struct FSNode {
    FSNode(size_t size, const std::string& name): size(size), name(name) {}

    size_t size;
    std::string name;

    std::vector<std::shared_ptr<FSNode>> files;
    std::map<std::string, std::shared_ptr<FSNode>> directories;

    std::shared_ptr<FSNode> parent;
};

std::shared_ptr<FSNode> root = std::make_shared<FSNode>(0, "/");

std::shared_ptr<FSNode> changeDirectory(std::shared_ptr<FSNode> current, const std::string& command) { 
    size_t index = command.rfind(" ");

    if (index != std::string::npos) {
        std::string argument = command.substr(index + 1);
        if (argument == root->name) {
            return root;
        } else if (argument == "..") {
            return current->parent; 
        } else {
            return current->directories[argument];
        }
    }

    return current;
}

void applyLSContents(std::shared_ptr<FSNode> current, const std::vector<std::string>& contents) {
    std::vector<std::string> split;

    for (auto iter = contents.begin(); iter != contents.end(); ++iter) {
        StringUtils::split(*iter, split, ' ');

        if (split[0] == "dir") {
            std::shared_ptr<FSNode> directory = std::make_shared<FSNode>(0, split[1]);
            directory->parent = current;
            current->directories[directory->name] = directory;
        } else {
            try {
                size_t size = stoi(split[0]);
                std::shared_ptr<FSNode> file = std::make_shared<FSNode>(size, split[1]);
                current->files.push_back(file);              
            } catch (const std::invalid_argument& e) {
            }
        }

        split.clear();
    }
}

void printFS(std::shared_ptr<FSNode> current, const std::string& tabIdent) {
    std::cout << tabIdent << "- " << current->name << " (dir)" << std::endl;

    std::string childTabIdent = tabIdent + "  ";

    for (auto iter = current->directories.begin(); iter != current->directories.end(); ++iter) {
        printFS(iter->second, childTabIdent);    
    }

    for (auto iter = current->files.begin(); iter != current->files.end(); ++iter) {
        std::cout << childTabIdent << "- " << (*iter)->name << " (file, size =" << (*iter)->size << ")" << std::endl;
    }
}

uint64_t calculateSizeOfDirectory(std::shared_ptr<FSNode> current) {
    uint64_t size = 0;

    for (auto iter = current->directories.begin(); iter != current->directories.end(); ++iter) {
        size += calculateSizeOfDirectory(iter->second);    
    }

    for (auto iter = current->files.begin(); iter != current->files.end(); ++iter) {
        size += (*iter)->size;    
    }

    return size;
}

void findDirectoriesBiggerThan(uint64_t sizeNeeded, std::shared_ptr<FSNode> current, std::vector<std::shared_ptr<FSNode>>& directories) {
    uint64_t size = calculateSizeOfDirectory(current);

    if (size >= sizeNeeded) {
        current->size = size;
        directories.push_back(current);    
    }

    for (auto iter = current->directories.begin(); iter != current->directories.end(); ++iter) {
        findDirectoriesBiggerThan(sizeNeeded, iter->second, directories);    
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    std::shared_ptr<FSNode> current;

    if (inputFile.is_open()) {
        std::string inputLine;
    
        std::vector<std::string> lsContents;

        while (getline(inputFile, inputLine)) {
            if (inputLine[0] == '$') {
                if (!lsContents.empty()) {
                    applyLSContents(current, lsContents);
                    lsContents.clear();       
                }

                if (inputLine.starts_with("$ cd")) {
                    current = changeDirectory(current, inputLine);
                } 
            } else {
                lsContents.push_back(inputLine);            
            }
        }

        if (!lsContents.empty()) {
            applyLSContents(current, lsContents);
        }

        uint64_t freeSpace = 70000000 - calculateSizeOfDirectory(root);
        uint64_t minimumToDelete = 30000000 - freeSpace;

        std::vector<std::shared_ptr<FSNode>> deletionCandidates;
        findDirectoriesBiggerThan(minimumToDelete, root, deletionCandidates);

        uint64_t minimumSize = std::numeric_limits<std::uint64_t>::max();
        for (auto iter = deletionCandidates.begin(); iter != deletionCandidates.end(); ++iter) {

            if ((*iter)->size < minimumSize) {
                minimumSize = (*iter)->size;
            }    
        }

        std::cout << minimumSize << std::endl;
    }
}
