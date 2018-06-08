#include<iostream>
#include<stdlib.h>	
using namespace std;

struct node
{
	int data;
	struct node *next;
};

struct node *newNode(int data)
{
	struct node *newnode = (struct node *)malloc(sizeof(struct node));
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}

void insertFront(struct node **head,int data)
{
	struct node *newnode = newNode(data);
	newnode->next = *head;
	*head = newnode;
}

void insertEnd(struct node **head,int data)
{
	if(*head == NULL)
		*head = newNode(data);
	else
	{
		struct node *temp = *head;
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = newNode(data);
	}
}

void deleteFront(struct node **head)
{
	struct node *temp = *head;
	if(temp)
	{
		*head = temp->next;
		free(temp);
	}
}

void deleteBack(struct node **head)
{
	struct node *temp = *head;
	if(temp == NULL || temp->next == NULL)
	{
		free(temp);
		*head = NULL;
	}
	else
	{
		while(temp->next->next != NULL)
			temp = temp->next;
		free(temp->next);
		temp->next = NULL;
	}
}
	
void deleteKey(struct node **head,int data)
{
	struct node *temp = *head;
	if(temp != NULL && temp->data == data)
	{
		*head = temp->next;
		free(temp);
		return;
	}
	struct node *prev;
	while(temp != NULL && temp->data != data)
	{
		prev = temp;
		temp = temp->next;
	}
	if(temp == NULL)		
		return;
	prev->next = temp->next;
	free(temp);
	return;
}

void deletePos(struct node **head,int pos)
{
	if(*head == NULL)
		return;
	struct node *temp = *head;
	if(pos == 0)
	{
		*head = temp->next;
		free(temp);
		return;
	}
	for(int i=0;i<pos-1 && temp != NULL;i++)
	{
		temp = temp->next;
	}
	if(temp == NULL || temp->next == NULL)
		return;
	struct node *next = temp->next->next;
	free(temp->next);
	temp->next = next;
} 
		
	
void display(struct node *head)
{
	if(head == NULL)
	{
		cout<<"Empty \n";
		return;
	}
	while(head)
	{
		cout<<head->data;
		head = head->next;
	}
}		
int main()
{
	struct node *head = NULL;
	display(head);
	insertFront(&head,5);
        insertFront(&head,6);
        insertEnd(&head,8);
        insertEnd(&head,1);
	insertFront(&head,2);
	insertFront(&head,3);
	display(head);cout<<endl;
	deletePos(&head,10);
	display(head);cout<<endl;
	display(head);cout<<endl;
	deleteBack(&head);
	display(head);cout<<endl;
	deleteBack(&head);
	display(head);cout<<endl;
	deleteBack(&head);
	display(head);cout<<endl;
	deleteBack(&head);
	display(head);cout<<endl;
	return 0;
}
						
