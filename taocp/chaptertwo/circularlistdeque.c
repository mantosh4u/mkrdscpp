#include<stdio.h>
#include<stdlib.h>

#define TABLESIZE 128


void printwarning(const char* msg)
{
	puts(msg);
}


void printerror(const char* msg)
{
	printwarning(msg);
	abort();
}


struct list
{
	int info;
	struct list* link;
};


// Array of pointing to conceptual left node in the circular linked list
struct list* ptr[TABLESIZE] = {NULL};
int listcount = 0;


struct list* get_avail(void)
{
	return(struct list*)calloc(1,sizeof(struct list));
}


void put_avail(struct list* node)
{
	free((void*)node);
}


void intialize_list(void)
{
	listcount = listcount + 1;
}


int list_empty(void)
{
	return(ptr[listcount] == NULL);
}



struct list* insert_onleft(int value)
{
	struct list* left = NULL;
	left = get_avail();
	left->info = value;
	
	if(list_empty())
	{
		left->link = left;
		ptr[listcount] = left->link;
	}
	else
	{
		left->link = ptr[listcount]->link;
		ptr[listcount]->link = left;
	}
	return left;
}



void insert_onright(int value)
{
	struct list* right = NULL;
	right = insert_onleft(value);
	ptr[listcount] = right;
}




void setleft_anddelete(void)
{
	struct list* left = NULL;
	int value;
	
	if(list_empty())
	{
		printwarning("Underflow");
		return;
	}
	
	left = ptr[listcount]->link;
	value = left->info;
	ptr[listcount]->link = left->link;
	
	if(ptr[listcount] == left)
	{
		ptr[listcount] = NULL;
	}
	put_avail(left);
}



struct list* print_circularlist(void)
{
	if(list_empty())
	{
		return ptr[listcount];
	}
	
	struct list* left = NULL;
	struct list* right = NULL;
	
	//printf("Leftmost Node:");
	right = ptr[listcount]->link;
	left = ptr[listcount];
	
	while(right != left)
	{	
		printf("%d\t",right->info);
		right = right->link;
	}
	printf("%d\n",right->info);	
	
	//printf("Rightmost Node\n");
	return ptr[listcount];
}



struct list* insert_entirelists(struct list* l1, struct list* l2)
{
	if(l2 != NULL)
	{
		if(l1 != NULL)
		{
			struct list* l = l1->link;
			l1->link = l2->link;
			l2->link = l;
		}
		l1 = l2;
		l2 = NULL;
	}
	return l1;
}



void print_mergelists(struct list* l)
{
	if(l == NULL)
	{
		return;
	}
	
	struct list* left = NULL;
	struct list* right = NULL;
	
	//printf("Leftmost Node:");
	right = l->link;
	left = l;
	
	while(right != left)
	{	
		printf("%d\t",right->info);
		right = right->link;
	}
	printf("%d\n",right->info);	
	//printf("Rightmost Node\n");

}




int main(int argc, const char* argv[])
{
	
	// list 1
	struct list* l1 = NULL;
	intialize_list();
	insert_onleft(10);
	insert_onright(20);
	insert_onleft(30);
	insert_onright(40);
	setleft_anddelete();
	l1 = print_circularlist();

	
	//list 2
	struct list* l2 = NULL;
	intialize_list();
	insert_onleft(99);
	insert_onright(88);
	l2 = print_circularlist();

		
	struct list* l3 = insert_entirelists(l1,l2);
	print_mergelists(l3);


	//list 3
	struct list* l4 = NULL;
	intialize_list();
	insert_onleft(96);
	insert_onright(69);
	l4 = print_circularlist();

	struct list* l5 = insert_entirelists(l3,l4);
	print_mergelists(l5);


	return 0;
}

