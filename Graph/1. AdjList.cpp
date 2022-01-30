#include <iostream>

using namespace std;

struct DestinationNode {
    int vertex;
    DestinationNode* next;
};

struct Edgelist {
    DestinationNode* head;
};

struct Graph {
    int V;
    Edgelist* array;
};

DestinationNode* CreateNode (int dest) {
    DestinationNode* node = new DestinationNode();
    node->vertex = dest;
    node->next = NULL;
    return node;
}

Graph* CreateGraph(int V) {
    Graph* graph = new Graph();

    graph->V = V;
    graph->array = new Edgelist[V];
    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addNode(Graph* graph, int src, int dest, int undirected_graph) {
    DestinationNode* node1 = CreateNode(dest);

    node1->next = graph->array[src].head;
    graph->array[src].head = node1;


    if (undirected_graph) {
        DestinationNode* node2 = CreateNode(src);
        node2->next = graph->array[dest].head;
        graph->array[dest].head = node2;
    }
}

void printGraph(Graph* graph) {
    int v;
    for (int i=0; i<graph->V;i++) {
        cout << i << " = ";
        DestinationNode* ptr = graph->array[i].head;
        while (ptr != NULL) {
            cout << ptr->vertex << " -> ";
            ptr = ptr->next;
        }
        cout << "\n";
    }
    cout << "\n";

}

int main() {
    int V = 5;
    int undirected_graph;

    cin >> undirected_graph;
    if (undirected_graph) {
        undirected_graph = 1;
    } else {
        undirected_graph = 0;
    }

    //Create Graph DS
    cout << "Creating Graph \n";
    Graph* graph = CreateGraph(V);

    cout << "Adding edge \n";
    addNode(graph, 0, 1, undirected_graph);
    cout << "Adding edge - 2\n";
    addNode(graph, 1, 2, undirected_graph);
    addNode(graph, 2, 3, undirected_graph);
    addNode(graph, 3, 4, undirected_graph);
    addNode(graph, 4, 0, undirected_graph);
    addNode(graph, 4, 1, undirected_graph);
    addNode(graph, 1, 3, undirected_graph);

    cout << "Printing Graph \n";
    printGraph(graph);
}
