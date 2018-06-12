#include<iostream>
#include<stdlib.h>	
#include<bits/stdc++.h>
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

void removeDuplicatesFromSorted(struct node *head)
{
	struct node *current = head;
	struct node *next_node;
	if(!current)
		return;
	while(current->next)
	{
		if(current->data == current->next->data)
		{
			next_node = current->next->next;
			free(current->next);
			current->next = next_node;
		}
		else
			current = current->next;
	}
}
//https://www.geeksforgeeks.org/remove-duplicates-from-an-unsorted-linked-list/
//Remove duplicates from unsorted linked list

void removeDuplicates(struct node *head)
{
	if(!head)
		return;
	struct node *curr = head;
	struct node *prev = NULL;
	unordered_set<int> s;
	while(curr != NULL)
	{
		if(s.find(curr->data) != s.end())
		{
			prev->next = curr->next;
			free(curr);
		}
		else
		{
			s.insert(curr->data);
			prev = curr;
		}
		curr = prev->next;
	}
}

//https://www.geeksforgeeks.org/swap-nodes-in-a-linked-list-without-swapping-data/
void swapNodes(struct node **head,int x,int y)
{
	struct node *prevX=NULL,*currX=*head;
	while(currX && currX->data != x)
	{
		prevX = currX;
		currX = currX->next;
	}

	struct node *prevY=NULL,*currY=*head;
	while(currY && currY->data != y)
	{
		prevY = currY;
		currY = currY->next;
	}

	if(!prevX)
		*head = currY;
	else
		prevX->next = currY;

	if(!prevY)
		*head = currX;
	else
		prevY->next = currX;

	struct node *temp = currX->next;
	currX->next = currY->next;
	currY->next = temp;

}

// https://www.geeksforgeeks.org/pairwise-swap-elements-of-a-given-linked-list/
void swapPairWise(struct node *head)
{
	struct node *temp = head;
	while(temp && temp->next)
	{
		int t = temp->data;
		temp->data = temp->next->data;
		temp->next->data = t;
		temp = temp->next->next;
	}
}

//https://www.geeksforgeeks.org/intersection-of-two-sorted-linked-lists/
void intersection(struct node **head1, struct node **head2,struct node **head3)
{
    // Your Code Here
    struct node *temp1 = *head1;struct node *temp2 = *head2;
    while(temp1 && temp2)
    {
        if(temp1->data == temp2->data)
        {
            insertEnd(head3,temp1->data);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if(temp1->data < temp2->data)
            temp1 = temp1->next;
        else
            temp2 = temp2->next;
    }
}

int main()
{
	struct node *head1 = newNode(1);
	head1->next = newNode(2);
	head1->next->next = newNode(3);
	head1->next->next->next = newNode(4);
	head1->next->next->next->next = newNode(5);
	display(head1);

	struct node *head2 = newNode(1);
	head2->next = newNode(3);
	head2->next->next = newNode(5);
	display(head2);
	struct node *head3 = NULL;
	intersection(&head1,&head2,&head3);

	cout<<"\nIntersection of two lists is : ";
	display(head3);


	return 0;
}
						
