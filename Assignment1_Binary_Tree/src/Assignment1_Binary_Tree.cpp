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
	friend class Queue;
	friend class Stack;
};

class Queue
{
	Node *visitedNodes;
	int front,rear;

public:
	Queue()
	{
		visitedNodes = new Node[20];
		front = -1;
		rear = -1;
	}

	void enqueue(Node *d)
	{
		if(front == -1)
		{
			front = rear = 0;
		}
		else
		{
			rear++;
		}
		visitedNodes[rear] = *d;
	}
	Node dequeue()
	{
		Node toReturn = visitedNodes[front];
//		delete visitedNodes[front];
		if(front ==rear)
		{
			front = rear = -1;
		}
		else
		{
			front++;
		}
		return toReturn;
	}
	friend class BinaryTree;

};

class Stack
{
	Node *st;
	int top;
public:
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
	friend class BinaryTree;
};

class BinaryTree
{
	Node *root=nullptr;
	Node *current;
	Node *allNodes[15];
	int i=0;

	static int totalNodes;

public:
	void createTree(int data);
	void display();
	void preorder();
	void inorder();
};
int BinaryTree :: totalNodes = 0;

void BinaryTree :: preorder()
{
	Stack obj;
	Node *temp = root;
	while(true)
	{
		while(temp!=nullptr)
		{
					cout<<temp->data<<" ";
					if(temp->right != nullptr)
					{
						obj.push(temp->right);

					}

					temp = temp->left;

		}
		if(obj.top == -1)
		{
			cout<<"\nPreorder Traversal Completed\n";
			return;
		}
		else
		{
			temp = obj.pop();
		}

	}

}

void BinaryTree :: inorder()
{
	cout<<"\nInside func";
	Stack obj;
	Node *temp = root;

	while(true)
	{
		cout<<"\nInside Infiy";
		while(temp != nullptr)
		{
			obj.push(temp);
			temp = temp -> left;
		}
		if(obj.top == -1)
		{
			break;
		}
		else
		{
			cout<<temp->data<<" ";
			temp = obj.pop();
			temp = temp->right;
		}
	}
}

void BinaryTree :: createTree(int data)
{
	if(root == nullptr)
	{
		root = new Node(data);
		allNodes[i] = root;
		current = allNodes[i];
		i++;
		totalNodes++;
	}
	else
	{
		Node *newNode = new Node(data);
		current = root;
		cout<<"Data of root"<<root->data;
		while(true)
		{
			char choice;
			cout<<"\nYou want to insert data to left or right(l/r) of node: "<<current->data<<": ";
			cin>>choice;
			switch(choice)
			{
			case 'l':
				if(current->left == nullptr)
				{
					cout<<"\nInserting after:  "<<current->data;
					current->left = newNode;
					totalNodes++;
					return;

				}
				current = current->left;
				cout<<"\nLeft is not null...\n";

				break;
			case 'r':
				if(current->right == nullptr)
				{
					cout<<"\nInserting after: "<<current->data;
					current->right = newNode;
					totalNodes++;
					return;
				}
				current = current->right;
				cout<<"\nRight is not null..\n";
				break;
			default:
				cout<<"\nInvalid choice";
				createTree(data);
			}
		}

	}
}
void BinaryTree :: display()
{
	Node *temp = new Node;
	temp = root;
	Queue obj;
	int *valuesInTree = new int[totalNodes];
	int i=0;
	obj.enqueue(temp);
	while(obj.front != -1)
	{
		*temp = obj.visitedNodes[obj.front];

		valuesInTree[i] = temp->data;
		i++;

		if(temp->left != nullptr)
		{
			obj.enqueue(temp->left);
		}
		if(temp->right != nullptr)
		{
			obj.enqueue(temp->right);
		}
		obj.dequeue();
	}
	temp = root;
	cout<<"BFS Traversal: \n";
	for(int i=0; i<totalNodes;i++)
	{
		cout<<"  "<<valuesInTree[i];
	}
	cout<<"Root: "<<root->data;
	 delete[] valuesInTree;
}
int main() {

		BinaryTree obj;
		int choice;
		do{
			cout<<"\n1.Insert Data\n2.Display\n3.Preorder\n4.Inorder\n5.Postorder\n6.Exit\n\nEnter choice code: ";
			cin>>choice;
			switch(choice)
			{
			case 1:
				int data;
				cout<<"\nEnter Data: ";
				cin>>data;
				obj.createTree(data);
				break;
			case 2:
				obj.display();
				break;
			case 3:
				obj.preorder();
				break;
			case 4:
				obj.inorder();
				break;
			case 5:
				break;

			case 6:
				cout<<"\nByeee.....";
			}
		}while(choice!=6);

		return 0;
}
