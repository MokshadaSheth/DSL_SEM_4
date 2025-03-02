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
	Node *root=nullptr;  //Changed    //IMP
	Node *temp;
public:

	void createTree();
	void insertNode(Node *newNode, Node *r);
	void ascendingDisplay();
	void desendingDisplay();
	void recursiveAscending(Node *node);
	void recursiveDescending(Node *node);
	Node* helperFunc(Node *t);
	void deleteKey(string);
	Node* findLastRight(Node *r);
	void updateKey();
	void maxComparisons();
	int findHeight(Node*);
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
		root = new Node();
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

	int compVal = temp->key.compare(newNode->key);

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
	if(root == nullptr) cout<<"Tree is empty";
	else recursiveAscending(root);
}
void BST :: recursiveAscending(Node *node)
{
	if(node)
	{
		if(node->left!=nullptr) recursiveAscending(node->left);
		cout<<"  "<<node->key<<"-->"<<node->value<<"\n";
		if(node->right!=nullptr) recursiveAscending(node->right);
	}
}

void BST :: recursiveDescending(Node *node)
{
	if(node)
	{
		if(node->right!=nullptr) recursiveDescending(node->right);
		cout<<"  "<<node->key<<"-->"<<node->value<<"\n";
		if(node->left!=nullptr) recursiveDescending(node->left);
	}
}
void BST :: desendingDisplay()
{
	if(root == nullptr) cout<<"Tree is empty";
	else recursiveDescending(root);
}

void BST::maxComparisons()
{
    cout<<"\nMaximum Comparision needed(Height): "<< findHeight(root);
}

int BST::findHeight(Node* node)
{
    if (node == nullptr)
        return 0; // Base case: empty subtree has height 0
    int leftHeight = findHeight(node->left);
    int rightHeight = findHeight(node->right);
    return max(leftHeight, rightHeight) + 1; // Add 1 for the current level
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

void BST :: deleteKey(string delKey)
{
	cout<<"\nInside del func";
	Node *dummy = root;
	Node *delNode = nullptr;
	if(dummy == nullptr) 
	{
		cout<<"\nTree is empty";
		return;
	}
	if(dummy->key == delKey) //To delete Root
	{
		delNode = dummy;
		dummy = helperFunc(dummy);
		root = dummy;
		delete delNode;
		return;
	}

	while(dummy!=nullptr)
	{
		cout<<"\ninside while";
		if(dummy->key.compare(delKey)>0) //Left side
		{
			if(dummy->left!=nullptr && (dummy->left->key == delKey))
			{
				dummy->left = helperFunc(dummy->left);
				return;
			}else{
				dummy = dummy->left;
			}
		}
		else{
			if(dummy->right!=nullptr && (dummy->right->key == delKey))
			{
				dummy->right = helperFunc(dummy->right);
				return;
			}else
			{
				dummy = dummy->right;
			}
		}
	}

}

Node* BST :: helperFunc(Node *t)
{
	cout<<"\n Helper";
	if(t->left == nullptr) //Check which child is present
	{
		cout<<"Returning: "<<t->right;
		return t->right;
	}
	if(t->right == nullptr)
	{
		return t->left;
	}
	Node *rightChild = t->right;
	Node *lastRight = findLastRight(t->left);
	lastRight->right = rightChild;
	cout<<"\nDeletion Succesfull";
	return t;
}

Node* BST::findLastRight(Node *r)
{
	if(r->right == nullptr)
	{
		return r;
	}
	return findLastRight(r->right);
}

int main() {
	BST obj;
	int choice;
	
	string delKey;
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
		case 4:
			obj.maxComparisons();
			break;
		case 5:
			cout<<"\nEnter key to delete: ";
			cin>>delKey;
			obj.deleteKey(delKey);
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
