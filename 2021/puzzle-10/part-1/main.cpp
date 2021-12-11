#include <iostream>
#include <fstream>

enum IllegalCharacter {
    Parenthese,
    Bracket,
    CurlyBrace,
    GreaterThan,

    None
};

IllegalCharacter illegalCharacterFrom(const char& character) {
    switch (character) {
    case ')':
        return Parenthese;
    case ']':
        return Bracket;
    case '}':
        return CurlyBrace;
    case '>':
        return GreaterThan;
    default:
        return None;    
    }
}

IllegalCharacter checkLine(const std::string& line) {
    std::string parsed;

    for (size_t i = 0; i < line.size(); ++i) {
        switch (line[i]) {
        case '(': case '[': case '{': case '<':
            parsed.push_back(line[i]);
            break;
        case ')':
            if (parsed.back() == '(') {
                parsed.pop_back();            
            } else {
                return illegalCharacterFrom(line[i]);             
            }
            break;
        case ']':
            if (parsed.back() == '[') {
                parsed.pop_back();            
            } else {
                return illegalCharacterFrom(line[i]);             
            }
            break;
        case '}':
            if (parsed.back() == '{') {
                parsed.pop_back();            
            } else {
                return illegalCharacterFrom(line[i]);             
            }
            break;
        case '>':
            if (parsed.back() == '<') {
                parsed.pop_back();            
            } else {
                return illegalCharacterFrom(line[i]);             
            }
            break;
        default:
            continue;
        }
    }

    return None;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Supply input file as first argument" << std::endl;
        return -1;    
    }

    std::ifstream inputFile;
    inputFile.open(argv[1]);

    if (inputFile.is_open()) {
        std::string inputLine;

        int score = 0;

        while (getline(inputFile, inputLine)) {
            IllegalCharacter character = checkLine(inputLine);

            switch (character) {
            case Parenthese:
                score += 3; 
                break;
            case Bracket:
                score += 57;
                break;
            case CurlyBrace:
                score += 1197;
                break;
            case GreaterThan:
                score += 25137;
                break;
            case None:
                continue;  
            }
        }

        std::cout << score << std::endl;
    }
}
