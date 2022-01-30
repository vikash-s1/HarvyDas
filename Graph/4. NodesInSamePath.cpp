/* Calculate intime or outtime
intime[parent] < intime[child] && outtime[parent] > outtime[child]

    U(intime, outtime)

    |
    v

    V (intime, outtime)
intime[u] < intime[v] && outtime[u] > outtime[v] 
*/

#include<iostream>
#include<list>

using namespace std;

int timer = 0;

class Graph {
    int V;
    bool is_directed;
    list<int> *adjList;

    void dfs(int node, bool visited[], int inTime[], int outTime[]);
public:
    Graph(int V, bool is_directed);
    bool addEdge(int src, int dst);
    bool IsNodesSamePath(int node1, int node2);
};

Graph::Graph(int V, bool is_directed) {
    this->V = V;
    this->is_directed = is_directed;
    this->adjList = new list<int>[V];
}

bool Graph::addEdge(int src, int dst) {
    if ((src < 0 && src >= V) || (dst < 0 && dst >= V)) {
        return false;
    }

    adjList[src].push_back(dst);

    if(!is_directed) {
        adjList[dst].push_back(src);
    }

    return true;
}

void Graph::dfs(int node, bool visited[], int inTime[], int outTime[]) {
    visited[node] = true;
    inTime[node] = ++timer;

    list<int>::iterator itr;
    for (itr = adjList[node].begin(); itr != adjList[node].end(); ++itr) {
        if (visited[*itr] == false) {
            dfs(*itr, visited, inTime, outTime);
        }
    }

    outTime[node] = ++timer;
}

bool Graph::IsNodesSamePath(int node1, int node2) {
    // taking intime and outtime
    int inTime[V];
    int outTime[V];
    bool visited[V];

    for(int i=0; i<V; i++) {
        visited[i] = false;
    }

    for (int i=0; i<V; i++) {
        if(visited[i] == false) {
            dfs(i, visited, inTime, outTime);
        }
    }

    if(inTime[node1] < inTime[node2] && outTime[node1] > outTime[node2]) {
        return true;
    }

    if (inTime[node2] < inTime[node1] && outTime[node2] > outTime[node1]) {
        return true;
    }

    return false;
}



int main() {
    int V = 9;
    Graph graph(V, 0);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(3, 6);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    graph.addEdge(5, 7);
    graph.addEdge(5, 8);
    graph.addEdge(5, 9);

    cout << graph.IsNodesSamePath(1, 5);
    cout << graph.IsNodesSamePath(2, 9);
    cout << graph.IsNodesSamePath(2, 6);  

    return 0;
}


