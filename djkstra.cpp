#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

class Graph{

    public:

    unordered_map<string, vector<pair<string, int>>> adj_list;

    void add_edge(string node1, string node2, int weight){
        adj_list[node1].push_back({node2, weight});
        adj_list[node2].push_back({node1, weight});
    }

    void show_adj_list(){
        for(auto item : adj_list){
            cout<<item.first<<" --> ";
            for(auto nbr : item.second){
                cout<<"( "<<nbr.first<<" @ "<<nbr.second<<" )";
            }
            cout<<endl<<endl;
        }
    }
};

void djkstra(Graph &graph, string start_node){

    unordered_map<string, int> distance;
    unordered_map<string, bool> visited;

    //set the distance to infinity 
    for(auto item : graph.adj_list){
        distance[item.first] = INT_MAX;
    }

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> heap;

    distance[start_node] = 0;

    heap.push({0, start_node});

    /*
    In the while looooop,

    1. fetch to top values of the heap (distance and node)
    2. pop it
    3. if it is marked as visited, continue
    4. if not, the mark it as visited and do the next steps
    5. Print the node and the distance
    6. run a loop for getting all the neighbors of that node from the adjacency list
    7. Store the neighbor ID in next_node and the weight in weight
    8. check if the neighbor is visited or not and whether its distance is greater than dist + weight, if yes update the distance with dist + weight and push it into the heap
    
    ZALAAA THAT'S IT
    */

    while(!heap.empty()){

        auto[dist, node] = heap.top();
        heap.pop();

        if(visited[node])continue;
        visited[node] = true;

        cout<<"VISITED: "<<node<<" at distance "<<dist<<endl;

        for(auto nbr : graph.adj_list[node]){
            string nextnode = nbr.first;
            int weight = nbr.second;

            if(!visited[nextnode] && distance[nextnode] > dist + weight){
                distance[nextnode] = dist + weight;
                heap.push({distance[nextnode], nextnode});
            }

        }

    }

}

int main(){
    Graph graph;

    string node1;
    string node2;
    int weight;

    while(1){
        cout<<"Enter node1";
        cin>>node1;
        if(node1 =="-") break;
        cout<<"Enter node2";
        cin>>node2;
        cout<<"Enter weight";
        cin>>weight;

        graph.add_edge(node1, node2, weight);
    }

    string startnode;

    cout<<"Enter start node:";
    cin>>startnode;

    djkstra(graph, startnode);

    return 0;
}


/*
Test with this:

A B 7 B C 3 C D 6 D E 7 E A 1 E B 8 E C 2 -

*/