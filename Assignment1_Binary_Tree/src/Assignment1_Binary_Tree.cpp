//============================================================================
// Name        : Assignment1_Binary_Tree.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Node
{
	Node *prev; //Parent
	Node *left,*right;
	int data;

public:
	Node()
	{
		prev = nullptr;
		left = nullptr;
		right = nullptr;
		data = 0;
	}
	Node(int d): prev(nullptr),left(nullptr),right(nullptr),data(d){}

	friend class BinaryTree;
};
class BinaryTree
{
	Node *root=nullptr;
	Node *current;
	Node *allNodes[15];
	int i=0;

public:
	void createTree(int data);
	void display();
};
void BinaryTree :: createTree(int data)
{
	if(root == nullptr)
	{
		root = new Node(data);
		allNodes[i] = root;
		current = allNodes[i];
		i++;
	}
	else
	{
		Node *newNode = new Node(data);
		current = root;
		while(true)
		{
			char choice;
			cout<<"\nYou want to insert data to left or right(l/r) of node "<<current->data<<": ";
			cin>>choice;
			switch(choice)
			{
			case 'l':
				if(current->left == nullptr)
				{
					cout<<"\nInserting after "<<current->data;
					current->left = newNode;
					return;

				}
				current = current->left;
				cout<<"\nLeft is not null...\n";

				break;
			case 'r':

				break;
			default:
				cout<<"\nInvalid choice";
				createTree(data);
			}
		}

	}
}
int main() {

}
