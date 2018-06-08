#include<iostream>
#include<queue>
#include<stdlib.h>
#include<stack>
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
	stack <struct node *> s;
	struct node *temp = root;
	while(1)
	{
		if(temp)
		{
			s.push(temp);
			temp = temp->left;
		}
		else if(!s.empty())
		{
				temp = s.top();
				s.pop();
				cout<<temp->data<<endl;
				temp = temp->right;
		}
		else
			break;
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
	struct node *root = NULL;
	root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	inorder(root);
	cout<<endl;
	insert(root,12);
	insert(root,21);
	inorder(root);	
	return 0;
}
