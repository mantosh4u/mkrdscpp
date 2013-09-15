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


struct list
{
	int info;
	struct list* link;
};


// Start the queue with empty
// if(front == NULL)&& (rear == LOC(front))
struct list* front = NULL;
struct list* rear = NULL;


struct list* get_avail(void)
{
	return(struct list*)calloc(1,sizeof(struct list));
}


void put_avail(struct list* node)
{
	free((void*)node);
}


int queue_empty(void)
{
	return((front == NULL)&& (rear == (struct list*)&front));
}


void intiailze_queue(void)
{
	rear = (struct list*)&front;
}


void destroy_queue(void)
{
	if(queue_empty())
	{
		return;
	}
	//TODO
}



void insert_rear(int value)
{
	struct list* p = get_avail();
	p->info = value;
	p->link = NULL;

	if(queue_empty())
	{
		front = p;
	}
	rear->link = p;
	rear = p;
}



int remove_front(void)
{
	struct list* p = NULL;
	int value = 0;
	if(front == NULL)
	{
		printwarning("Queue Underflow");
		return -1;
	}
	p = front;
	front = p->link;
	value = p->info;
	put_avail(p);

	if(front == NULL)
	{
		rear = (struct list*)&front;
	}
	return value;
}




void print_queue(void)
{
	if(queue_empty())
	{
		printf("Queue Is Empty\n");
		return;
	}
	printf("Front Side Of Queue\t");
	struct list* p = front;
	while(p)
	{
		printf("<-%d",p->info);
		p = p->link;
	}
	printf("\t\t");
	printf("Back Side Of Queue\n");

}



int main(int argc, const char* argv[])
{
	intiailze_queue();
	int value = 389;
	insert_rear(value);
	value = 400;
	insert_rear(value);
	value = 450;
	insert_rear(value);
	value = 460;
	insert_rear(value);

	print_queue();

	remove_front();
	print_queue();

	destroy_queue();

	return 0;
}


