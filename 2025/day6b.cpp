#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MAXLINES 10
#define MAXCOLUMNS 2000

void getNumbersSymbols(std::ifstream& f, char** numbers, int* nbLines, int* nbColumns) {
    int i = 0;
    char c;
    f.get(c);
    while (f.peek() != EOF) {
        int j = 0;
        while (c != '\n') {
            numbers[i][j] = c;
            f.get(c);
            j++;
        }
        f.get(c);
        *nbColumns = j;
        i++;
    }
    *nbLines = i;
}

uint64_t computeFromColumn(char** numbers, int nbLines, int nbColumns, int start) {
    bool isMult = numbers[nbLines - 1][start] == '*';
    uint64_t total = isMult;
    std::cout << "start = " << start << std::endl;
    for (int j = start; j < nbColumns && (j == nbColumns - 1 || numbers[nbLines - 1][j + 1] == ' '); j++) {
        uint64_t columnNumber = 0;
        for (int i = 0; i < nbLines - 1; i++) {
            if (numbers[i][j] != ' ') {
                columnNumber = columnNumber * 10 + (uint64_t) (numbers[i][j] - '0');
            }
        }
        std::cout << "  Computed column " << j << ": " << columnNumber << std::endl;
        if (isMult) {
            total *= columnNumber;
        }
        else {
            total += columnNumber;
        }
    }
    return total;
}

uint64_t processFile(std::string filename) {

    // allocate memory
    char** numbers = (char**) malloc(MAXLINES * sizeof(uint64_t*));
    for (int i = 0; i < MAXLINES; i++) {
        numbers[i] = (char*) malloc(MAXCOLUMNS * sizeof(uint64_t));
    }
    int nbLines;
    int nbColumns;
    
    // read file
    std::ifstream f(filename);
    getNumbersSymbols(f, numbers, &nbLines, &nbColumns);
    f.close();

    // get the sum
    uint64_t total = 0;
    for (int j = 0; j < nbColumns; j++) {
        if (numbers[nbLines - 1][j] != ' ') {
            total += computeFromColumn(numbers, nbLines, nbColumns, j);
        }
    }

    // free memory
    for (int i = 0; i < MAXLINES; i++) {
        free(numbers[i]);
    }
    free(numbers);

    return total;
}

int main() {
    uint64_t total = processFile("inputs/day6.txt");
    std::cout << "Total: " << total << std::endl;
    return 0;
}