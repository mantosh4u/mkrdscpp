#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cctype>

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
 * polynomial structure x^Ay^Bz^C
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



/*
 * Friend Function for later usage. This little function is used while
 * sorting/inserting the nodes from the expression.
 */
int get_xyzpowervalue(struct polynomialnode* node)
{
	int value = 0;
	if(node != NULL)
	{
		value = 100*node->x_power + 10*node->y_power + 1*node->z_power;
	}
	return value;
}



/*
* Friend Function for later usage(Print the elements).
*/
void print_polynomial(struct polynomialnode* node)
{
	struct polynomialnode* tmp = node->link;
	while(tmp->link != node)
	{
		printf("(%d,%d,%d,%d)\n",tmp->coefficent,tmp->x_power
								,tmp->y_power, tmp->z_power);
		tmp = tmp->link;
	}

	/* The Last Node */
	printf("(%d,%d,%d,%d)\n",tmp->coefficent,tmp->x_power
							,tmp->y_power, tmp->z_power);
}




/*
* The main "polynomial" struct/class.
*/
struct polynomial
{
	polynomial(const char* input);
	~polynomial();
	void print_expression(void);
	void parse_buffer(char* input);
	void store_values(char* node, int size);
	int  find_power_values(char c, int* position,char* subval,char* tmp,int size);
	void add_newnodes(struct polynomialnode* inut);

	friend void print_polynomial(void);
	friend int get_xyzpowervalue(struct polynomialnode* node);

	struct polynomialnode* ptr;
	char* expression;
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
			index = (int)(pos1 - tmp);
			strncpy(node,tmp,index);
			store_values(node,sizeof(node));

			tmp = tmp + index + 1;
			memset(node,'\0',sizeof(node));
		}
		else
		{
			/*last node requires special attention as strchr would give NULL*/
			/* in that case */
			index = (int)strlen(tmp);
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





int polynomial::find_power_values(char c, int* position, char* subval,char* tmp,int size)
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
		return;
	}
	else
	{
		struct polynomialnode* first = ptr;
		struct polynomialnode* second = NULL;

		while(first->link != ptr)
		{
			if(	get_xyzpowervalue(first->link) > get_xyzpowervalue(input))
			{
				first = first->link;
			}
			else
			{
				/* At this moment there is something in both side of this node */
				second = first->link;
				first->link = input;
				input->link = second;
				return;
			}
		}

		first->link = input;
		input->link = ptr;
		return;
	}
}




void polynomial::print_expression(void)
{
	printf("Expression:%s\n",expression);
	print_polynomial(ptr);
}




/*
 * Addition Of Polynomial which are sorted and stored in the form of the
 * required for this algorithm. Page: 276, Volume:1
 */
struct polynomialnode* polynomial_addition(struct polynomialnode* pp,
										   struct polynomialnode* qq )
{
	struct polynomialnode* p  = NULL;
	struct polynomialnode* q  = NULL;
	struct polynomialnode* q1 = NULL;
	struct polynomialnode* q2 = NULL;

	// Step1: [Initialize]
	p = pp->link;
	q1 = q;
	q = qq->link;

	// Step2: [ABC(p):ABC(q)]
	step2:

	while(get_xyzpowervalue(p) < get_xyzpowervalue(q))
	{
		q1 = q;
		q = q->link;
	}

	if(get_xyzpowervalue(p) == get_xyzpowervalue(q))
	{
		goto step3;
	}

	if(get_xyzpowervalue(p) > get_xyzpowervalue(q))
	{
		goto step5;
	}


	step3:
	// Add Coefficients of polynomial
	if(get_xyzpowervalue(p) < 0)
	{
		return q;
	}

	q->coefficent = q->coefficent + p->coefficent;
	if(q->coefficent == 0)
	{
		goto step4;
	}
	else
	{
		q1 = q;
		p = p->link;
		q = q->link;
		goto step2;
	}


	step4:
	// Delete Zero Term.
	q2 = q;
	q = q->link;
	q1->link = q;
	deletenode(q2);
	p = p->link;
	goto step2;


	step5:
	//Insert the new node into Q.
	q2 = allocatenode();
	// COEF(Q2)<-- COEF(P)
	q2->coefficent = p->coefficent;
	// ABC(Q2)<-- ABC(P)
	q2->x_power = p->x_power;
	q2->y_power = p->y_power;
	q2->z_power = p->z_power;

	q2->link = q;
	q1->link = q2;
	q1 = q2;
	p = p->link;
	goto step2;

}



/*
* Test function for client code usage.
*/
void test_polynomial(void)
{

	const char* poly1 = "x^1 + y^1 + z^1";
	polynomial exp1(poly1);
	exp1.print_expression();

	const char* poly2 = "x^2 + -2y^1 + -z^1";
	polynomial exp2(poly2);
	exp2.print_expression();
	
	struct polynomialnode* output = NULL;
	output = polynomial_addition(exp1.ptr, exp2.ptr);
	
	printf("Addition of two polynomial are:\n");
	print_polynomial(output);

}





int main(int argc, const char* argv[])
{
	test_polynomial();
	return 0;
}


