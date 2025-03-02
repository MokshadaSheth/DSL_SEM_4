void BST :: deleteKey(string delKey)
{
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
		delete delNode;
		return;
	}

	while(dummy)
	{
		if((dummy->left != nullptr) && (dummy->key.compare(delKey))<0)
		{
			if(dummy->left->key == delKey)
			{
				delNode = dummy->left;
				dummy = helperFunc(dummy->left);
				delete delNode;
				return;
			}
			else{
				dummy = dummy->left;
			}
		}
		else if((dummy->right!=nullptr) && (dummy->key.compare(delKey))>0)
		{
			if(dummy->right->key == delKey)
			{
				delNode = dummy->right;
				dummy = helperFunc(dummy->right);
				delete delNode;
				return;
			}
			else{
				dummy = dummy->right;
			}
		}
	}

}

Node* BST :: helperFunc(Node *t)
{
	if(t->left == nullptr) //Check which child is present
	{
		return t->right;
	}
	if(t->right == nullptr)
	{
		return t->left;
	}
	Node *rightChild = t->right;
	t = t->left;
	Node *lastRight = findLastRight(rightChild);
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