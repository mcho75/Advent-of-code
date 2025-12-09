#include <fstream>
#include <iostream>
#include <string>
#include <queue>

#define MAXSIZE 200

struct tuple {
    int posi;
    int posj;
};
typedef struct tuple tuple;

void printArray(bool** isSplitter, bool** isBeam, int sizei, int sizej) {
    for (int i1 = 0; i1 < sizei; i1++) {
        for (int j1 = 0; j1 < sizej; j1++) {
            std::cout << (isBeam[i1][j1] ? '|' : (isSplitter[i1][j1] ? '^' : '.'));
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool operator>(const tuple& a, const tuple& b) {
    return a.posi > b.posi;
}

int countBeams(bool** isSplitter, int sizei, int sizej, int starti, int startj) {

    bool** isBeam = (bool**) malloc(MAXSIZE * sizeof(bool*));
    for (int i = 0; i < MAXSIZE; i++) {
        isBeam[i] = (bool*) malloc(MAXSIZE * sizeof(bool));
        for (int j = 0; j < MAXSIZE; j++) {
            isBeam[i][j] = false;
        }
    }

    int total = 0;
    std::priority_queue<tuple, std::vector<tuple>, std::greater<tuple>> currentBeams;
    currentBeams.push({starti, startj});
    while (!currentBeams.empty()) {
        tuple beam = currentBeams.top();
        currentBeams.pop();
        if (!isBeam[beam.posi][beam.posj]) {
            std::cout << "Beam at: " << beam.posi << ", " << beam.posj << std::endl;
            int i = beam.posi;
            while (i < sizei && !isSplitter[i][beam.posj]) {
                isBeam[i][beam.posj] = true;
                i += 2;
            }
            if (isSplitter[i][beam.posj]) {
                currentBeams.push({i, beam.posj - 1});
                currentBeams.push({i, beam.posj + 1});
                total++;
            }
        }
    }

    for (int i = 0; i < MAXSIZE; i++) {
        free(isBeam[i]);
    }
    free(isBeam);

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
    sizei = i - 1;
    f.close();

    // casting the first beam and counting
    int total = countBeams(isSplitter, sizei, sizej, starti, startj);

    // memory deallocation
    for (int i = 0; i < MAXSIZE; i++) {
        free(isSplitter[i]);
    }
    free(isSplitter);

    return total;
}

int main() {
    uint64_t total = processFile("inputs/day7.txt");
    std::cout << "Total: " << total << std::endl;
    return 0;
}