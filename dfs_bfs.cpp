#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

class Graph{
    private:
    int v;
    vector<vector<int> >adj;
    public:
    Graph(int v){
        this->v = v;
        for(int i=0; i<v; i++){
            vector<int> row(v, 0);
            this->adj.push_back(row);
        }
    }

    void add_edge(int x, int y){
        if (x >= 0 && x < v && y >= 0 && y < v){
            adj[x][y] = true;
            adj[y][x] = true;
        }
        else {
            cout << "Invalid edge: " << x << " - " << y << endl;
        }
    }

    void dfs(int start = 0){
        cout << "\nDFS traversal: ";
        vector<int>visited(v, false);
        visited[start] = true;
        stack<int>st;
        st.push(start);

        while(!st.empty()){
            int node = st.top();
            cout << node << " ";
            st.pop();
            for(int i=0; i<v; i++){
                if(adj[node][i] && !visited[i]){
                    st.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    void bfs(int start = 0){
        cout << "BFS traversal: ";
        vector<int>visited(v, false);
        queue<int>q;
        q.push(start);
        visited[start] = true;
        
        while(!q.empty()){
            int node = q.front();
            cout << node << " ";
            q.pop();
            
            for(int i = 0; i < v; i++){
                if(adj[node][i] && !visited[i]){
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    bool dfs_search(int start, int target) {
        cout << "\nDFS Search for node " << target << ": ";
        vector<int>visited(v, false);
        vector<int>parent(v, -1);
        stack<int>st;
        
        st.push(start);
        visited[start] = true;
        bool found = false;
        
        while(!st.empty() && !found) {
            int node = st.top();
            cout << node << " ";
            
            if(node == target) {
                found = true;
                break;
            }
            
            st.pop();
            for(int i=0; i<v; i++) {
                if(adj[node][i] && !visited[i]) {
                    st.push(i);
                    visited[i] = true;
                    parent[i] = node;
                }
            }
        }
        
        if(found) {
            cout << "\nPath to target: ";
            vector<int> path;
            int current = target;
            while(current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            for(int i = path.size()-1; i >= 0; i--) {
                cout << path[i];
                if(i > 0) cout << " -> ";
            }
            cout << endl;
            return true;
        }
        
        cout << "\nTarget not found!" << endl;
        return false;
    }
    
    bool bfs_search(int start, int target) {
        cout << "\nBFS Search for node " << target << ": ";
        vector<int>visited(v, false);
        vector<int>parent(v, -1);
        queue<int>q;
        
        q.push(start);
        visited[start] = true;
        bool found = false;
        
        while(!q.empty() && !found) {
            int node = q.front();
            cout << node << " ";
            
            if(node == target) {
                found = true;
                break;
            }
            
            q.pop();
            for(int i = 0; i < v; i++) {
                if(adj[node][i] && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                    parent[i] = node;
                }
            }
        }
        
        if(found) {
            cout << "\nPath to target: ";
            vector<int> path;
            int current = target;
            while(current != -1) {
                path.push_back(current);
                current = parent[current];
            }
            for(int i = path.size()-1; i >= 0; i--) {
                cout << path[i];
                if(i > 0) cout << " -> ";
            }
            cout << endl;
            return true;
        }
        
        cout << "\nTarget not found!" << endl;
        return false;
    }
};

int main(){
    Graph g = Graph(6);

    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 2);
    g.add_edge(1, 4);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 4);

    cout << "Regular traversals:" << endl;
    g.bfs();
    g.dfs();

    // Test searching
    g.bfs_search(0, 4);  // Search for node 4 starting from node 0
    g.dfs_search(0, 3);  // Search for node 3 starting from node 0
    g.bfs_search(0, 5);  // Search for non-existent node 5

    return 0;
}