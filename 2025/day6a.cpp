#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MAXLINES 10
#define MAXCOLUMNS 2000

void getNumbersSymbols(std::ifstream& f, uint64_t** numbers, bool* symbols, int* nbLines, int* nbColumns) {
    std::string line;
    int i = 0;
    while (std::getline(f, line)) {
        std::size_t pos;
        int j = 0;
        while ((pos = line.find(' ')) != std::string::npos) {
            if (pos != 0) {
                std::string token = line.substr(0, pos);
                if (token == "+" || token == "*") {
                    symbols[j] = (token == "*");
                }
                else {
                    numbers[i][j] = std::stoull(token);
                }
                j++;
            }
            line.erase(0, pos + 1);
        }
        *nbColumns = j;
        i++;
    }
    *nbLines = i;
}

uint64_t computeColumn(uint64_t** numbers, bool isMult, int column, int nbLines) {
    uint64_t total = isMult;
    for (int i = 0; i < nbLines - 1; i++) {
        if (isMult) {
            total *= numbers[i][column];
        }
        else {
            total += numbers[i][column];
        }
    }
    return total;
}

uint64_t processFile(std::string filename) {

    // allocate memory
    uint64_t** numbers = (uint64_t**) malloc(MAXLINES * sizeof(uint64_t*));
    for (int i = 0; i < MAXLINES; i++) {
        numbers[i] = (uint64_t*) malloc(MAXCOLUMNS * sizeof(uint64_t));
    }
    bool* symbols = (bool*) malloc(MAXCOLUMNS * sizeof(bool));
    int nbLines;
    int nbColumns;
    
    // read file
    std::ifstream f(filename);
    getNumbersSymbols(f, numbers, symbols, &nbLines, &nbColumns);
    f.close();

    // get the sum
    uint64_t total = 0;
    for (int j = 0; j < nbColumns; j++) {
        total += computeColumn(numbers, symbols[j], j, nbLines);
        std::cout << "Adding " << computeColumn(numbers, symbols[j], j, nbLines) << std::endl;
    }

    // free memory
    for (int i = 0; i < MAXLINES; i++) {
        free(numbers[i]);
    }
    free(numbers);
    free(symbols);

    return total;
}

int main() {
    uint64_t total = processFile("inputs/day6.txt");
    std::cout << "Total: " << total << std::endl;
    return 0;
}