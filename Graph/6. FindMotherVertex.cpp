/* 1. Connected graph.
   2. If undirected graph, all nodes are mother vertex.
   3. If directed graph, find the vertex reach to reach all nodes
Nieve Approch 
run bfs or dfs and check all nodes reached or node.
O(V(V+E)) -> very complex for large graph

Kosa Raju Strongly connected algorithm
O(V+3) 

1f mother vertex exists in a graph. then last finished in DFS is one of those mother vertex.


Solution 2 time DFS
*/




#include <iostream>
#include <list>

#include <vector>

using namespace std;

class Graph {

    int V;
    bool is_directed;
    list<int> *edgeList;
    void dfsUtils(int node, vector<bool> &visited);
  public:
    Graph(int V, bool is_directed) {
        this->V = V;
        this->is_directed = is_directed;
        this->edgeList = new list<int>[V];
    }
    bool addEdge(int src, int dst);

    int GetMothorVertex();
};

bool Graph::addEdge(int src, int dst) {
    if ((src < 0 && src >= V) || (dst < 0 && dst >= V)) {
        return false;
    }

    edgeList[src].push_back(dst);

    if(!is_directed) {
        edgeList[dst].push_back(src);
    }

    return true;
}

// return vertex
int Graph::GetMothorVertex() {
    vector<bool> visited(V, false);
    int lastnode;

    for (int i=0; i<V; i++) {
        if (visited[i] == false) {
            dfsUtils(i, visited);
            lastnode = i;
        }
    }

    fill (visited.begin(), visited.end(), false);
    dfsUtils(lastnode, visited);

    for (int i=0; i<V; i++) {
        if (visited[i] == false) {
            return -1;
        }
    }

    return lastnode;
}

void 
Graph::dfsUtils(int node, vector<bool> &visited) {
    visited[node] = true;
    for (list<int>::iterator itr = edgeList[node].begin(); itr != edgeList[node].end(); ++itr) {
        if (visited[*itr] == false) {
            dfsUtils(*itr, visited);
        }
    }
}
