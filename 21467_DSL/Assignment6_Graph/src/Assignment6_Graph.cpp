//============================================================================
// Name        : Assignment6_Graph.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :Represent a given graph using adjacency list to perform DFS and BFS.
//Use the map of the area around the college as the graph. Identify the
//prominent land marks as nodes and perform DFS and BFS on that.
//============================================================================

#include <iostream>
using namespace std;
const int MAXSIZE = 20;
class Node
{
	int data;
	Node *next;
public:
	friend class Graph;
	Node(int x)
	{
		data = x;
		next = nullptr;
	}
};

class Graph
{
	Node *H[MAXSIZE];
	int tVertices;

public:
	Graph(int n){
		for(int i=0;i<n;i++)
		{
			H[i] = new Node(i);
		}
	}

	void createGraph(int totalVertices);
	void BFS();
	void DFS();
};

void Graph:: createGraph(int totalVertices)
{
	tVertices = totalVertices;
	if(totalVertices > MAXSIZE)
	{
		cout<<"\nToo much vertices\n";
	}
	for(int i=0;i<totalVertices;i++)
	{
		int s,d;
		cout<<"\nSource: ";
		cin>>s;
		cout<<"\nDestination: ";
		cin>>d;

		//Add new node from source to destination
		Node *temp = H[s];
		Node *destinationNode = new Node(d);
		while(temp->next != nullptr)
			temp = temp->next;
		temp->next = destinationNode;

		//Add new node from destination to source
		Node *t = H[d];
		Node *sourceNode = new Node(s);
		while(t->next != nullptr)
			t = t->next;
		t->next = sourceNode;
	}
	return;
}

void Graph::BFS()
{
	Node *temp;
	int Q[20],f=0,r=-1;
	int visited[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int v1 = H[0]->data;
	Q[++r] = v1;
	visited[v1] = 1;

	while(f<=r)
	{
		int x = Q[f++];
		cout<<" "<<x;
		temp = H[x];
		while(temp!=nullptr)
		{
			if(visited[temp->data] == 0)
			{
				Q[++r] = temp->data;
				visited[temp->data] = 1;
			}
			temp = temp->next;
		}
	}
	cout<<endl;
}

void Graph :: DFS()
{
	int st[20],top=-1;
	int visited[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	Node *temp;

	int v1 = H[0]->data;
	st[++top] = v1;
	visited[v1] = 1;

	while(top!=-1)
	{
		int x = st[top--];
		temp = H[x];
		cout<<" "<<temp->data;

		while(temp!=nullptr)
		{
			if(visited[temp->data] == 0)
			{
				st[++top] = temp->data;
				visited[temp->data] = 1;
			}
			temp = temp->next;
		}
	}
	cout<<endl;
}

int main() {
	int choice,vertices,edges;
	Graph *obj = nullptr;
	do
	{
		cout<<"\n1.Set Vertices\n2.Create Graph\n3.BFS\n4.DFS\n5.Exit\n\nEnter Choice Code: ";
		cin>>choice;

		switch (choice)
		{
		case 1:
			cout<<"\nEnter total vertices: ";
			cin>>vertices;
			obj = new Graph(vertices);
			break;
		case 2:
			cout<<"\nEnter total no. of edges: ";
			cin>>edges;
			(*obj).createGraph(edges);
			break;
		case 3:
			(*obj).BFS();
			break;
		case 4:
			(*obj).DFS();
			break;
		case 5:
			cout<<"\nBye";
			break;
		default:
		cout<<"\nInvalid choice!!";
			break;
		}

	} while (choice != 5);
	
	return 0;
}

