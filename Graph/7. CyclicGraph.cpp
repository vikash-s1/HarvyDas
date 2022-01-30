// Directed Graph 
//    recursion array + visited array

//Undirected Graph
/*      DFS Method - parent variable + visited array
      Find and Union */

#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
    int V;
    bool is_directed;
    list<int> *edgeArray;

    bool isCycleDirectedUtils(int node, vector<bool> visited, vector<bool> recArray);
    bool isCycleUndirectedUtils(int node, vector<bool> visited, int parent);
    bool isCycleDirected();
    bool isCycleUndirected();
  public:
    Graph (int V, bool is_directed) {
        this->V = V;
        this->is_directed = is_directed;
        this->edgeArray = new list<int>[10];
    }

    bool addEdge(int src, int dst) {
        if ((src < 0 && src >= V) || (dst < 0 && dst >= V)) {
            return false;
        }

        edgeArray[src].push_back(dst);

        if(!is_directed) {
            edgeArray[dst].push_back(src);
        }

        return true;
    }


    bool isCycle();
};

bool
Graph::isCycle() {
    if (is_directed) {
        return isCycleDirected();
    } else {
        return isCycleUndirected();
    }
}


bool
Graph::isCycleDirected() {
    vector<bool> visited(V, false);
    vector<bool> recursionArray(V, false);

    for (int i=0; i<V; i++) {
        if (isCycleDirectedUtils(i, visited, recursionArray) == true) {
            return true;
        }
    }

    return false;
}


bool Graph::isCycleDirectedUtils(int node, vector<bool> visited, vector<bool> recArray) {

    if (visited[node] == false) {
        visited[node] = true;
        recArray[node] = true;

        for (list<int>::iterator itr = edgeArray[node].begin(); itr != edgeArray[node].end(); ++itr) {
            if ((visited[*itr] == false) && isCycleDirectedUtils(*itr, visited, recArray)) {
                return true;
            } else if (recArray[*itr] == true) {
                return true;
            }
        }
    }
    recArray[node] = false;
    return false;
}

bool
Graph::isCycleUndirected() {
    cout << "isCycleUndirected" << endl;
    int parent = -1;
    vector<bool> visited(V, false);

    for (int i=0; i<V; i++) {
        if(visited[i] == false && isCycleUndirectedUtils(i, visited, parent)) {
            return true;
        }
    }

    return false;

}

bool Graph::isCycleUndirectedUtils(int node, vector<bool> visited, int parent) {
    visited[node] = true;

    list<int>::iterator itr;
    for (itr = edgeArray[node].begin(); itr != edgeArray[node].end(); itr++) {
        if (visited[*itr] == false) {
            return isCycleUndirectedUtils(*itr, visited, node);
        } else if (*itr != parent) {
            return true;
        }
    }

    return false;
}

int main () {
    Graph g(4, 0);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(0, 0);

    cout << "Checking cycles" << endl;
    cout << g.isCycle() << endl;

    return 0;
}
