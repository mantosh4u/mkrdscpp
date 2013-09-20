#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<cmath>


struct block
{
	size_t  size;
	struct block* link;
};

struct block* avail = nullptr;


void intialize_memorymap(void)
{

	struct block* node = nullptr;
	struct block* tmp   = nullptr;
	size_t  nodesize = 0;
	size_t  numnode = 0;
	
	nodesize = sizeof(struct block);

	numnode = 11;
	tmp = (struct block*)calloc(numnode, nodesize);
	// First node is stored in the "avail" pointer.
	avail = tmp;
	tmp->size = numnode*nodesize - nodesize;
	tmp->link = nullptr;
	
	
	numnode = 9;
	node = (struct block*)calloc(numnode, nodesize);
	tmp->link = node;
	node->size = numnode*nodesize - nodesize;
	node->link = nullptr;
	
	
	numnode = 23;
	tmp = (struct block*)calloc(numnode, nodesize);
	node->link = tmp;
	tmp->size = numnode*nodesize - nodesize;
	tmp->link = nullptr;
	
	
	numnode = 5;
	node = (struct block*)calloc(numnode, nodesize);
	tmp->link = node;
	node->size = numnode*nodesize - nodesize;
	node->link = nullptr;
	
}



void display_memoryprint(void)
{
	struct block* p = avail;
	
	printf("Location\tSIZE\t\tLINK\n");
	
	while(p != nullptr)
	{
		printf( "%x\t\t%d\t\t%x\n",p,p->size, p->link);
		p = p->link;
	}
}







void*  firstfit_method(size_t sz)
{
	struct block* q = nullptr;
	struct block* p = nullptr;
	size_t  k = 0;
	void*   out = nullptr;
		
	//A1.[Intialize]
	q = (struct block*)avail;
	
A2: //.[End Of List]
	p = q->link;
	if(p == nullptr)
	{
		return nullptr;
	}	
	
	//A3.[Is SIZE enough]
	if(p->size >= sz)
	{
		// A4:[Reserve N.]
		k = p->size - sz;
		if(k == 0)
		{
			q->link = p->link;
		}
		else
		{
			p->size = k;
		}
		out = (char*)p + k;
		return (void*)out;
	}
	else
	{
		q = p;
		goto A2;
	}
	
}




int main(int argc, const char* argv[])
{
	printf("Intial Memory Map\n");
	intialize_memorymap();
	display_memoryprint();
	
	char* buff = nullptr;
	auto index = 8;
	size_t sz = 0;
	
	do 
	{
		sz = index* sizeof(struct block);
		printf("Going to request buffer size:%d\n", sz);
		buff = (char*)firstfit_method(sz);
		if(buff)
		{
			printf("Successfully Got The Memory of Size:%d at location:%x\n", sz, buff);
			index = index + 2;
			display_memoryprint();
		}
		else
		{
			printf("Out Of Memory\n");
			break;
		}
	}while(1);
	
	return 0;	
}
