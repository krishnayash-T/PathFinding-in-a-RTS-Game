#include "Astar.h"

// Function to calculate the Manhattan distance heuristic
int manhattanDistance(const Node* a, const Node* b) {
    return std::abs(a->x - b->x) + std::abs(a->y - b->y);
}

// A* pathfinding algorithm
std::vector<Node*> aStar(Node* start, Node* goal, const std::vector<std::vector<int>>& grid) 
{
    std::priority_queue<Node*, std::vector<Node*>, 
                        struct CompareNodes> openList; 
    std::unordered_map<Node*, bool> closedList;

    int dirX[] ={-1,0,1,0}; // (-1,0),(0,1),(1,0),(0,-1) - four directions to explore neighbours
    int dirY[] = {0,1,0,-1};

    openList.push(start);
    std::cout <<"Starting A star While loop\n";
    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();
        closedList[current] = true;
        //std::cout <<"Current X:"<<current->x << "Current Y:"<<current->y <<"\n";
        if (current == goal) {
            // Reconstruct the path
            std::vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            reverse(path.begin(), path.end());
            std::cout <<"Found Path\n";
            return path;
        }

        // Explore neighbors
        for(int i=0;i<4;i++)// Only need to explore forward-back and left and right
        {
            int nx = current->x + dirX[i];
            int ny = current->y + dirY[i];

            // Check if the neighbor is within bounds and not an obstacle
            if (nx >= 0 && nx < grid[0].size() && ny >= 0 && ny < grid.size() && grid[nx][ny] != 3) 
            {
                
                Node* neighbor = new Node(nx, ny);
                neighbor->gCost = current->gCost + 1; // Discrete Steps (The movement of a unit on the batlefield from one posi�on to the next is discrete and occurs in
                                                       // single steps. Units never occupy a position par�ally.)
                neighbor->hCost = manhattanDistance(neighbor, goal);
                neighbor->parent = current;

                if (!closedList[neighbor]) 
                {
                    openList.push(neighbor);
                }
            }
        }
    }

    return std::vector<Node*>(); // No path found
}
