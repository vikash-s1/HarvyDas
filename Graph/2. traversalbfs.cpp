#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph {
    int V;
    list<int>  *adjlist;
    bool undirected_graph;

    void BFSUtils(int starting_node, bool visited[]);
    void DFSUtils(int starting_node, bool visited[]);
public:
    Graph(int V, bool type) {
        this->V = V;
        adjlist = new list<int>[V];
        undirected_graph = type;
    }

    void addEdge(int src, int dst);
    void print_bfs();
    void print_dfs();

    void printGraph() {
        int v;
        for (int i=0; i<V;i++) {
            cout << i << " = ";
            list<int>::iterator itr = adjlist[i].begin();

            while (itr != adjlist[i].end()) {
                cout << *itr << " -> ";
                itr++;
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

void Graph::addEdge(int src, int dst) {
    adjlist[src].push_back(dst);
    if(undirected_graph) {
        adjlist[dst].push_back(src);
    }
}

void Graph::BFSUtils(int node, bool visited[]) {
    queue<int> myqueue;
    visited[node] = true;
    myqueue.push(node);

    while(!myqueue.empty()) {
        int currNode = myqueue.front();
        myqueue.pop();

        cout << currNode << " ";

        list<int>::iterator itr; 
        for (itr = adjlist[currNode].begin(); itr != adjlist[currNode].end(); itr++) {
            if (visited[*itr] == false) {
                myqueue.push(*itr);
                visited[*itr] = true;
            }
        }

    }
    cout << endl;
}

void Graph::DFSUtils(int node, bool visited[]) {
    visited[node] = true;

    cout << node << " ";
    for (list<int>::iterator itr = adjlist[node].begin(); itr != adjlist[node].end(); itr++) {
        if (visited[*itr] == false) {
            DFSUtils(*itr, visited);
        }
    }
}

void Graph::print_bfs() {
    bool visited[V];
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }

    for (int i=0; i<V; i++) {
        if (visited[i] == false)
            BFSUtils(i, visited);
    }
    cout << endl;

}


void Graph::print_dfs() {
    bool visited[V];
    for (int i=0; i<V; i++) {
        visited[i] = false;
    }

    for (int i=0; i<V; i++) {
        if (visited[i] == false) 
            DFSUtils(i, visited);
    }
    cout << endl;
}

int main() {
    Graph graph(5, 1);

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(0, 4);
    graph.addEdge(1, 4);
    graph.addEdge(1, 3);

    graph.printGraph();
    graph.print_bfs();
    graph.print_dfs();

    return 0;
}
