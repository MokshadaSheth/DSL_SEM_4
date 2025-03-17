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
	Node *root = nullptr;

public:
	void createTree(int d);
	void insertNode(Node *newnode, Node *currentParent);
	void inorder();
	Node *inorderSuccessor(Node *node);
	void preorder();
	Node *deleteKey(Node *delNode, int delkey);
	void helperDel(int delKey);
	Node *lastRight(Node *r);
	Node *lastLeft(Node *l);
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
		head->isRchild = true; // For Inorder Algo
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

void TBST ::inorder()
{
	Node *t = head;
	while (true)
	{
		t = inorderSuccessor(t);
		if (t == head)
			return;
		cout << " " << t->data;
	}
}
Node *TBST ::inorderSuccessor(Node *x)
{
	Node *s = x->rthread;
	if (x->isRchild) // If  s is thread then return
	{
		while (s->isLchild)
		{
			s = s->lthread;
		}
	}
	return s;
}
void TBST::preorder()
{
	if (root == nullptr)
		return;
	Node *temp = root;
	// since circular last node connected back to head
	while (temp != head)
	{
		// cout<<"\nTemp: "<<temp<<"\nhead: "<<head<<"\nRoot: "<<root;
		cout << temp->data << "  ";
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
				if (temp->rthread == head)
					return; // Note this breaks the loop
				while (temp->isRchild != true)
				{
					temp = temp->rthread;
				}
				temp = temp->rthread;
			}
			// find the inorder successor last node connected to parent
		}
	}
}
void TBST :: helperDel(int delKey)
{
	root = deleteKey(root,delKey);
	if(root == nullptr)
	{
		cout<<"\nNode to be deleted is not found or it was the last node";
	}
	else{
		cout<<"\nNode deletion successful...\n";
	}
}

Node *TBST::deleteKey(Node *delNode, int delKey)
{
	if (delNode == nullptr)
	{
		return nullptr;
	}

	Node *parent = nullptr;
	Node *node = delNode;

	// Searching for key to be deleted
	while (node != nullptr)
	{
		if (node->data == delKey) 
		{
			break;
		}
		parent = node;
		if (node->data > delKey)
		{
			if (node->isLchild)
			{
				node = node->lthread;
			}
			else
			{
				return delNode; // For cases where we will call it recursively
			}
		}
		else
		{
			if (node->isRchild)
			{
				node = node->rthread;
			}
			else
			{
				return delNode;
			}
		}
	}
	if (node == nullptr) // Node not found
	{
		return delNode;
	}

	// Case 1: Has two children
	if (node->isLchild && node->isRchild)
	{
		Node *inSuc = lastLeft(node->rthread);
		node->data = inSuc->data;
		node->rthread = deleteKey(node->rthread, inSuc->data);
		if(node->rthread == head){ node->isRchild = false;  }  //Specially when we delete root
	}
	// Case 2: Has no child(Leaf Node)
	else if (node->isLchild == false && node->isRchild == false)
	{
		if (parent == nullptr)
		{
			return head; // Node is root
		}
		else if (parent->lthread == node)
		{
			parent->lthread = node->lthread;
			parent->isLchild = false;
		}
		else
		{
			parent->rthread = node->rthread;
			parent->isRchild = false;
		}
	}
	//Case 3: Has One child
	else{
		Node *child = nullptr;
		if(node->isLchild == true)
		{
			child = node->lthread;
		}
		else{
			child = node->rthread;
		}

		//Assigning child
		if(parent == nullptr)
		{
			delNode = child;
		}
		if(parent->lthread == node)
		{
			parent->lthread = child;
		}
		else{
			parent->rthread = child;
		}

		if(node->isLchild ==true)
		{
			Node *pred = lastRight(node->lthread);
			if(pred) pred->rthread = parent;  //Check this for error
		}
		else{
			Node *inSuc = lastLeft(node->rthread);
			if(inSuc) inSuc->lthread = parent;
		}

	}	
	delete node;
	return delNode;
}

Node *TBST ::lastRight(Node *r)
{
	if (r->isRchild == false)
	{
		return r;
	}
	return lastRight(r->rthread);
}
Node *TBST ::lastLeft(Node *l)
{
	if (l->isLchild == false)
	{
		return l;
	}
	return lastLeft(l->lthread);
}
int main()
{
	int choice;
	int delKey;
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
			obj.inorder();
			break;
		case 3:
			obj.preorder();
			break;
		case 4:
			cout << "\nEnter key to delete: ";
			cin >> delKey;
			obj.helperDel(delKey);
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

// void TBST :: deleteKey(int delKey)
// {
// 	cout<<"\nDeleting...\n";
// 	if(root == nullptr)
// 	{
// 		cout<<"\nTree is Empty\n";
// 		return;
// 	}
// 	if(root->data == delKey) //Deletion of root
// 	{
// 		if(!(root->isLchild || root->isRchild)) //last node
// 		{
// 			root = nullptr;
// 			head->lthread = head;
// 			head->isLchild = false;
// 		}
// 		else{
// 			if(root->isLchild == true && root->isRchild == false)
// 			{
// 				cout<<"\nRoot has left";
// 				Node *rightMost = lastRight(root->lthread);
// 				rightMost->rthread = root->rthread;
// 				root = root->lthread;
// 				head->lthread = root;
// 			}
// 			else if(root->isRchild == true && root->isLchild == false)
// 			{
// 				cout<<"\nRoot has right";
// 				Node *leftMost = lastLeft(root->rthread);
// 				leftMost->lthread = root->lthread;
// 				root = root->rthread;
// 				head->lthread = root;
// 			}
// 			else //Both child are present
// 			{
// 				Node *rightMost = lastRight(root->lthread);
// 				rightMost->rthread = root->rthread;
// 				Node *leftMost = lastLeft(rightMost->rthread);
// 				leftMost->lthread = rightMost;
// 				rightMost->isRchild = true;
// 				root = root->lthread;
// 				head->lthread = root;
// 			}

// 		}
// 		return;
// 	}
// 	Node *parent = root;

// 	while(parent!=head)
// 	{
// 		if(parent->data > delKey)
// 		{
// 			if(parent->isLchild == true && parent->lthread->data == delKey)
// 			{
// 				// parent->lthread = helperFunc(parent->lthread,parent);
// 				// return;
// 				Node *t = parent->lthread;
// 				if(t->isLchild==false && t->isRchild==false) //Leaf Node
// 				{
// 					parent->lthread = t->lthread;
// 					parent->isLchild = false;
// 					delete t;
// 					return;
// 				}
// 				else if(t->isLchild == true && t->isRchild == false)
// 				{
// 					cout<<"\nInside left child is present";
// 					parent->lthread = t->lthread;
// 					Node *lastRightNode = lastRight(parent->lthread);
// 					lastRightNode->rthread = t->rthread; //head
// 					return;
// 				}
// 				else if(t->isRchild == true && t->isLchild == false)
// 				{
// 					cout<<"\nInside right child is present";
// 					parent->lthread = t->rthread;
// 					Node *lastLeftNode = lastLeft(parent->lthread);
// 					lastLeftNode->lthread = t->lthread;
// 					return;
// 				}
// 				else{
// 					cout<<"\nInside both child present";
// 					parent->lthread = t->lthread;
// 					Node *rightmost = lastRight(parent->lthread);
// 					rightmost->rthread = t->rthread;
// 					rightmost->isRchild = true;
// 					Node *leftmost = lastLeft(rightmost->rthread);
// 					leftmost->lthread = rightmost;
// 					return;
// 				}
// 			}
// 			else{
// 				parent = parent->lthread;  //If no child then it will point to head
// 			}
// 		}
// 		else
// 		{
// 			if(parent->isRchild == true && parent->rthread->data == delKey)
// 			{
// 				Node *t = parent->rthread;
// 				if(t->isLchild==false && t->isRchild==false) //Leaf Node
// 				{
// 					parent->rthread = t->rthread;
// 					parent->isRchild = false;
// 					delete t;
// 					return;
// 				}
// 				else if(t->isLchild == true && t->isRchild == false)
// 				{
// 					cout<<"\nInside left child is present";
// 					parent->rthread = t->lthread;
// 					Node *lastRightNode = lastRight(parent->rthread);
// 					lastRightNode->rthread = t->rthread; //head
// 					return;
// 				}
// 				else if(t->isRchild == true && t->isLchild == false)
// 				{
// 					cout<<"\nInside right child is present";
// 					parent->rthread = t->rthread;
// 					Node *lastLeftNode = lastLeft(parent->rthread);
// 					lastLeftNode->lthread = t->lthread;
// 					return;
// 				}
// 				else{
// 					cout<<"\nInside both child present";
// 					parent->rthread = t->lthread;
// 					Node *rightmost = lastRight(parent->rthread);
// 					rightmost->rthread = t->rthread;
// 					rightmost->isRchild = true;
// 					Node *leftmost = lastLeft(rightmost->rthread);
// 					leftmost->lthread = rightmost;
// 					return;
// 				}
// 			}
// 			else{
// 				parent = parent->rthread;
// 			}
// 		}
// 	}
// 	cout<<"\nKey does not exists";
// }

