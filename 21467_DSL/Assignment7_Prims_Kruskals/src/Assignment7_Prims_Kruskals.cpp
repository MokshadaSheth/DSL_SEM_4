//============================================================================
// Name        : Assignment7_Prims_Kruskals.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
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

        for (int i = 0; i < totalVertices; i++)
        {
            for (int j = 0; j < totalVertices; j++)
            {
                adjecencyMatrix[i][j] = INT_MAX;
            }
        }
    }

    void createGraph();
    void displayMatrix();
    void primsAlgo(int start);
    void kruskalsAlgo();

private:
    int find(int parent[], int i);
    void unionSets(int parent[], int x, int y);
};

void Graph::createGraph()
{
    int source, destination, weight;
    while (true)
    {
        cout << "\nTo exit set everything as -1...";
        cout << "\nEnter source, destination, weight: ";
        cin >> source >> destination >> weight;

        if (source == -1 || destination == -1 || weight == -1)
            break;

        adjecencyMatrix[source][destination] = weight;
        adjecencyMatrix[destination][source] = weight; // Since undirected graph
    }
}

void Graph::displayMatrix()
{
    cout << "\nAdjacency Matrix:\n";
    for (int i = 0; i < totalVertices; i++)
    {
        for (int j = 0; j < totalVertices; j++)
        {
            if (adjecencyMatrix[i][j] == INT_MAX)
                cout << "INF ";
            else
                cout << adjecencyMatrix[i][j] << " ";
        }
        cout << "\n";
    }
}

// Prim's Algorithm
void Graph::primsAlgo(int start)
{
    int key[MAX_SIZE], parent[MAX_SIZE];
    bool mstSet[MAX_SIZE];

    for (int i = 0; i < totalVertices; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = false;
        parent[i] = -1;
    }

    key[start] = 0;

    for (int count = 0; count < totalVertices - 1; count++)
    {
        int min = INT_MAX, u = -1;

        for (int v = 0; v < totalVertices; v++)
        {
            if (!mstSet[v] && key[v] < min)
            {
                min = key[v];
                u = v;
            }
        }

        mstSet[u] = true;

        for (int v = 0; v < totalVertices; v++)
        {
            if (adjecencyMatrix[u][v] != INT_MAX && !mstSet[v] && adjecencyMatrix[u][v] < key[v])
            {
                key[v] = adjecencyMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "\nMinimum Spanning Tree using Prim's Algorithm:\n";
    cout << "Edge\tWeight\n";
    int totalWeight = 0;
    for (int i = 0; i < totalVertices; i++)
    {
        if (parent[i] != -1)
        {
            cout << parent[i] << " - " << i << "\t" << adjecencyMatrix[i][parent[i]] << "\n";
            totalWeight += adjecencyMatrix[i][parent[i]];
        }
    }
    cout << "Total Weight of MST: " << totalWeight << endl;
}

// Kruskal's Algorithm
int Graph::find(int parent[], int i)
{
    while (parent[i] >= 0)
        i = parent[i];
    return i;
}

void Graph::unionSets(int parent[], int x, int y)
{
    parent[y] = x;
}

void Graph::kruskalsAlgo()
{
    struct Edge
    {
        int src, dest, weight;
    };

    vector<Edge> edges;

    // Create edge list from adjacency matrix
    for (int i = 0; i < totalVertices; i++)
    {
        for (int j = i + 1; j < totalVertices; j++)
        {
            if (adjecencyMatrix[i][j] != INT_MAX)
            {
                edges.push_back({i, j, adjecencyMatrix[i][j]});
            }
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
         { return a.weight < b.weight; });

    int parent[MAX_SIZE];
    for (int i = 0; i < totalVertices; i++)
        parent[i] = -1;

    cout << "\nMinimum Spanning Tree using Kruskal's Algorithm:\n";
    cout << "Edge\tWeight\n";

    int totalWeight = 0, count = 0;

    for (auto e : edges)
    {
        int root1 = find(parent, e.src);
        int root2 = find(parent, e.dest);

        if (root1 != root2)
        {
            cout << e.src << " - " << e.dest << "\t" << e.weight << "\n";
            totalWeight += e.weight;
            unionSets(parent, root1, root2);
            count++;
            if (count == totalVertices - 1)
                break;
        }
    }

    cout << "Total Weight of MST: " << totalWeight << endl;
}

// Main
int main()
{
    int vertices;
    cout << "Enter number of vertices: ";
    cin >> vertices;

    Graph obj(vertices);
    obj.createGraph();
    obj.displayMatrix();

    int choice;
    while (true)
    {
        cout << "\nChoose MST Algorithm:\n1. Prim's Algorithm\n2. Kruskal's Algorithm\n3. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            obj.primsAlgo(0); // start from vertex 0
        }
        else if (choice == 2)
        {
            obj.kruskalsAlgo();
        }
        else if (choice == 3)
        {
            cout << "\nByee";
            break;
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}