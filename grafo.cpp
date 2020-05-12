#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> 

using namespace std; 

//int inf = numeric_limits<int>::max();

typedef struct vertex {
    //int num;
    int nPrev = -1;
    vector<int> adj;
} Vertex;
  
// Print adjacency list representaion ot graph 
void printGraph(vector<Vertex> vertexes, int V) { 
    int v;
    for (int u = 0; u < V; u++) { 
        cout << "Node " << u << " makes an edge with \n"; 
        for (v = 0; v < (int) vertexes[u].adj.size(); v++)  {
            cout << "\tNode " << vertexes[u].adj[v] << ".\n";
        } 
        cout << "\n"; 
    } 
} 

int coordsToInt(int x, int y, int xMax) {
    return (y - 1) * xMax + x;
}

void addEdge(vector<Vertex> &vertexes, int u, int v) { 
    vertexes[u].adj.push_back(v);
    vertexes[v].adj.push_back(u);
} 

void addExtremes(vector<Vertex> &vertexes, int v, int n, int xMax) {
    int x, y;
    for(int i = 0; i < n; i ++) {
        cin >> y >> x;
        addEdge(vertexes, v, coordsToInt(x, y, xMax));
    }
}

void makeGraph(vector<Vertex> &vertexes, int xMax, int yMax) {
    for(int y = 1; y <= yMax; y++) {
        for(int x = 1; x <= xMax; x++) {
            if(y != yMax)
                addEdge(vertexes, coordsToInt(x, y, xMax), coordsToInt(x, y + 1, xMax));
            if(x != xMax)
                addEdge(vertexes, coordsToInt(x, y, xMax), coordsToInt(x + 1, y, xMax));
        }
    }
}

int main() {
    int xMax, yMax, nSp, nCt;
    cin >> xMax >> yMax;
    cin >> nSp >> nCt;

    int V = xMax * yMax + 2;
    vector<Vertex> vertexes;

    for(int i = 0; i < V; i++) {
        vertexes.push_back(Vertex());
    }

    addExtremes(vertexes, V - 1, nSp, xMax);
    addExtremes(vertexes, 0, nCt, xMax);

    makeGraph(vertexes, xMax, yMax);  

    printGraph(vertexes, V);  

    return 0;
}