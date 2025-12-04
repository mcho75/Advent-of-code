#include <fstream>
#include <iostream>
#include <string>

#define LINE 135
#define COLUMN 135

int countNeighbors(bool** isPaper, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                int newX = x + i;
                int newY = y + j;
                if (newX >= 0 && newX < LINE && newY >= 0 && newY < COLUMN) {
                    if (isPaper[newX][newY]) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}

int nbAccessiblePapers(bool** isPaper) {
    int total = 0;
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            int nbNeighbors = 0;
            if (isPaper[i][j]) {
                if (countNeighbors(isPaper, i, j) < 4) {
                    total++;
                }
            }
        }
    }
    return total;
}

bool** processFile(std::ifstream& f) {
    char ch;
    bool** isPaper = (bool**) malloc(LINE * sizeof(bool*));
    for (int i = 0; i < LINE; i++) {
        isPaper[i] = (bool*) malloc(COLUMN * sizeof(bool));
        for (int j = 0; j < COLUMN; j++) {
            f.get(ch);
            isPaper[i][j] = (ch == '@');
        }
        f.get(ch);
    }
    return isPaper;
}

int main() {
    std::ifstream f("inputs/day4.txt");
    bool** isPaper = processFile(f);
    std::cout << "Number of accessible papers: " << nbAccessiblePapers(isPaper) << std::endl;
    f.close();
    for (int i = 0; i < LINE; i++) {
        free(isPaper[i]);
    }
    free(isPaper);
    return 0;
}