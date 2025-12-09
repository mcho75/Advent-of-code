#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>

#define ITERATIONS 1000
#define SUM_CLASSES 3

struct junctionBox {
    uint64_t x;
    uint64_t y;
    uint64_t z;
    junctionBox* rep = nullptr;
    uint64_t sizeClass = 0;
};
typedef struct junctionBox junctionBox;

struct distanceInfo {
    junctionBox* box1;
    junctionBox* box2;
    uint64_t dist;
};
typedef struct distanceInfo distanceInfo;

junctionBox* findRep(junctionBox* box) {
    if (box->rep == box) {
        return box;
    }
    box->rep = findRep(box->rep);
    return box->rep;
}

bool operator>(const distanceInfo& a, const distanceInfo& b) {
    return a.dist > b.dist;
}

void computeDistances(std::vector<junctionBox*>& boxes,
    std::priority_queue<distanceInfo, std::vector<distanceInfo>, std::greater<distanceInfo>>& distances) {
    for (std::size_t i = 0; i < boxes.size(); i++) {
        for (std::size_t j = 0; j < i; j++) {
            uint64_t dist = std::sqrt(
                (boxes[i]->x - boxes[j]->x) * (boxes[i]->x - boxes[j]->x) +
                (boxes[i]->y - boxes[j]->y) * (boxes[i]->y - boxes[j]->y) +
                (boxes[i]->z - boxes[j]->z) * (boxes[i]->z - boxes[j]->z)
            );
            distances.push({boxes[i], boxes[j], dist});
        }
    }
}

void linkClosestBoxes(std::priority_queue<distanceInfo, std::vector<distanceInfo>, std::greater<distanceInfo>>& distances) {
    for (int i = 0; i < ITERATIONS; i++) {
        distanceInfo info = distances.top();
        distances.pop();
        if (findRep(info.box1) != findRep(info.box2)) {
            findRep(info.box1)->rep = findRep(info.box2);
        }
    }
}

uint64_t sizeClasses(std::vector<junctionBox*>& boxes) {
    for (auto& box : boxes) {
        junctionBox* rep = findRep(box);
        rep->sizeClass++;
        if (rep != box) {
            box->sizeClass = 0;
        }
    }
    std::priority_queue<uint64_t> sizes;
    for (auto& box : boxes) {
        if (box->sizeClass != 0) {
            std::cout << "(" << box->x << ", " << box->y << ", " << box->z << ") class of size " << box->sizeClass << std::endl;
            sizes.push(box->sizeClass);
        }
    }
    uint64_t total = 1;
    for (int i = 0; i < SUM_CLASSES; i++) {
        total *= sizes.top();
        sizes.pop();
    }
    return total;
}

uint64_t processFile(const std::string& filename) {
    std::vector<junctionBox*> boxes;
    std::priority_queue<distanceInfo, std::vector<distanceInfo>, std::greater<distanceInfo>> distances;

    // read file
    std::ifstream f(filename);
    std::string line;
    std::getline(f, line);
    while (!line.empty()) {
        std::size_t delim1 = line.find(',');
        std::size_t delim2 = line.find(',', delim1 + 1);
        junctionBox* box = new junctionBox({
            std::stoull(line.substr(0, delim1)),
            std::stoull(line.substr(delim1 + 1, delim2)),
            std::stoull(line.substr(delim2 + 1, line.size()))
        });
        box->rep = box;
        boxes.push_back(box);
        std::getline(f, line);
    }
    f.close();

    // compute distances between boxes and process them
    computeDistances(boxes, distances);
    linkClosestBoxes(distances);
    uint64_t total = sizeClasses(boxes);

    // free memory
    for (const auto& box : boxes) {
        delete box;
    }
    return total;
}

int main() {
    uint64_t size = processFile("inputs/day8.txt");
    std::cout << "Total size : " << size << std::endl;
    return 0;
}