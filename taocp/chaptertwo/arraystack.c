#include<stdio.h>
#include<stdlib.h>

#define SIZE 1024

int array[SIZE];
int stacksize = 0;



void printwarning(const char* msg)
{
	puts(msg);
}



void printerror(const char* msg)
{
	printwarning(msg);
	abort();
}


int empty(void)
{
	return(stacksize == 0);
}


int size(void)
{
	return(stacksize);
}


void push(int value)
{
	array[stacksize]= value;
	stacksize = stacksize + 1;
	if(stacksize > SIZE)
	{
		printerror("Stack Overflow");
	}
}



int pop(void)
{
	if(empty())
	{
		printwarning("Stack Underflow");
		return -1;
	}
	int y = array[stacksize];
	stacksize = stacksize - 1;
	return y;
}



void print_stack(void)
{
	int i;

	if(empty())
	{
		return;
	}

	for(i = 0; i < size(); i++)
	{
		printf("%d\n",array[i]);
	}
}



int main(int argc, const char* argv[])
{
	int i;

	for(i = 0; i < SIZE; i++)
	{
		push(argc+i);
	}

	for(i = 0; i < SIZE -5; i++)
	{
		pop();
	}

	print_stack();


	return 0;
}

