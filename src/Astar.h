#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>


// Structure to represent a node in the grid
struct Node {
    int x, y; // Coordinates
    int gCost, hCost; // G cost (cost from start), H cost (heuristic cost to goal)
    Node* parent; // Pointer to the parent node

    Node(int x, int y) : x(x), y(y), gCost(0), hCost(0), parent(nullptr) {}

    // Calculate the total cost (fCost)
    int fCost() const { return gCost + hCost; }
};

// Comparison struct for priority queue
struct CompareNodes {
    bool operator()(const Node* a, const Node* b) const {
        return a->fCost() > b->fCost();
    }
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2; // XOR for combined hash
    }
};
std::vector<Node*> aStar(Node* start, Node* goal, const std::vector<std::vector<int>>& grid) ;