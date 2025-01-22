//============================================================================
// Name        : Assignment2_Dictionary.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
// Problem Statement:A dictionary stores keywords and its meanings. Provide facility for add-
//ing new keywords, deleting keywords, updating values of any entry.
//Provide facility to display whole data sorted in ascending/ Descending
//order. Also find how many maximum comparisons may require for find-
//ing any keyword. Use Binary Search Tree for implementation.
//============================================================================

#include <iostream>
#include<string>
#include<cstring>
using namespace std;


class Node
{
	Node *right;
	string key;
	string value;
	Node *left;

public:
	Node()
	{
		right = nullptr;
		left = nullptr;
		key = "0";
		value = "0";
	}
	Node(string k, string v)
	{
		right = nullptr;
		left = nullptr;
		key = k;
		value = v;
	}
	friend class BST;
};

class Stack
{
	Node *st;
	int top;
public:
	//Note add stack full and empty condition
	Stack()
	{
		st = new Node[20];
		top = -1;
	}

	void push(Node *data)
	{
		top++;
		st[top] = *data;
	}
	Node* pop()
	{
		return &st[top--];
	}
	friend class BST;
};


class BST
{
	Node *root;
	Node *temp;
public:

	void createTree();
	void insertNode(Node *newNode, Node *r);
	void ascendingDisplay();
};

void BST :: createTree()
{
	string k,v;
	cout<<"\nEnter key: ";
	cin>>k;
	cout<<"\nEnter value: ";
	cin>>v;
	Node *newNode = new Node(k,v);
	if(root == nullptr)
	{
		root = newNode;
	}
	else
	{
		insertNode(newNode,root);
	}

}
void BST :: insertNode(Node *newNode, Node *r)
{
	temp = r;

	cout<<"\nTemp val: "<<temp->value<<endl;

	int compVal = temp->key.compare(newNode->key);
	cout<<"Comparison: "<<compVal<<endl;

	if(compVal == 0)
	{
		cout<<"\nKey already exists...\n";
		return;
	}
	else if(compVal < 0) //Right child
	{
		if(temp->right != nullptr) //It has child
		{
			insertNode(newNode,temp->right); //Recursion
		}
		else
		{
			temp->right = newNode;
			cout<<"\nInserted in right side\n";
			return;
		}
	}
	else
	{
		if(temp->left != nullptr) //It has left child
		{
			insertNode(newNode, temp->left);
		}
		else
		{
			temp->left = newNode;
			cout<<"\nInserted In Left Side\n";
			return;
		}
	}

}

void BST :: ascendingDisplay()
{
		Stack obj;
		Node *temp = root;

		while(true)
		{
			while(temp != nullptr)
			{
				obj.push(temp);
				temp = temp -> left;
			}
			if(obj.top == -1)
			{
				cout<<"\nInorder Traversal Completed\n";
				break;
			}
			else
			{
				temp = obj.pop(); // IMP first pop
				cout<<temp->key<<"-->"<<temp->value<<endl;

				temp = temp->right;
			}
		}
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	BST obj;
	int choice;
	do
	{
		cout<<"\n1.Insert Data\n2.Ascending Display\n3.Decending Display\n4.No. of Max Cmp\n5.Exit\n";
		cout<<"\n\nEnter choice code: ";
		cin>>choice;

		switch(choice)
		{
		case 1:
			obj.createTree();
			break;

		case 2:
			obj.ascendingDisplay();
			break;
		case 5:
			cout<<"\nBye";
			break;
		default:
			cout<<"\nInvalid choice code\n";

		}
	}while(choice!=5);
	return 0;
}
