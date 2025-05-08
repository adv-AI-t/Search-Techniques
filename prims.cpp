/*

Let us understant the Prim's Algorithm for Minimum Spanning Tree (MST):

1. We start with a graph represented as an adjacency list.
2. We use a min-heap to keep track of the edges with the smallest weights.
3. We maintain a visited list to keep track of the nodes that have been added to the MST.
4. We initialize the min-heap with the starting node and its weight.
5. We repeatedly extract the minimum edge from the heap, add it to the MST, and push its unvisited neighbors into the heap.
6. The process continues until all nodes are included in the MST.
7. Finally, we print the edges included in the MST and the total cost.

*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Graph{
    // lets define an adjacency list
    public:
    unordered_map<string, vector<pair<string, int>>> adj_list;

    //here the key is a node, and the value is vector of pairs of adjacent nodes and weights

    //we need to add an undirected edge

    void addEdge(string &node1, string &node2, int weight){
        adj_list[node1].push_back({node2, weight});
        adj_list[node2].push_back({node1, weight});
    }

    void print() {
        for (const auto &entry : adj_list) {
            cout << entry.first << ": ";
            for (const auto &neighbor : entry.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

// Let's talk business

//PRIMS ALGORITHM

void prims(Graph &graph){
    //we need a data structure to store visited nodes

    unordered_map<string, bool> visited;

    //we need a min heap to store the edges with the smallest weights

    priority_queue<tuple<int, string, string>, vector<tuple<int, string, string>>, greater<>> min_heap;

    //lets choose first node as starting node

    string start_node = graph.adj_list.begin()->first;

    min_heap.push({0, start_node, ""});

    //define the min cost

    int min_cost = 0;

    while(!min_heap.empty()){
        //  get the top element of the heap
        // this will be the edge with the smallest weight
        auto[weight, current, parent] = min_heap.top();
        min_heap.pop();

        //if it is already visited, skip it
        if(visited[current]) continue;
        visited[current] = true;

        if(!parent.empty()){
            cout<<"Edge added: "<<parent<<" - "<<current<<", weight = "<<weight<<endl;
            min_cost += weight;
        }

        for(const auto &neighbor : graph.adj_list[current]){
            //if the neighbor is not visited, push it into the heap
            if(!visited[neighbor.first]){
                min_heap.push({neighbor.second, neighbor.first, current});
            }
        }
    }
}

int main() {
    Graph graph;

    // Input loop for edges
    cout << "Enter edges in the format:\n";
    cout << "FirstNode SecondNode Weight (example: A B 5)\n";
    cout << "Enter '-' as FirstNode to finish input.\n";

    while (true) {
        string node_a, node_b;
        int weight;

        cout << "Enter first node: ";
        cin >> node_a;
        if (node_a == "-") break;

        cout << "Enter second node: ";
        cin >> node_b;

        cout << "Enter weight: ";
        cin >> weight;

        graph.addEdge(node_a, node_b, weight);
    }

    // Display the graph structure
    cout << "\nGraph adjacency list:\n";
    graph.print();

    // Run Prim's Algorithm
    cout << "\nMinimum Spanning Tree (Prim's Algorithm):\n";
    prims(graph);

    return 0;
}