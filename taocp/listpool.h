/*
 * listpool.h
 *
 *  Created on: 08-Sep-2013
 *      Author: mantosh
 */

#ifndef LISTPOOL_H_
#define LISTPOOL_H_


#include"common.h"

/*
 * Linked Allocation Method
 * Page: 254(269)
 *
 */


struct linkedlist
{
	int info;
	struct linkedlist* link;
};


/*
 * make the array of linkedlist which would take out one node
 * This table is known as storage pool.
 * The first node(head) "info" would store the count in the
 * each list. So it would be updated while adding and removing
 * the nodes from our storage pool.
 */



class listpool
{
public:
	listpool();
	~listpool();
	void createpool(void);
	struct linkedlist* getnode(void);
	void putnode(struct linkedlist* node);
	void destroypool(void);

	/*
	 * Data Member
	 */
private:
	unsigned int currentlist;
	struct   linkedlist** headpool;
	struct   linkedlist** tailpool;
	struct   linkedlist* allocatenode(void);
	void     deletenode(struct linkedlist* node);
};



listpool::listpool()
:currentlist(0)
{
	headpool = (struct linkedlist** )malloc(SIZE*sizeof(struct linkedlist));
	tailpool = (struct linkedlist** )malloc(SIZE*sizeof(struct linkedlist));

	for(unsigned int index = 0; index < SIZE; index++)
	{
		headpool[index] = (struct linkedlist*)malloc(sizeof(struct linkedlist));
		headpool[index]->info  = 0;
		headpool[index]->link  = NULL;

		tailpool[index] = (struct linkedlist*)malloc(sizeof(struct linkedlist));
		tailpool[index]->info  = 0;
		tailpool[index]->link  = NULL;
	}
}




listpool::~listpool()
{
	for(unsigned int index = 0; index < SIZE; index++)
	{
		free((void*)headpool[index]);
		free((void*)tailpool[index]);
	}

	free((void*)headpool);
	headpool = (struct linkedlist**)NULL;
	free((void*)tailpool);
	tailpool = (struct linkedlist**)NULL;
}




void listpool::createpool(void)
{
	struct linkedlist* tmp  = NULL;
	struct linkedlist* head = NULL;
	struct linkedlist* tail = NULL;
	struct linkedlist* node = NULL;

	for(unsigned int index = 0; index < SIZE; index++)
	{
		head = headpool[index];
		tail = tailpool[index];

		for(unsigned int count = 0; count < SIZE; count++)
		{
			if(head->link == NULL)
			{
				/* Empty list. Insert a new node and update head and tail */
				node = allocatenode();
				head->link = node;
				head->info = head->info + 1;
				tail = node;
			}
			else
			{
				/* Non Empty list. Insert a new node and update tail*/
				node = allocatenode();
				head->info = head->info + 1;
				tmp = tail;
				tmp->link = node;
				tail = node;
			}
		}
	}
}



struct linkedlist* listpool::getnode(void)
{
	struct linkedlist* tmp  = NULL;

	for(unsigned int index = currentlist; index < SIZE; index++)
	{
		struct linkedlist* head = headpool[index];

		if(head->link != NULL)
		{
			tmp = head->link;
			head->info = head->info - 1;
			/* point to the next node */
			head->link = tmp->link;
			return tmp;
		}
		else
		{
			/* current list got empty so search for the node in next list */
			currentlist = currentlist + 1;
		}

	}

	return tmp;
}



void listpool::putnode(struct linkedlist* node)
{
	struct linkedlist* tmp = NULL;

	if(node != NULL)
	{
		for(unsigned int index = 0; index < SIZE; index++)
			{
				struct linkedlist* head = headpool[index];
				struct linkedlist* tail = tailpool[index];
				if(head->info < SIZE)
				{
					tmp = tail;
					tmp->link = node;
					tail = node;
					head->info = head->info + 1;
				}
			}
	}
}




void listpool::destroypool(void)
{
	struct linkedlist* head = NULL;
	struct linkedlist* node = NULL;

	for(unsigned int index = 0; index < SIZE; index++)
	{
		head = headpool[index];
		while(head->link != NULL)
		{
			node = head->link;
			head->link = node->link;
			deletenode(node);
		}
	}

}




struct linkedlist* listpool::allocatenode(void)
{
	return (struct linkedlist*)calloc(1,sizeof(struct linkedlist));
}




void listpool::deletenode(struct linkedlist* node)
{
	free((void*)node);
}




/*
 * Client Function to test the above listpool class
 */

void test_listpool(void)
{
	struct linkedlist* node = NULL;
	listpool pool;

	pool.createpool();
	for(unsigned int i = 0; i< 4096;i++ )
		node = pool.getnode();
	pool.putnode(node);
	pool.destroypool();

}







#endif /* LISTPOOL_H_ */
