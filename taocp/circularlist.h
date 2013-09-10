/*
 * circularlist.h
 *
 *  Created on: 09-Sep-2013
 *      Author: mantosh
 */

#ifndef CIRCULARLIST_H_
#define CIRCULARLIST_H_

#include"common.h"



struct clinkedlist
{
	int info;
	struct clinkedlist* link;
};



class callocator
{
public:
	struct clinkedlist* intializeheader(void);
	struct clinkedlist* allocatenode(void);
	void deletenode(struct clinkedlist* node);
	void destroyheader(struct clinkedlist* h);
};



struct clinkedlist* callocator::intializeheader(void)
{
	struct clinkedlist* h = allocatenode();
	h->link = h;
	return h;
}


struct clinkedlist* callocator::allocatenode(void)
{
	return (struct clinkedlist*)calloc(1,sizeof(struct clinkedlist));
}


void callocator::deletenode(struct clinkedlist* node)
{
	free((void*)node);
}


void callocator::destroyheader(struct clinkedlist* h)
{
	deletenode(h);
}



class clist
{
public:
	clist();
	~clist();
    struct clinkedlist* insertnode(int value);
    void removenode(struct clinkedlist* node);
    void printlist(void);
private:
	callocator aobject;
	struct clinkedlist* head;
};


clist::clist()
:head(NULL)
{
	head =  aobject.intializeheader();
}


clist::~clist()
{
	struct clinkedlist* node = NULL;
	struct clinkedlist* tmp = head->link;


	while(tmp != head)
	{
		node = tmp;
		tmp = node->link;
		aobject.deletenode(node);
	}

	aobject.destroyheader(head);
	head = NULL;
}



struct clinkedlist* clist::insertnode(int value)
{
	struct clinkedlist* newnode = aobject.allocatenode();
	newnode->info = value;

	struct clinkedlist* tmp = head;
	while(tmp->link != head)
	{
		tmp = tmp->link;
	}

	tmp->link = newnode;
	newnode->link = head;

	return newnode;
}



void clist::removenode(struct clinkedlist* node)
{
	struct clinkedlist* tmp = head;
	if(node != NULL)
	{
		while(!(tmp->link == node))
		{
			tmp = tmp->link;
		}
		tmp->link = node->link;
	}
}


void clist::printlist(void)
{
	/* Skip The Head Pointer While using the current list */
	struct clinkedlist* tmp = head->link;

	while(tmp->link != head)
	{
		printf("%d\t",tmp->info);
		tmp = tmp->link;
	}
	printf("\n");
}






/*
 * Client Function to test the above cicular list class
 */

void test_clist(void)
{
	struct clinkedlist* node[10] = {NULL};

	clist list_int;

	for(int i = 0; i < 10; i++)
	{
		node[i] = list_int.insertnode(i*i);
	}

	list_int.printlist();

	list_int.removenode(node[2]);
	list_int.printlist();

	list_int.removenode(node[0]);
	list_int.printlist();

	list_int.removenode(node[19]);
	list_int.printlist();

}

#endif /* CIRCULARLIST_H_ */
