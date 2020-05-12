#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> 

using namespace std; 

//int inf = numeric_limits<int>::max();

typedef struct vertex {
    int run = 0;
    bool infected = false;
    int nPrev = -1;
    vector<int> adj;
} Vertex;
  
  /*
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
*/
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
        cin >> x >> y;
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

bool runBFS(vector<Vertex> &vertexes, vector<int> &queue, int cRun, int V) {
    int v = queue[0];
    queue.erase(queue.begin());


    for(int i = 0; i < (int) vertexes[v].adj.size(); i++) {
        int u = vertexes[v].adj[i];

        if(cRun == vertexes[u].run || vertexes[u].infected) continue; //check if vertex can ve visited

        queue.push_back(u);

        vertexes[u].nPrev = v;
        vertexes[u].run = cRun;

        if(u == V - 1) return true; //check if reached sink or BFS stopped
    }

    return false;
}

int runEdmundo(vector<Vertex> &vertexes, int V) {
    vector<int> queue;
    int cRun = 0;
    int flux = 0;

    while(true) {
        bool flag = false;

        cRun++;
        queue.push_back(0);

        while(!flag) {
            flag = runBFS(vertexes, queue, cRun, V);
            if((int) queue.size() == 0) return flux;
        }


        flux++;
        queue.clear();

        int v = vertexes[V - 1].nPrev;
        while(v != 0) {
            vertexes[v].infected = true;        
            v = vertexes[v].nPrev;
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

    //printGraph(vertexes, V);  

    int flux = runEdmundo(vertexes, V);

    printf("%d\n", flux);

    return 0;
}