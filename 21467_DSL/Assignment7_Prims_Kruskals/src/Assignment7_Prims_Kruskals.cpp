//============================================================================
// Name        : Assignment7_Prims_Kruskals.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <limits.h> //For int max
using namespace std;
const int MAX_SIZE = 20;
class Graph
{
	int adjecencyMatrix[MAX_SIZE][MAX_SIZE];
	int totalVertices;

public:

	Graph(int tV)
	{
		totalVertices = tV;
		adjecencyMatrix[totalVertices][totalVertices];

		for(int i=0;i<totalVertices;i++)
		{
			for(int j=0;j<totalVertices;j++)
			{
				adjecencyMatrix[i][j] = INT_MAX;  //The value of int max is 21467...
			}
		}
	}

	void createGraph();
	void displayMatrix();
	void primsAlgo(int start);
};

void Graph :: createGraph()
{
	int source,destination,weight;
	while(true)
	{
		cout<<"\nTo exit set everything as -1...";
		cout<<"\nFor total vertices "<<totalVertices<<" graph enter edges and its weights:\n\n";
		cout<<"\nEnter source,destination, weight:  ";
		cin>>source>>destination>>weight;

		if(weight == -1)
		{
			break;
		}
		adjecencyMatrix[source][destination] = weight;
	}
}
void Graph::displayMatrix()
{
	for(int i=0;i<totalVertices;i++)
	{
		for(int j=0;j<totalVertices;j++)
		{
			cout<<adjecencyMatrix[i][j]<<" ";
		}
		cout<<"\n";
	}
}

void Graph::primsAlgo(int start) {
    int key[MAX_SIZE];
    int parent[MAX_SIZE];
    bool mstSet[MAX_SIZE];

    for (int i = 0; i < totalVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
        parent[i] = -1;
    }

    key[start] = 0;

    for (int count = 0; count < totalVertices - 1; count++) {
        int min = INT_MAX, u = -1;

        // Pick the minimum key vertex not yet included in MST
        for (int v = 0; v < totalVertices; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

        // Update key and parent for adjacent vertices
        for (int v = 0; v < totalVertices; v++) {
            if (adjecencyMatrix[u][v] != INT_MAX && !mstSet[v] && adjecencyMatrix[u][v] < key[v]) {
                key[v] = adjecencyMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    // Print MST
    cout << "\nMinimum Spanning Tree using Prim's Algorithm:\n";
    cout << "Edge\tWeight\n";
    int totalWeight = 0;
    for (int i = 0; i < totalVertices; i++) {
        if (parent[i] != -1) {
            cout << parent[i] << " - " << i << "\t" << adjecencyMatrix[i][parent[i]] << "\n";
            totalWeight += adjecencyMatrix[i][parent[i]];
        }
    }
    cout << "Total Weight of MST: " << totalWeight << endl;
}

int main() {
    int vertices;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph obj(vertices);
    obj.createGraph();
    obj.displayMatrix();

    int choice;
    cout << "\nChoose MST Algorithm:\n1. Prim's Algorithm\n2. Kruskal's Algorithm\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        obj.primsAlgo(0); // start from vertex 0
    } else if (choice == 2) {
        // obj.kruskalsAlgo();
    } else {
        cout << "Invalid choice!\n";
    }

    return 0;
}

