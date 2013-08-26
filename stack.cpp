#include"stack.h"
#include"common.h"

using namespace mdatastruct;


stack::stack()
:top(0)
{
	std::fill(S,S+ASIZE,0);
}


stack::~stack()
{

}


inline bool  stack::empty(void)
{
	return(top == 0);
}


inline size_t stack::size(void)
{
	return top;
}


inline void  stack::push(int x)
{
	if(size()== ASIZE)
	{
		throw std::exception("Stack Overflow");
	}
	else
	{
		top = top + 1;
		S[top] = x;
	}
}



inline int stack::pop(void)
{
	if(empty())
	{
		throw std::exception("Stack Underflow");
	}
	else
	{
		top = top - 1;
		return S[top];
	}
}






/*
int main(int argc, char** argv)
{
	mdatastruct::stack os;
	int node = 10;
	for(;;)
	{
		os.push(node);
	}

	return 0;
}
*/


