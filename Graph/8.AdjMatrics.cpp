#include <iostream>

using namespace std;

#define N 5;

int createGraph( int Nodes, int edges, int arr[][2], int **Adj) {

}


int main() {
    int arr[][2]
        = { { 1, 2 }, { 2, 3 }, 
            { 4, 5 }, { 1, 5 } };

    // Number of Edges
    int Edges = sizeof(arr) / sizeof(arr[0]);


    int AdjMatrix[N+1][N+1];
    createGraph(arr, AdjMatrix);

    
    int V
}
