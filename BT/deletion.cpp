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
	
	
int main()
{
	 struct node* root = newNode(10);
    root->left = newNode(11);
    root->left->left = newNode(7);
    root->left->right = newNode(12);
    root->right = newNode(9);
    root->right->left = newNode(15);
    root->right->right = newNode(8);
 
    cout << "Inorder traversal before deletion : ";
    inorder(root);
 
    int key = 11;
    deletenode(root, key);
 
    cout << endl;
    cout << "Inorder traversal after deletion : ";
    inorder(root);
 
    return 0;
}
