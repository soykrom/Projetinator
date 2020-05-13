#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void makeGraph(vector<vector<int>> &vertexes, int size, int xMax, int yMax) {
    for(int i = 1; i <= size; i++) {
        if(i % 2 == 1) {
            vertexes[i].push_back(i + 1); //connect Vin to Vout
        } else {
            if(i > 2 * xMax) 
                vertexes[i].push_back(i - 1 - 2 * xMax);
            if(i % (2 * xMax) != 2)
                vertexes[i].push_back(i - 3);
            if(i % (2 * xMax) != 0)
                vertexes[i].push_back(i + 1);
            if(i <= 2 * xMax * (yMax - 1))
                vertexes[i].push_back(i - 1 + 2 * xMax);
        }
    }

    int nSp, nCt;
    cin >> nSp >> nCt;
    int x, y;
    for(int i = 0; i < nSp; i++) {
        cin >> x >> y;
        vertexes[2 * ((y - 1) * xMax + x)].push_back(size + 1);
    }

    for(int i = 0; i < nCt; i++) {
        cin >> x >> y;
        vertexes[0].push_back(2 * ((y - 1) * xMax + x - 1) + 1);
    }

}

void printGraph(vector<vector<int>> &vertexes, int V) { 
    int v;
    for (int u = 0; u < V; u++) { 
        cout << "Node " << u << " makes an edge with \n"; 
        for (v = 0; v < (int) vertexes[u].size(); v++)  {
            cout << "\tNode " << vertexes[u][v] << ".\n";
        } 
        cout << "\n"; 
    } 
} 

int main() {
    int xMax, yMax;
    cin >> xMax >> yMax;

    int V = xMax * yMax; //number of vertexes in graph
    vector<vector<int>> vertexes;
    vertexes.resize(V * 2 + 2);
    makeGraph(vertexes, V * 2, xMax, yMax);

    printGraph(vertexes, V * 2 + 2);

    return 0;
}