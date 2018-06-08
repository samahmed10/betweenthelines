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
void inorder(struct node *root,int n)
{
	static int count = 0;
	if(root)
	{
		inorder(root->left,n);
		count++;
		if(count == n)
		{
			cout<<root->data<<endl;
			return;
		}
		inorder(root->right,n);
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
	
int main()
{	
    struct node* root = newNode(10);
    root->left = newNode(20);
    root->right = newNode(30);
    root->left->left = newNode(40);
    root->left->right = newNode(50);
 
    int n = 3;
 
    inorder(root, n);
    return 0;
}
