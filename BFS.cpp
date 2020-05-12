//C++ implementation of Bellman-Ford algorithm
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> 

using namespace std; 

int inf = numeric_limits<int>::max();
// To add an edge 
void addEdge(vector<vector<int>> &adj, int u, int v) { 
    adj[u].push_back(v);
} 
  
// Print adjacency list representaion ot graph 
void printGraph(vector<vector<int>> adj, int V) { 
    int v;
    for (int u = 0; u < V; u++) { 
        cout << "Node " << u << " makes an edge with \n"; 
        for (v = 0; v < (int) adj[u].size(); v++)  {
            cout << "\tNode " << adj[u][v] << ".\n";
        } 
        cout << "\n"; 
    } 
} 

int deQueue(vector<int> &queue) {
    int v = queue.at(0);
    queue.erase(queue.begin());
    return v;
}

bool auxBFS(vector<vector<int>> adj, vector<int> &queue, vector<int> &prev, int vf) {
    int v = deQueue(queue);
    for(int u; u < (int) adj[v].size(); u++) {
        if(prev[adj[v][u]] != -1) continue;
        else if(adj[v][u] == vf) {
            prev[vf] = v;
            return true;
        }

        queue.push_back(adj[v][u]);
        prev[adj[v][u]] = v;
    }
    return false;
}

void runBFS(vector<vector<int>> &adj, vector<int> &queue, vector<int> &prev) {
    bool flag = false;
    queue.push_back(2); //starting vertice is first in queue;

    while(!flag) 
        flag = auxBFS(adj, queue, prev, 1);
    
}


int main() {
    int V = 6;
    vector<vector<int>> adj;
    vector<int> queue;
    vector<int> prev;
    adj.resize(V);
    prev.resize(V);

    for(int i = 0; i < V; i++) prev[i] = -1;

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 5);
    addEdge(adj, 3, 1);
    addEdge(adj, 3, 4);
    addEdge(adj, 4, 2);
    addEdge(adj, 4, 5);
    addEdge(adj, 5, 0);
    addEdge(adj, 5, 3);

    printGraph(adj, V);

    runBFS(adj, queue, prev);
    int v = 1;
    int i = 2;
    printf("O caminho mais rápido do vértice %d ao vértice %d é (por backtracking):\n", i, v);
    i = 0;
    while(v != -1) {
        printf("\t%d - Vértice %d\n", ++i, v);
        v = prev[v];
    }

    return 0;
}