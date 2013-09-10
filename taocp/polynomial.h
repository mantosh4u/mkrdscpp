/*
 * polynomial.h
 *
 *  Created on: 09-Sep-2013
 *      Author: mantosh
 */

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include"common.h"


/*
 * Arithematics on polynomial by using the circular linked list.
 * This shows we need to read this book to understand many beautiful
 * concepts...as no way i could have thought that linked list could
 * be used to do these stuf.. Now lets see how it can be done
 * (x^4 + 2x^3y^1 + 3x^2y^2 + 4x^1y^3 + 5y^4)
 * (x^2 - 2x^1y^1 + y^2)
 * (x^6 - 6x^1y^5 + 5y^6)
 */


/*
 *  Here coefficent is the coeffient of the term x^Ay^Bz^C
 */

struct polynomialnode
{
	int coefficent;
	int x_power;
	int y_power;
	int z_power;
	struct polynomialnode* link;
};



struct polynomialnode* allocatenode(void)
{
	return (struct polynomialnode*)calloc(1,sizeof(struct polynomialnode));
}


void deletenode(struct polynomialnode* node)
{
	free((void*)node);
}



class polynomial
{
public:
	polynomial(const char* input);
	~polynomial();
	void print_polynomial(void);
private:
	struct polynomialnode* ptr;
	char*  expression;
	void   parse_buffer(char* input);
	void   store_values(char* node, int size);
	int    find_power_values(char c, int* position, char* subval,char* tmp,int size);
	void   add_newnodes(struct polynomialnode* inut);
	void   sort_nodes(void);
};


polynomial::polynomial(const char* input)
{
	ptr = allocatenode();
	/*
	 * This special node should be populated in this manner as mentioned on the
	 * page 276, Volume 1
	 */
	ptr->coefficent = 0;
	ptr->x_power = 0;
	ptr->y_power = 0;
	ptr->z_power = -1;
	ptr->link = ptr;

	if(input != NULL)
	{
		size_t size = strlen(input) + 1;
		expression = new char[size];
		memset(expression,'\0',size);
		strcpy(expression, input);
	}

	parse_buffer(expression);
}



polynomial::~polynomial()
{
	/*
	 * TODO: Delete all nodes in the list
	 */
	deletenode(ptr);
	delete [] expression;
}



void polynomial::parse_buffer(char* input)
{
	char* tmp = (char*)input;
	char plus = '+';
	char node[10] = {'\0'};
	char* pos1 = NULL;
	int index = 0;

	do
	{
		pos1 = strchr(tmp,plus);
		if(pos1 != NULL)
		{
			index = pos1 - tmp;
			strncpy(node,tmp,index);
			store_values(node,sizeof(node));

			tmp = tmp + index + 1;
			memset(node,'\0',sizeof(node));
		}
		else
		{
			/*last node requires special attention as strchr would give NULL*/
			/* in that case */
			index = strlen(tmp);
			strncpy(node,tmp,index);
			store_values(node,sizeof(node));
			break;
		}
	}while(1);
}





void polynomial::store_values(char* node, int size)
{
	int i;
	int j;
	int pos;
	char tmp[10] = {'\0'};
	char subval[10] = {'\0'};

	struct polynomialnode* newnode = allocatenode();


	/* Remove the forward trailing space characters from the node */
	for(i = 0, j = 0; j < size; j++)
	{
		if(!isspace(node[j]))
		{
			tmp[i] = node[j];
			i++;
		}
	}

	/* parse the coefficent values */
	pos = 0;
	bool signedvalue = false;
	if(tmp[pos] == '-')
	{
		signedvalue = true;
		pos = pos + 1;
	}

	for(i = 0,j = pos; j < size; j++)
	{
		if(isdigit(tmp[j]))
		{
			subval[i] = tmp[j];
			i++;
		}
		else
		{
			break;
		}
	}

	if(i == 0)
	{
		newnode->coefficent = 1;
		if(signedvalue)
		{
			newnode->coefficent = (-1)*newnode->coefficent;
		}
	}
	else
	{
		newnode->coefficent = atoi(subval);
		if(signedvalue)
		{
			newnode->coefficent = (-1)*newnode->coefficent;
		}
	}


	/* Parse the x values */
	newnode->x_power = find_power_values('x', &j, subval, tmp, sizeof(tmp));
	/* Parse the y values */
	newnode->y_power = find_power_values('y', &j, subval, tmp, sizeof(tmp));
	/* Parse the z values */
	newnode->z_power = find_power_values('z', &j, subval, tmp, sizeof(tmp));

	add_newnodes(newnode);
}





int  polynomial::find_power_values(char c, int* position, char* subval,char* tmp,int size)
{
	int i;
	int j;
	int output = 0;

	int pos = *position;
	memset(subval,'\0',sizeof(subval));

	if(!( (tmp[pos] == c)&&(tmp[pos+1] == '^')) )
	{
		output = 0;
		return output;
	}
	else
	{
		for(i = 0,j = pos+2; i< size; j++)
		{
			if(isdigit(tmp[j]))
			{
				subval[i] = tmp[j];
				i++;
			}
			else
			{
				break;
			}
		}

		output = atoi(subval);
	}

	*position = j;
	return output;
}


void polynomial::add_newnodes(struct polynomialnode* input)
{
	if(ptr->link == ptr)
	{
		/* Empty List in which only one special nodes present */
		ptr->link = input;
		input->link = ptr;
	}
	else
	{
		struct polynomialnode* tmp = ptr;
		while(tmp->link != ptr)
		{
			tmp = tmp->link;
		}
		tmp->link = input;
		input->link = ptr;
	}
}




void polynomial::sort_nodes(void)
{
	/*
	struct polynomialnode* tmp = ptr;
	struct polynomialnode* node = NULL;

	while(tmp->link != ptr)
	{
		node = tmp->link;
		if()

		tmp = tmp->link;
	}
	*/

}



void polynomial::print_polynomial(void)
{
	struct polynomialnode* tmp = ptr->link;
	printf("Expression:%s\n",expression);

	sort_nodes();

	while(tmp->link != ptr)
	{
		printf("(%d,%d,%d,%d)\n",tmp->coefficent,tmp->x_power
								,tmp->y_power, tmp->z_power);
		tmp = tmp->link;
	}

	/* The Last Node */
	printf("(%d,%d,%d,%d)\n",tmp->coefficent,tmp->x_power
								,tmp->y_power, tmp->z_power);

}




void test_polynomial(void)
{

	const char* poly1 = "550x^4z^1 + 2x^3y^1 + -3x^2y^2 + 4x^1y^3 + -5y^4z^0";
	polynomial exp1(poly1);
	exp1.print_polynomial();


	const char* poly2 = "x^2 + -2x^1y^1 +  100y^2";
	polynomial exp2(poly2);
	exp2.print_polynomial();

	const char* poly3 = "333";
	polynomial exp3(poly3);
	exp3.print_polynomial();
}




#endif /* POLYNOMIAL_H_ */
