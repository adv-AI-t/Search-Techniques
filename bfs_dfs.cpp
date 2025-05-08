#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class Graph{

    public:
    unordered_map<string, vector<string>> adj_list;

    void add_edge(string node1, string node2){
        adj_list[node1].push_back(node2);
        adj_list[node2].push_back(node1);
    }

    void DFS(string node, unordered_map<string, bool> &visited){
        visited[node] = true;
        cout<<node<<" ";
        for(string nbr: adj_list[node]){
            if(!visited[nbr]){
                DFS(nbr, visited);
            }
        }
        return;
    }

    void BFSRecursive(unordered_map<string, bool> &visited, queue<string> &q){
        if(q.empty()) return;

        string node = q.front();
        cout<<node<<" ";
        q.pop();

        for(string nbr: adj_list[node]){
            if(!visited[nbr]){
                visited[nbr] = true;
                q.push(nbr);
            }
        }

        BFSRecursive(visited, q);
    }

    void BFS(string node, unordered_map<string, bool> &visited){
        visited[node] = true;
        queue<string> q;
        q.push(node);
        BFSRecursive(visited, q);
    }
};

int main() {
    Graph g;
    g.add_edge("A", "B");
    g.add_edge("A", "C");
    g.add_edge("B", "D");
    g.add_edge("C", "D");

    unordered_map<string, bool> visited;
    cout << "DFS: ";
    g.DFS("A", visited);

    cout << "\nBFS: ";
    visited.clear();
    g.BFS("A", visited);
}
