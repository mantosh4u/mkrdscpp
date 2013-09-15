#include<stdio.h>
#include<stdlib.h>

void printwarning(const char* msg)
{
	puts(msg);
}

void printerror(const char* msg)
{
	printwarning(msg);
	abort();
}



//Stack Immplementation Using the List Structure. Page 258, Chapter:2

struct list
{
	int info;
	struct list* link;
};


struct list* get_avail(void)
{
	return(struct list*)calloc(1,sizeof(struct list));
}


void put_avail(struct list* node)
{
	free((void*)node);
}



// Start the stack with empty
struct list* top = NULL;


int stack_empty(void)
{
	return (top == NULL);
}


void push(int value)
{
	struct list* p = get_avail();
	p->info = value;
	p->link = top;

	top = p;
}


int pop(void)
{
	if(stack_empty())
	{
		printwarning("Stack Underflow");
		return -1;
	}

	struct list* p = NULL;
	int value = 0;

	p = top;
	top = p->link;

	value = p->info;
	put_avail(p);

	return value;
}



void print_stack(void)
{
	if(stack_empty())
	{
		return;
	}

	struct list* p = top;
	while(p)
	{
		printf("%d\n",p->info);
		p = p->link;
	}
	return;
}




int main(int argc, const char* argv[])
{
	int val = 0;
	print_stack();

	val = 10;
	push(val);
	val = 20;
	push(val);
	print_stack();

	val = pop();
	print_stack();
	val = pop();
	print_stack();
	val = pop();
	print_stack();

	return 0;
}



