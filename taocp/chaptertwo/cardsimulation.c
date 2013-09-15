#include<stdio.h>
#include<string.h>
#include<stdlib.h>


enum tag{UP = 0, DOWN = 1};

enum suit{CLUB =1,DIAMOND= 2,HEARTS=3,SPADES=4};

enum rank{ACE=1, DEUCE=2, THREE=3, FOUR=4,FIVE=5, SIX=6, SEVEN=7,
		  EIGHT=8, NINE=9, TEN=10, ELEVEN=11, TWELVE=12, KING=13 };



struct card
{
	enum tag     cardtag;
	enum suit    suitvalue;
	enum rank    rankvalue;
	char         title[12];
	struct card* next;
};


struct card* top = NULL;



struct card* allocatenode(void)
{
	return(struct card*)calloc(1,sizeof(struct card));
}



void deletenode(struct card* node)
{
	if(node)
	{
		free((void*)node);
		node = NULL;
	}
}



void generate_pile_of_card(void)
{
	struct card* first = NULL;
	first = allocatenode();
	first->cardtag = UP;
	first->suitvalue = DIAMOND;
	first->rankvalue = DEUCE;
	strncpy(first->title,"[_][_]2[_]D",sizeof(first->title));
	first->next = NULL;

	top = first;

	struct card* second = NULL;
	second = allocatenode();
	second->cardtag = UP;
	second->suitvalue = SPADES;
	second->rankvalue = THREE;
	strncpy(second->title,"[_][_]3[_]S",sizeof(second->title));
	second->next = NULL;

	first->next = second;

	struct card* third = NULL;
	third = allocatenode();
	third->cardtag = DOWN;
	third->suitvalue = CLUB;
	third->rankvalue = TEN;
	strncpy(third->title,"[_]10[_]C",sizeof(third->title));
	third->next = NULL;

	second->next = third;
}



void printcard(struct card* node)
{
	if(node != NULL)
	{
		printf("(tag=%d,suit=%d,rank=%2d,title=%s)\n",
				node->cardtag,node->suitvalue,
				node->rankvalue,node->title);
	}
}



void print_cards_stacks(void)
{
	struct card*  tmp = top;
	struct card*  node = NULL;
	while(tmp)
	{
		node = tmp->next;
		printcard(tmp);
		tmp = node;
	}
}



void cleanup_nodes(void)
{
	struct card* tmp = top;
	struct card*  node = NULL;
	while(tmp)
	{
		node = tmp->next;
		deletenode(tmp);
		tmp = node;
	}
}




int main(int argc, const char* argv[])
{

	generate_pile_of_card();
	print_cards_stacks();
	cleanup_nodes();

	return 0;
}


