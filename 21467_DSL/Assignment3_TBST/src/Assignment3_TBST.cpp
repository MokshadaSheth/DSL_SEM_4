//============================================================================
// Name        : Assignment3_TBST.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Create an inordered threaded binary search tree. Perform inorder, preorder
// traversals without recursion and deletion of a node. Analyze time
// and space complexity of the algorithm
//============================================================================

#include <iostream>
using namespace std;

class Node
{
	Node *lthread;
	bool isLchild;
	int data;
	bool isRchild;
	Node *rthread;

public:
	Node()
	{
		lthread = nullptr;
		isLchild = false;
		isRchild = false;
		data = -1;
		rthread = nullptr;
	}
	Node(int d)
	{
		lthread = nullptr;
		isLchild = false;
		isRchild = false;
		data = d;
		rthread = nullptr;
	}
	friend class TBST;
};

class TBST
{
	Node *head = new Node();

public:
	Node *root = nullptr;
	void createTree(int d);
	void insertNode(Node *newnode, Node *currentParent);
	void inorder(Node *node);
	void preorder();
};

void TBST ::createTree(int d)
{
	Node *newNode = new Node(d);
	if (head->lthread == nullptr) // Tree is empty
	{
		root = newNode;
		head->lthread = root;
		head->rthread = head; // Point to self
		root->lthread = head;
		root->rthread = head;
		head->isLchild = true;
	}
	else
	{
		insertNode(newNode, root);
	}
}

void TBST ::insertNode(Node *newNode, Node *currentParent)
{
	if (currentParent->data > newNode->data)
	{
		if (currentParent->isLchild == false)
		{
			newNode->lthread = currentParent->lthread;
			newNode->rthread = currentParent;
			currentParent->lthread = newNode;
			currentParent->isLchild = true;
			return;
		}
		else
		{
			currentParent = currentParent->lthread;
			insertNode(newNode, currentParent);
		}
	}
	else
	{
		if (currentParent->isRchild == false)
		{
			newNode->rthread = currentParent->rthread;
			newNode->lthread = currentParent;
			currentParent->rthread = newNode;
			currentParent->isRchild = true;
			return;
		}
		else
		{
			currentParent = currentParent->rthread;
			insertNode(newNode, currentParent);
		}
	}
}

void TBST ::inorder(Node *node)
{
	if (node)
	{
		if (node->isLchild == true)
			inorder(node->lthread);
		cout << "  " << node->data;
		if (node->isRchild == true)
			inorder(node->rthread);
	}
}
void TBST::preorder()
{
	if(root == nullptr) return;
	Node *temp = root;
	// since circular last node connected back to head
	while (temp != head)
	{
		// cout<<"\nTemp: "<<temp<<"\nhead: "<<head<<"\nRoot: "<<root;
		cout <<temp->data << "  ";
		if (temp->isLchild)
		{
			temp = temp->lthread;
		}
		else
		{
			if (temp->isRchild)
			{
				temp = temp->rthread;
			}
			else
			{
				if(temp->rthread == head) return;  //Note this breaks the loop
				while (temp->isRchild != true)
				{
					temp = temp->rthread;
				}
				temp = temp->rthread;
			}
			// find the inorder successor last node connected to parent
		}
	}
	//	cout<<"root->data"<<root->data<<"\nroot->lthread "<<root->lthread->data<<"\nroot->lthread->rthread "<<root->lthread->rthread->data;
	//	cout<<"\nroot->rthread->data "<<root->rthread->data<<"r thread ka succ: "<<root->rthread->rthread->data;
}

int main()
{
	int choice;
	TBST obj;
	do
	{
		cout << "\n1.Insert Data\n2.Inorder Display\n3.Preorder Display\n4.Delete Node\n5.Exit";
		cout << "\nEnter choice code: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cout << "\nEnter data: ";
			int d;
			cin >> d;
			obj.createTree(d);
			break;
		case 2:
			obj.inorder(obj.root);
			break;
		case 3:
			obj.preorder();
			break;
		case 5:
			cout << "\n\nbyee";
			break;

		default:
			cout << "\nInvalid choice code";
		}
	} while (choice != 5);

	return 0;
}
