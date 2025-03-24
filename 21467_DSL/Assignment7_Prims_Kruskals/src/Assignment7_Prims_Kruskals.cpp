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

void Graph :: primsAlgo(int start)
{
	int edges[totalVertices];
	edges[0] = start;
	int edgePointer = 1;
	for(int temp = 1;temp<totalVertices;temp++)
	{
		edges[temp] = -1;
	}
	int current;
	int sum = 0;

	while(edges[totalVertices - 1] == -1)
	{
		for(int i=0;i<totalVertices;i++)
			{
				cout<<edges[i]<<"-->";
			}
		current = start;
		for(int i=0;i<totalVertices;i++)
		{
			int checker = 0;
			int min = INT_MAX;
			bool flag=false;
			while(edges[checker] != -1)
			{
				if(edges[checker] == i)
				{
					cout<<"Checker: "<<checker<<" ";
					cout<<"\nPresent in edges graph..Going to next vertex";
					flag = true;
					break;
				}
				checker++;
			}
			if(flag) //This vertex is present in edges
			{
				continue;
			}

			if(adjecencyMatrix[current][i] < min)
			{
				min = adjecencyMatrix[current][i];
				start = i;
			}
		}
		edges[edgePointer] = start;
		edgePointer++;
	}
	cout<<"\nPrims OP: \n";
	for(int i=0;i<totalVertices;i++)
	{
		cout<<edges[i]<<"-->";
	}
}

int main() {

	Graph obj(6);
	obj.createGraph();
	obj.displayMatrix();
	obj.primsAlgo(0);
	return 0;
}
