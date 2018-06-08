#include<iostream>
#include<stdlib.h>
using namespace std;
//check for property that data value of a node = sum of its children
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
	if(root)
	{
		inorder(root->left);
		cout<<root->data<<endl;
		inorder(root->right);
	}
}

int check(struct node *node)
{
	if(node == NULL || node->left == NULL && node->right == NULL)
		return 1;
	else
	{
		int left_data=0,right_data=0;
		if(node->left)
			left_data = node->left->data;
		if(node->right)
			right_data = node->right->data;
		if(node->data == left_data+right_data && check(node->left) && check(node->right))
			return 1;
		else
			return 0;
	}
}	
int main()
{
	struct node *root = newNode(10);
 	root->left         = newNode(8);
  	root->right        = newNode(2);
  	root->left->left   = newNode(3);
  	root->left->right  = newNode(5);
  	root->right->right = newNode(2);
	inorder(root);
	cout<<endl;
	int res = check(root);	
	cout<<res<<endl;
	return 0;
}
