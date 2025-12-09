#include <fstream>
#include <iostream>
#include <string>
#include <queue>

#define MAXSIZE 200

uint64_t countTimes(bool** isSplitter, uint64_t** nbPossibilities, int sizei, int sizej, int starti, int startj) {

    std::cout << "Recursion at: " << starti << ", " << startj << std::endl;

    // move down until a splitter is found
    int i = starti;
    while (i < sizei && !isSplitter[i][startj]) {
        i += 2;
    }

    // stop the recursion
    if (i == sizei) {
        return 1;
    }
    if (nbPossibilities[i][startj] > 0) {
        std::cout << "Already computed: " << nbPossibilities[i][startj] << std::endl;
        return nbPossibilities[i][startj];
    }

    // check the two new beams
    uint64_t total = 0;
    total += countTimes(isSplitter, nbPossibilities, sizei, sizej, i + 2, startj - 1);
    total += countTimes(isSplitter, nbPossibilities, sizei, sizej, i + 2, startj + 1);
    nbPossibilities[i][startj] = total;

    return total;
}

uint64_t processFile(const std::string& filename) {

    // memory allocation
    int starti, startj;
    int sizei, sizej;
    bool** isSplitter = (bool**) malloc(MAXSIZE * sizeof(bool*));
    for (int i = 0; i < MAXSIZE; i++) {
        isSplitter[i] = (bool*) malloc(MAXSIZE * sizeof(bool));
    }
    uint64_t** nbPossibilities = (uint64_t**) malloc(MAXSIZE * sizeof(uint64_t*));
    for (int i = 0; i < MAXSIZE; i++) {
        nbPossibilities[i] = (uint64_t*) malloc(MAXSIZE * sizeof(uint64_t));
        for (int j = 0; j < MAXSIZE; j++) {
            nbPossibilities[i][j] = 0;
        }
    }

    // file reading
    std::ifstream f(filename);
    char c = ' ';
    int i = 0;
    while (f.peek() != EOF) {
        f.get(c);
        int j = 0;
        while (c != '\n' && c != EOF) {
            isSplitter[i][j] = (c == '^');
            if (c == 'S') {
                starti = i;
                startj = j;
            }
            f.get(c);
            j++;
        }
        sizej = j;
        i++;
    }
    sizei = i;
    f.close();

    // casting the first beam and counting
    uint64_t total = countTimes(isSplitter, nbPossibilities, sizei, sizej, starti, startj);

    // memory deallocation
    for (int i = 0; i < MAXSIZE; i++) {
        free(isSplitter[i]);
        free(nbPossibilities[i]);
    }
    free(isSplitter);
    free(nbPossibilities);

    return total;
}

int main() {
    uint64_t total = processFile("inputs/day7.txt");
    std::cout << "Total: " << total << std::endl;
    return 0;
}