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
	//Note: Add queue full and queue empty condition
	void enqueue(Node *d)
	{
		if(rear == 20)
		{
			cout<<"\nQueue is full";
			
		}
		else 
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
	}
	Node dequeue()
	{
		
		if(front == -1)
		{
			cout<<"Queue is empty";
			return NULL;
		}
		else
		{
			Node toReturn = visitedNodes[front];
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
		
	}
	friend class BinaryTree;
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
		if(top == 20) //Stack full
		{
			cout<<"\nStack is Full";
		}
		else
		{
			top++;
			st[top] = *data;
		}	
	}
	Node* pop()
	{
		if(top == -1)
		{
			cout<<"\nStack is empty";
			return NULL;
		}
		
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
	void postorder();
	void swap();
	void height();
	void internalLeaf();
};
int BinaryTree :: totalNodes = 0;

void BinaryTree :: height()
{
	Node *curr = root;
	Stack s;
	int height = 0;
	while(true)
	{
		while(curr)
		{
			if(curr->right != nullptr)
			{
				s.push(curr->right);
			}
			if(curr->left != nullptr)
			{
				curr = curr ->left;
				height++;
			}
		}
		
	}
}

void BinaryTree :: internalLeaf()
{

}
void BinaryTree :: swap()
{
	Node *current = root;
	Stack track;
	while(true)
	{
		while(current)
		{
			if(current->left != nullptr || current->right!=nullptr)
			{
				Node *t = current->left;
				current->left = current->right;
				current->right = t;
			}
			
			if(current->left)
			{
				track.push(current->left);
			}
			current = current->right;
		}
		if(current == nullptr && track.top==-1)
		{
			return;
		}
		current = track.pop();
	}
}
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
			cout<<temp->data<<" ";

			temp = temp->right;
		}
	}
}

void BinaryTree :: postorder()
{
	if (!root) {
        cout << "Tree is empty!" << endl;
        return;
    }
	Stack obj;
	Stack obj2;
	Node *temp = root;
	obj.push(root);
		while(obj.top != -1)
		{
			temp = obj.pop(); 
			obj2.push(temp);     //Storing elements in reverse order in stack

			if(temp->left != nullptr)
			{
				cout<<"\nInside temp->left";
				obj.push(temp->left);
			}
			if(temp->right != nullptr)
			{
				cout<<"\nInside temp->right";
				obj.push(temp->right);
			}
			cout<<"\nIn first while\n obj.top: "<<obj.top<<"  obj2.top: "<<obj2.top;
			
		}
		while(obj2.top != -1)
		{
			temp = obj2.pop();
			cout<<"  "<<temp->data;
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
			cout<<"\n1.Insert Data\n2.Display\n3.Preorder\n4.Inorder\n5.Postorder\n6.Swap Tree\n7.Height of tree\n8.Count Internal and Leaf Node\n9.Exit\n\nEnter choice code: ";
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
				obj.postorder();
				break;
			case 6:
				obj.swap();
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				cout<<"\nByeee.....";
			}
		}while(choice!=9);

		return 0;
}
