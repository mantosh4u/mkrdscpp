#include<stdio.h>
#include<stdlib.h>

#define SIZE 1024
int array[SIZE];
int front = 0;
int rear  = 0;


void printwarning(const char* msg)
{
	puts(msg);
}


void printerror(const char* msg)
{
	printwarning(msg);
	abort();
}


void insert_rear(int value)
{
	if(rear == SIZE)
	{
		rear = 0;
	}
	else
	{
		rear = rear + 1;
	}

	if(rear == front)
	{
		printerror("Queue Overflow");
	}
	array[rear] = value;
}


int remove_front(void)
{
	if(front == rear)
	{
		printwarning("Queue Underflow");
	}
	if(front == SIZE)
	{
		front = 1;
	}
	else
	{
		front = front + 1;
	}
	int y = array[front];
	return y;
}



int queue_empty(void)
{
	return front == rear;
}



void print_queue(void)
{
	int i;

	printf("Front Side Of Queue\t");

	if(queue_empty())
	{
		printf("Queue Is Empty\n");
		return;
	}

	for(i = front+1; i <= rear; i++)
	{
		printf("<-%d",array[i]);
	}
	printf("\t\t");
	printf("Back Side Of Queue\n");
}




int main(int argc, const char* argv[])
{
	int i;
	int value = 389;
	insert_rear(value);
	value = 400;
	insert_rear(value);
	value = 450;
	insert_rear(value);
	value = 460;
	insert_rear(value);

	print_queue();

	for(i = 0; i <1024; i++)
	{
		insert_rear(i);
	}

	return 0;
}


