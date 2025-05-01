#include<iostream>
#include<vector>
#include<algorithm>
#include <cfloat>
#include<set>

using namespace std;


/*
Let's learn about A star Algorithm for path finding:

We have a grid of MxN which consists of 0s and 1s
0s represent a free path, whereas 1s represent obstacle, so the path cannot pass through that cell.alignas

We have coordinates of the start node and the target node.

Our job is to used informed search technique to reach the target node, without exploring all the options (without being Greedy!)

For that we will use a heuristic cost function "h" that will give us the approximate/estimated cost from current Node to the target Node.alignas
Here, we have choice to use any function, but for simplicity and efficiency, let's use the Manhattan distance.

MANHATTAN DISTANCE:

manhattan(currentNode, targetNode) -> absolute_difference(currentNode.x, targetNode.x) + absolute_difference(currentNode.y, targetNode.y)

Along with this, we need to combine the actual cost "g"
Together with g and h, we get the total cost "f"

Starting with 0 at startNode, we just need to increment g by 1 after each move.

EXPLORING THE NEAGHBORS:

Here, let's allow movement only row wise and column wise. Therefore we can change the position by 4 combinations in total:
1. (1, 0)
2. (-1, 0)
3. (0, 1)
4. (0, -1)

Going further, if we want to allow diagonal movements, we can also include (1, 1), (1, -1), (-1, 1), and (-1, -1). 

EXAMPLE:

Grid (0=free, 1=obstacle):
0 1 0 0 0 
0 1 0 1 0 
0 1 0 1 0 
0 0 0 1 0 
0 0 0 0 0 

Type 1: Only vertical and horizontal movement allowed: 

Finding path from (0,0) to (4,4)
(0,0) (1,0) (2,0) (3,0) (4,0) (4,1) (4,2) (4,3) (4,4)

Type 2: Diagonal movement allowed:

Finding path from (0,0) to (4,4)
(0,0) (1,0) (2,0) (3,1) (4,2) (4,3) (4,4) 


*/


class Node{
    public:
    int x, y;
    float h, g, f;
    Node* parent;

    Node(int x, int y, float h = FLT_MAX, float g = FLT_MAX){
        this->x = x;
        this->y = y;
        this->h = h;
        this->g = g;
        this->f = g + h;
        this->parent = nullptr;
    }
};

const int dx[] = {1, -1, 0, 0, 1, 1, -1, -1};
const int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};

int heuristic(Node *a, Node *b){
    return abs(a->x - b->x) + abs(a->y - b->y);
}

bool isValid(int x, int y, vector<vector<int> >&grid){
    return (x >= 0 && y >= 0 && x < grid.size() && y < grid[0].size() && grid[x][y] == 0);
}

struct CompareNodes {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;  // min-heap behavior
    }
};

bool reachedGoal(Node *a, Node *target){
    return (a->x == target->x && a->y == target->y);
}

void aStar(vector<vector<int> >&grid, pair<int, int> &start, pair<int, int> &target){

    priority_queue<Node*, vector<Node*>, CompareNodes> openList;    

    set<pair<int, int>> closedList;

    Node* startNode = new Node(start.first, start.second);
    Node* targetNode = new Node(target.first, target.second);
    startNode->g = 0;
    startNode->h = heuristic(startNode, targetNode);
    openList.push(startNode);

    while(!openList.empty()){

        Node* current = openList.top();
        openList.pop();


        if(reachedGoal(current, targetNode)){
            vector<pair<int, int>> path;
            while(current != nullptr){
                path.push_back({current->x, current->y});
                current = current -> parent;
            }
            reverse(path.begin(), path.end());
            for(auto p : path){
                cout<<"("<<p.first<<","<<p.second<<") ";
            }
            cout<<endl;
            return;
        }

        
        closedList.insert({current->x, current->y});

        for(int i=0; i<8; i++){
            int newx = current->x + dx[i];
            int newy = current->y + dy[i];

            if(isValid(newx, newy, grid) && closedList.find({newx, newy})==closedList.end()){
                Node* neighbor = new Node(newx, newy);
                neighbor->g = current->g + 1;
                neighbor->h = heuristic(neighbor, current);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;

                openList.push(neighbor);
            }
        }
    }

    cout<<"NO PATH FOUND!"<<endl;
}

int main() {
    int rows = 5, cols = 5;
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    
    grid[0][1] = 1;
    grid[1][1] = 1;
    grid[2][1] = 1;
    grid[1][3] = 1;
    grid[2][3] = 1;
    grid[3][3] = 1;
    
    cout << "Grid (0=free, 1=obstacle):\n";
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    
    pair<int, int> start = {0, 0}; 
    pair<int, int> target = {4, 4};
    
    cout << "\nFinding path from (" << start.first << "," << start.second << ") to ("
         << target.first << "," << target.second << ")\n\n";

    aStar(grid, start, target);
    
    return 0;
}





