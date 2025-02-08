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

class BST
{
	Node *root = nullptr;
	Node *temp;
public:

	void createTree();
	void insertNode(Node *newNode, Node *r);
	void ascendingDisplay();
	void desendingDisplay();
	void recursiveAscending(Node *node);
	void recursiveDescending(Node *node);
	Node* helperFindLocation(string k);
	void deleteKey(string deleteKey);
	Node* rightMost(Node *t);
	void updateKey();
	void numOfComp();
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
		return;
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
	recursiveAscending(root);
}
void BST :: recursiveAscending(Node *node)
{
	if(node)
	{
		recursiveAscending(node->left);
		cout<<"  "<<node->key<<"-->"<<node->value<<"\n";
		recursiveAscending(node->right);
	}
}

void BST :: recursiveDescending(Node *node)
{
	if(node)
	{
		recursiveDescending(node->right);
		cout<<"  "<<node->key<<"-->"<<node->value<<"\n";
		recursiveDescending(node->left);
	}
}
void BST :: desendingDisplay()
{
	recursiveDescending(root);
}

void BST :: updateKey()
{
	string toUpdate,newKey;
	cout<<"\nEnter key to be updated: ";
	cin>>toUpdate;
	cout<<"\nEnter new key: ";
	cin>>newKey;

	Node *temp = root;
	while(temp)
	{
		//First need to find location of old key
		int cmp = temp->key.compare(toUpdate);

		if(cmp == 0) // key found
		{
			Node *newNode = new Node(newKey,temp->value);
			insertNode(newNode,root);
			//Note still deletion remaining
			return;
		}
		else if(cmp<0) //newKey is large
		{
			temp = temp->right;
		}
		else
		{
			temp = temp->left;
		}
	}
	cout<<"\nKey does not exist to update!!";
}

Node* BST ::helperFindLocation(string k)  //This function finds location of previos node of k key
{
	Node *temp = root;
	Node *prev = temp;
	while(temp)
	{
		int cmp = temp->key.compare(k);

		if(cmp == 0) // key found
		{
			return prev; //Direct address of node will be sent as its Node* i.e value at pointer
		}
		else if(cmp<0) //newKey is large
		{
			prev = temp;
			temp = temp->right;
		}
		else
		{
			prev = temp;
			temp = temp->left;
		}
	}
	return nullptr;
}

void BST :: deleteKey(string deleteKey)
{
	if(root == nullptr)
	{
		cout<<"\nTree is empty, no deletion possible";
	}
	else
	{
		Node *locationDelete = helperFindLocation(deleteKey);
		if(locationDelete == nullptr)
		{
			cout<<"\nKey does not exists in tree to delete";
		}
		else{
			if(locationDelete->left == nullptr)
			{
				
			}
		}

	}
}

Node* BST :: rightMost(Node* t)
{
	while(t->right != nullptr)
	{
		t = t->right;
	}
	return t;
}

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	BST obj;
	int choice;
	do
	{
		cout<<"\n1.Insert Data\n2.Ascending Display\n3.Descending Display\n4.No. of Max Cmp\n5.Delete Key\n6.Update Key\n7.Exit\n";
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
		case 3:
			obj.desendingDisplay();
			break;
		case 5:
			obj.deleteKey("a");
			break;
		case 6:
			obj.updateKey();
			break;
		case 7:
			cout<<"\nBye";
			break;
		default:
			cout<<"\nInvalid choice code\n";

		}
	}while(choice!=7);
	return 0;
}
