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
	insertFront(&head,1);
        insertFront(&head,1);
        insertEnd(&head,1);
        insertEnd(&head,1);
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
						
