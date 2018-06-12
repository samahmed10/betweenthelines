#include<iostream>
#include<queue>
#include<stdlib.h>
using namespace std;
struct node {
	int data;
	struct node *left;
	struct node *right;
};
struct node* newNode(int data)
{
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	temp->data = data;
	temp->left = temp->right = NULL;
	return temp;
}
void inorder(struct node *root)
{
	if(!root)
		return;
	inorder(root->left);
	cout<<root->data<<endl;
	inorder(root->right);
}

void postorder(struct node *root)
{
	if(root)
	{
		postorder(root->left);	
		postorder(root->right);
		cout<<root->data<<endl;
	}
}

void preorder(struct node *root)
{
	if(root)
	{
		cout<<root->data<<endl;
		preorder(root->left);
		preorder(root->right);
	}
}

void levelorder(struct node *root)
{
	struct node *temp = root;
	if(!root)
		return;
	queue<struct node *> q;
	while(temp)
	{
		cout<<temp->data<<endl;
		if(temp->left)
			q.push(temp->left);
		if(temp->right)
			q.push(temp->right);
		temp = q.front();
		q.pop();
	}
}	
void insert(struct node *root,int key)
{
	queue<struct node*> q;
	q.push(root);
	while(!q.empty())
	{
		struct node *temp = q.front();
		q.pop();
		if(!temp->left)
		{
			temp->left = newNode(key);
			break;
		}
		else
			q.push(temp->left);
		if(!temp->right)
		{
			temp->right = newNode(key);
			break;
		}
		else
			q.push(temp->right);
	}
}
void deleteDeepest(struct node *root,struct node *temp)
{
        queue<struct node *> q;
        q.push(root);
        struct node *curr;
        while(!q.empty())
        {
                curr = q.front();
                q.pop();
                if (curr->right)
                {
                        if(curr->right == temp)
                        {
                                curr->right = NULL;
                                delete(curr->right);
                                break;
                        }
                        else
                                q.push(curr->right);
                }
                if(curr->left)
                {
                        if(curr->left == temp)
                        {
                                curr->left = NULL;
                                delete(curr->left);
                                break;
                        }

                        else
                                q.push(curr->left);
                }
        }
}

void deletenode(struct node *root,int key)
{
	queue<struct node *> q;
	q.push(root);
	struct node *temp,*keynode;
	while(!q.empty())
	{
		temp = q.front();
		q.pop();
		if(temp->data == key)
		{
			keynode = temp;
		}
		if(temp->left)
			q.push(temp->left);
		if(temp->right)
			q.push(temp->right);
	}
	int x = temp->data;
	keynode->data = x;
	deleteDeepest(root,temp);
}

//https://www.geeksforgeeks.org/check-if-a-given-binary-tree-is-sumtree/
//sum of a node should be equal to sum of left and right subtrees 
// O(n^2)

int sum(struct node *root)
{
	if(!root)
		return 0;
	return sum(root->left)+root->data+sum(root->right);
}

int checkSumTree(struct node *root)
{
	if(!root || !root->left || !root->right)
		return 1;
	int lsum = sum(root->left);
	int rsum = sum(root->right);

	if(lsum+rsum == root->data && checkSumTree(root->left) && checkSumTree(root->right))
	{
		return 1;
	}

	return 0;
}

//Same problem with O(n)
int isleaf(struct node *root)
{
	if(!root)
		return 0;
	if(!root->left && !root->right)
		return 1;
	return 0;
}

int checkSumTree2(struct node *root)
{
	if(!root || isleaf(root))
		return 1;
	if(checkSumTree2(root->left) && checkSumTree2(root->right))
	{
		int ls,rs;

		if(!root->left)
			ls = 0;
		else if(isleaf(root->left))
			ls = root->left->data;
		else
			ls = 2 * root->left->data;

		if(!root->right)
			rs = 0;
		else if(isleaf(root->right))
			rs = root->right->data;
		else
			rs = 2 * root->right->data;

		return (ls+rs == root->data);

	}	
	
}

//https://www.geeksforgeeks.org/check-two-nodes-cousins-binary-tree/
//Check if two nodes are cousins 
//1. should be on the same level 2. should not be siblings

int isSibling(struct node *root,struct node *a,struct node *b)
{
	if(!root)
		return 0;
	return ((root->left == a && root->right == b)
			|| (root->left == b && root->right == a)
			|| (isSibling(root->left,a,b))
			|| (isSibling(root->right,a,b)));
}

int level(struct node *root,struct node *a,int lvl)
{
	if(!root)
		return -1;
	if(root == a)
		return lvl;
	int l = level(root->left,a,lvl+1);
	if(l)
		return l;
	return level(root->right,a,lvl+1);
}	

int isCousin(struct node *root,struct node *a,struct node *b)
{
	return (level(root,a,1) == level(root,b,1) && !isSibling(root,a,b));
}

//https://www.geeksforgeeks.org/check-leaves-level/
//check if all leaves are at same level


int checkEachNode(struct node *root,int level,int *leafLevel)
{
	if(!root)
		return 1;
	if(!root->left && !root->right)
	{
		if(*leafLevel == 0)
		{
			*leafLevel = level;
			return 1;
		}
		else
			return (level == *leafLevel);
	}
	return checkEachNode(root->left,level+1,leafLevel) && checkEachNode(root->right,level+1,leafLevel);
}
int checkLeavesLevel(struct node *root)
{
	int level = 0,leafLevel = 0;
	return checkEachNode(root,level,&leafLevel);
}


	
int main()
{

    struct node *root = newNode(12);
    root->left = newNode(5);
    root->left->left = newNode(3);
    root->left->right = newNode(9);
    root->left->left->left = newNode(1);
    root->left->right->left = newNode(1);
    if (checkLeavesLevel(root))
        cout<<"Leaves are at same level\n";
    else
        cout<<"Leaves are not at same level\n";
    return 0;
}
