#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

void getFreshIngredients(std::ifstream& f, std::vector<uint64_t>& freshIngredients) {
    std::string line;
    while (std::getline(f, line)) {
        uint64_t ingredientId = std::stoull(line);
        freshIngredients.push_back(ingredientId);
    }
}

uint64_t countFresh(const std::vector<uint64_t*>& ranges, const std::vector<uint64_t>& freshIngredients) {
    uint64_t countFresh = 0;
    for (const auto& ingredient : freshIngredients) {
        std::cout << "Checking ingredient: " << ingredient << std::endl;
        for (const auto& range : ranges) {
            if (ingredient >= range[0] && ingredient <= range[1]) {
                countFresh++;
                break;
            }
        }
    }
    return countFresh;
}

uint64_t processFile(std::string filename) {
    std::ifstream f(filename);
    std::vector<uint64_t*> ranges;
    std::vector<uint64_t> freshIngredients;
    getRanges(f, ranges);
    getFreshIngredients(f, freshIngredients);
    f.close();
    uint64_t count = countFresh(ranges, freshIngredients);
    for (const auto& range : ranges) {
        free(range);
    }
    return count;
}

int main() {
    uint64_t countFresh = processFile("inputs/day5.txt");
    std::cout << "Count of fresh ingredients: " << countFresh << std::endl;
    return 0;
}