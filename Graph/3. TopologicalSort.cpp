/* Topological sort
  1. It is a directed graph with no cycles.
  2. Cycles in Graph means for every visit of vertex v, if it visit adjacent u which is already visited#pragma region
  and u is not parent of v.
  3. For a directed graph, where LINEAR ORDRERING of vertices are consistant. 
  such that every directed edge (u, v), vertix u is always comes after v.


    A
B       C
    D
    E

A B C D E
A C B D E

APPLICATIONS
    Build Systems
    Advanced-Packaging tool (apt-get)
    Task Scheduling
    Pre-requiste problem (one job than other)

Underlne Data structure
DFS + Stack

*/


#include <iostream>
#include <list>
#include <queue>

#include <stack>

using namespace std;

class Graph {
    int V;
    list<int>  *adjlist;
    bool undirected_graph;

    void BFSUtils(int node, bool visited[]);
    void DFSUtils(int node, bool visited[]);
    void topologicalSortUtils(int node, bool visited[], stack<int> &Stack);
public:
    Graph(int V, bool type) {
        this->V = V;
        adjlist = new list<int>[V];
        undirected_graph = type;
    }

    bool addEdge(int src, int dst);
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

    void topologicalsort();
};

bool Graph::addEdge(int src, int dst) {

    if ((src < 0 || src >= V) || (dst < 0 || dst >= V)) {
        cout << "invalid edges \n";
        return 1;
    }

    adjlist[src].push_back(dst);
    if(undirected_graph) {
        adjlist[dst].push_back(src);
    }
    return 0;
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

void
Graph::topologicalSortUtils(int node, bool visited[], stack<int> &Stack) {
    visited[node] = true;

    list<int>::iterator itr;
    for(itr = adjlist[node].begin(); itr != adjlist[node].end(); itr++) {
        if (visited[*itr] == false)
            topologicalSortUtils(*itr, visited, Stack);
    }

    Stack.push(node);
}

void
Graph::topologicalsort() {
    bool visited[V];
    stack<int> Stack;

    for (int i = 0; i < V; i++){
        visited[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (visited[i] == false) {
            topologicalSortUtils(i, visited, Stack);
        }
    }

    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
    }

    cout << endl;
}

int main() {
    Graph g(6, 0);

    if (g.addEdge(5, 2)) {
        exit (1);
    }
    if (g.addEdge(5, 0)) {
        exit (1);
    }
    if (g.addEdge(4, 0)) {
        exit (1);
    }
    if (g.addEdge(4, 1)) {
        exit (1);
    }
    if (g.addEdge(2, 3)) {
        exit (1);
    }
    if (g.addEdge(3, 1)) {
        exit (1);
    }

    //g.printGraph();
    //graph.print_bfs();
    //graph.print_dfs();

    g.topologicalsort();


    return 0;
}
