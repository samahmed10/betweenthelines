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
void preorder(struct node *root)
{
	if(root)
	{
		cout<<root->data;
		preorder(root->left);
		preorder(root->right);	
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
vector<struct node *> gettrees(int in[],int start,int end)
{
	vector<struct node *> trees;
	if(start > end)
	{
		trees.push_back(NULL);
	}
	else
	{
		for(int i=start;i<=end;i++)
		{
			vector<struct node *> ltrees = gettrees(in,start,i-1);
			vector<struct node *> rtrees = gettrees(in,i+1,end);
			for(int j = 0;j<ltrees.size();j++)
			{
				for(int k = 0;k<rtrees.size();k++)
				{
					struct node *newnode = newNode(in[i]);
					newnode->left = ltrees[j];
					newnode->right = rtrees[k];
					trees.push_back(newnode);
				}
			}
		}
	}
	return trees;
}	
int main()
{
	int in[] = {4,5,7};
	int n = sizeof(in)/sizeof(in[0]);
	vector<struct node *> trees = gettrees(in,0,n-1);
	for(int i=0;i<trees.size();i++)
	{
		preorder(trees[i]);
		cout<<endl;
	}		
	return 0;
}
