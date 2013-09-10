/*
 * stack.h
 *
 *  Created on: 08-Sep-2013
 *      Author: mantosh
 */

#ifndef STACK_H_
#define STACK_H_


#include"common.h"

/*
 * Chapter:2 , Page 244
 * Implementation of STACK using the sequential allocation
 * scheme(simple array in c/c++). Knuth has mentioned that
 * we must first try to understand the simplicty and power
 * of sequential stuff before going for "complex stuff".
 */




struct buffer
{
	unsigned int top;
	int X[SIZE];
};


struct stackoperation
{
	void intialize(void);
	void push(int Y);
	int  pop(void);
	void displaystack(void);
	void printerror(const char* msg);
/*
 * Data Member
 */
	struct buffer ostack;
};



void stackoperation::intialize(void)
{
	memset((void*)&ostack, 0,sizeof(struct buffer));
}



void stackoperation::push(int Y)
{
	ostack.top = ostack.top + 1;

	if(ostack.top > SIZE)
	{
		printerror("stack overflow");
	}
	else
	{
		ostack.X[ostack.top] = Y;
	}

}



int stackoperation::pop(void)
{
	int tmp;

	if(ostack.top == 0)
	{
		printerror("stack underflow");
	}
	else
	{
		tmp = ostack.X[ostack.top];
		ostack.top = ostack.top - 1;
	}
	return tmp;
}



void stackoperation::displaystack(void)
{
	for(unsigned int index = ostack.top; index > 0; index--)
	{
		printf("%d\n",ostack.X[index]);
	}

}



void stackoperation::printerror(const char* msg)
{
	puts(msg);
	puts("\n");
	abort();
}




/*
 * Client Function to test the above structure
 */

void test_stackoperation(void)
{
	stackoperation	obj;
	obj.intialize();

	for(int value = 0; value < 5; value++)
	{
		obj.push(value*value+1);
	}

	puts("displaystack");
	obj.displaystack();
	obj.pop();
	puts("displaystack");
	obj.displaystack();

}








#endif /* STACK_H_ */
