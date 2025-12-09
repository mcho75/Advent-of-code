#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cmath>

struct junctionBox {
    uint64_t x;
    uint64_t y;
    uint64_t z;
    junctionBox* rep = nullptr;
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

uint64_t linkClosestBoxes(std::priority_queue<distanceInfo, std::vector<distanceInfo>, std::greater<distanceInfo>>& distances) {
    std::vector<distanceInfo> connected;
    while (!distances.empty()) {
        distanceInfo info = distances.top();
        distances.pop();
        if (findRep(info.box1) != findRep(info.box2)) {
            findRep(info.box1)->rep = findRep(info.box2);
            connected.push_back(info);
        }
    }
    distanceInfo last = connected.back();
    return last.box1->x * last.box2->x;
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
    uint64_t total = linkClosestBoxes(distances);

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