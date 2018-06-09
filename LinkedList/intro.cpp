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
	int count = 0;
	while(head)
	{
		cout<<head->data;
		count++;
		head = head->next;
	}
	cout<<"\t\tCount "<<count<<endl;
}

void deleteList(struct node **head)
{
	struct node *temp = *head;
	struct node *next;
	while(temp != NULL)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	*head = NULL;
}	
int getCount(struct node *head)
{
	if(!head)
		return 0;
	return 1+getCount(head->next);
}	
int search(struct node *head,int x)
{
	struct node *current = head;
	int count = 0;
	while(current != NULL)
	{
		if(current->data == x)
			return count;
		count++;
		current = current->next;
	}
	return -1;
}	

void printMid(struct node *head)
{
	struct node *fast = head;
	struct node *slow = head;
	if(head)
	{
		while(fast != NULL && fast->next != NULL)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
	}
	cout<<"Mid node is "<<slow->data<<endl;
}

int countnodes(struct node *head)
{
	struct node *temp = head;
	int res = 1;
	while(temp->next != head)
	{
		res ++;
		temp = temp->next;
	}
	return res;
}

void detectloop(struct node *head)
{
	struct node *fast = head,*slow = head;
	if(head)
	{
		while(fast && slow && fast->next)
		{
			fast = fast->next->next;
			slow = slow->next;
			if(fast == slow)
			{
				cout<<"LOOP EXISTS"<<endl;
				cout<<"There are "<<countnodes(slow)<<" nodes in the loop"<<endl;
				return;
			}
		}
	}
	cout<<"NO LOOP"<<endl;
}

void reverse(struct node **head)
{
	struct node *prev = NULL;
	struct node *curr = *head;
	struct node *next;
	while(curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

int compareLists(struct node *head1,struct node *head2)
{
	struct node *temp1=head1,*temp2=head2;
	while(temp1 && temp2)
	{
		if(temp1->data == temp2->data)
		{
			temp1 = temp1->next;		
			temp2 = temp2->next;
		}
		else
			return 0;
	}
	if(!temp1 && !temp2)
		return 1;
	return 0;
}

int checkPalindrome(struct node *head)
{
	struct node *fast = head,*slow = head;
	int res = 0;
	struct node *prev,*second,*midnode=NULL;
	if(head && head->next)
	{
		while(fast &&  fast->next)
		{
			fast = fast->next->next;
			prev = slow;
			slow = slow->next;
		}	
		
		if(fast)
		{
			midnode = slow;
			slow = slow->next;
		}
		second = slow;
		prev->next = NULL;
		reverse(&second);
		res = compareLists(head,second);
		reverse(&second);
		if(midnode)
		{
			prev->next = midnode;
			midnode->next = second;
		}
		else
			prev->next = second;
	}
	return res;
}
				
int main()
{
	struct node *head = NULL;
	deleteList(&head);
	display(head);
	insertFront(&head,7);
        insertFront(&head,4);
        insertEnd(&head,6);
	display(head);
	reverse(&head);
	display(head);
//	head->next->next->next = head;
	detectloop(head);
	if(checkPalindrome(head))
		cout<<"PALINDROME";
	else
		cout<<"NOT A PALINDROME";
	return 0;
}
						
