#include "Astar.h"

// Function to calculate the Manhattan distance heuristic
int manhattanDistance(const Node* a, const Node* b) {
    return std::abs(a->x - b->x) + std::abs(a->y - b->y);
}

// A* pathfinding algorithm
std::vector<Node*> aStar(Node* start, Node* goal, const std::vector<std::vector<int>>& grid) 
{
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openList;
    std::unordered_map<std::pair<int, int>, bool, pair_hash> closedList;

    int dirX[] = {-1, 0, 1, 0};
    int dirY[] = {0, 1, 0, -1};

    openList.push(start);
    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (closedList[{current->x, current->y}])
            continue;

        closedList[{current->x, current->y}] = true;

        if (current->x == goal->x && current->y == goal->y) {
            std::vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; i++) {
            int nx = current->x + dirX[i];
            int ny = current->y + dirY[i];

            if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] != 3) {
                Node* neighbor = new Node(nx, ny);
                neighbor->gCost = current->gCost + 1;
                neighbor->hCost = manhattanDistance(neighbor, goal);
                neighbor->parent = current;

                if (!closedList[{nx, ny}]) {
                    openList.push(neighbor);
                } else {
                    delete neighbor;  // Clean up to prevent memory leak
                }
            }
        }
    }
    return {}; // No path found
}
