#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void getRanges(std::ifstream& f, std::vector<uint64_t*>& ranges) {
    std::string line;
    std::getline(f, line);
    while (!line.empty()) {
        uint64_t* range = (uint64_t*) malloc(2 * sizeof(uint64_t));
        std::size_t space_idx = line.find('-');
        range[0] = std::stoull(line.substr(0, space_idx));
        range[1] = std::stoull(line.substr(space_idx + 1, line.size() - space_idx - 1));
        ranges.push_back(range);
        std::getline(f, line);
    }
}

bool comp(const uint64_t* range1, const uint64_t* range2) {
    return range1[0] < range2[0];
}

uint64_t countFresh(std::vector<uint64_t*>& ranges) {
    uint64_t countFresh = 0;
    sort(ranges.begin(), ranges.end(), comp);
    const uint64_t* prec = ranges[0];
    uint64_t start = prec[0];
    uint64_t end = prec[1];
    for (const auto& range : ranges) {
        if (prec[1] >= range[0]) {
            end = std::max(std::max(prec[1], range[1]), end);
        }
        else {
            countFresh += end - start + 1;
            start = range[0];
            end = range[1];
        }
        prec = range;
    }
    countFresh += end - start + 1;
    return countFresh;
}

uint64_t processFile(std::string filename) {

    // read file
    std::ifstream f(filename);
    std::vector<uint64_t*> ranges;
    getRanges(f, ranges);
    f.close();

    // compute count of fresh ingredients
    uint64_t count = countFresh(ranges);
    
    // free allocated memory
    for (const auto& range : ranges) {
        free(range);
    }

    // return count
    return count;
}

int main() {
    uint64_t countFresh = processFile("inputs/day5.txt");
    std::cout << "Count of possible fresh ingredients: " << countFresh << std::endl;
    return 0;
}