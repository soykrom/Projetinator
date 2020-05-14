#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> prevVertex;

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


int bfs(vector<vector<int>> &vertexVec, int maxV) {
  prevVertex.clear();               //resets vector containig the previous vertexes;
  for(int i = 0; i < maxV; i++){
    prevVertex.push_back(-1);
  }

  prevVertex.at(0) = -2;

  queue<int> queue;
  queue.push(0);                  //pushes the source;

  while(!queue.empty()) {             //stops execution when the q is empty or finds the sink;
    int currentNode = queue.front();
    queue.pop();

    for(unsigned int i = 0; i < vertexVec.at(currentNode).size(); i++){ //for every adjacent vertex;
      int dest = vertexVec.at(currentNode).at(i);
      if(prevVertex[dest] == -1){                                        //if doesn't have previous, adds to queue;
        prevVertex[dest] = currentNode;
        if(dest == (maxV - 1)){                                          //if the adjacent vertex is the sink, returns 1;
          return 1;
        }
        queue.push(dest);
      }
    }
  }
  return 0;
}

int edmondsKarp(vector<vector<int>> &vertexVec, int maxV){
  int maxFlow = 0;

  while(true){
    int flow = bfs(vertexVec, maxV);
    if(flow == 0) {
      break;
    }
    maxFlow += flow;
    int currentNode = maxV - 1;

    while(currentNode != 0){
      int previousNode = prevVertex[currentNode];
        for(unsigned int i = 0; i < vertexVec.at(previousNode).size(); i++) {
          if(vertexVec.at(previousNode).at(i) == currentNode) {
            vertexVec[previousNode].erase(vertexVec[previousNode].begin() + i);
            vertexVec[currentNode].push_back(previousNode);
            break;
          }
        }
      currentNode = previousNode;
    }
  }
  return maxFlow;
}

int main() {
    int xMax, yMax;
    cin >> xMax >> yMax;

    int V = xMax * yMax; //number of vertexes in graph
    int MAX = V*2 + 2;
    vector<vector<int>> vertexes;
    vertexes.resize(MAX);
    makeGraph(vertexes, V * 2, xMax, yMax);

    int maxFlow = edmondsKarp(vertexes, MAX);

    cout << maxFlow << endl;

    return 0;
}