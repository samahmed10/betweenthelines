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

//https://www.geeksforgeeks.org/construct-tree-from-given-inorder-and-preorder-traversal/ 
// Construct tree from given inorder and preorder traversals
int search(int in[],int start,int end,int data)
{
	for(int i=start;i<=end;i++)
		if(in[i] == data)
			return i;
	return -1;
}
struct node *buildTree(int in[],int pre[],int start,int end)
{
	static int preIndex = 0;
	if(start > end)
		return NULL;
	struct node* root = newNode(pre[preIndex++]);
	if(start == end)
		return root;
	int rootIndexinInorder = search(in,start,end,root->data);
	root->left = buildTree(in,pre,start,rootIndexinInorder-1);
	root->right = buildTree(in,pre,rootIndexinInorder+1,end);
	return root;
}
	
	
int main()
{
  int in[] = {4, 2, 5, 1, 6, 3};
  int pre[] = {1, 2, 3, 4, 5, 6};
  int len = sizeof(in)/sizeof(in[0]);
  struct node *root = buildTree(in, pre, 0, len - 1);
 
  /* Let us test the built tree by printing Insorder traversal */
  cout<<"Inorder traversal of the constructed tree is \n";
  inorder(root);


 
    return 0;
}
