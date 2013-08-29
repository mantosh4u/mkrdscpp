#include<string.h>
#include<stdlib.h>
#include<stdio.h>


#define MAX_LEN     1000
#define MAX_BUCKETS 1000
#define MULTIPLIER    31
#define LEN	     100


struct wordrec
{
	char*  word;
	unsigned long    count;
	struct wordrec*  next;
};


/* Forward Declaration */
unsigned long hashstring(const char*);
struct wordrec* lookup(const char*, int);
struct wordrec* create_wordrec_object(const char*);
void   destroy_wordrec_object(struct wordrec*);
void   print_hashtable_entry(void);
void   destroy_hastable(void);
void   print_hashtable_statistics(void);
void   print_hastable_loadfactor(void);


/* Initial hash bucket */
struct wordrec* table[MAX_LEN] = {0};


/* Store the total number of keys  */
unsigned long total_key = 0;



unsigned long hashstring(const char* str)
{
	unsigned long hash =0;
	unsigned long out = 0;
	while (*str)
	{
		hash = hash*MULTIPLIER+*str ;
		str++;
	}
	out = hash%MAX_BUCKETS;
	if(out >= MAX_LEN)
	{
		/* Ideally it should never happen. This means
		* that our has function is really bad one.
		*/
		printf("%ld\n",out);
	}
	return out;
}




struct wordrec* lookup(const char* str, int create)
{
	struct wordrec* curr = NULL;
	unsigned long hash = hashstring(str);
	struct wordrec* wp = table[hash];
	
	for(curr = wp; curr != NULL; curr = curr->next)
	{
		if(strcmp(curr->word,str))
		{
			return curr;
		}
		else
		{
			if(curr->next)
			{
				continue;
			}
			else
			{
				goto notfound;
			}
		}
	}

notfound:
	if(create)
	{
		curr = create_wordrec_object(str);
		if(table[hash] == 0)
		{ 
			table[hash] = curr;
		}
		else
		{
			struct wordrec* head = table[hash];
			curr->next = head;
			table[hash] = curr;	
		}
	}
	return curr;
}




struct wordrec* create_wordrec_object(const char* str)
{
	struct wordrec* output = NULL; 
	output = (struct wordrec*)calloc(1,sizeof(struct wordrec));
	output->count = (unsigned long)strlen(str)+1;
	output->word = (char*)calloc(1,output->count); 
	strcpy(output->word,str);
	return output;
}




void destroy_wordrec_object(struct wordrec* node)
{
	free(node->word);
	free(node);
	node = NULL;
}




void print_hashtable_entry(void)
{
	struct wordrec* node = NULL;
	struct wordrec* head = NULL;
	unsigned long i;
		
	for(i = 0;i < MAX_LEN;++i)
	{
		node = table[i];
		if(node == NULL)
		{
			continue;
		}
		else
		{
			printf("(");
			for(head = node; head != NULL; head= head->next)
			{
				printf("%s->",head->word);
			}
			printf(")");
			printf("\n");			
		}
	}
}




void print_hashtable_statistics(void)
{
	struct wordrec* node = NULL;
	float used = 0;
	float unused = 0;
	unsigned long i;
		
	for(i = 0;i < MAX_LEN;++i)
	{
		node = table[i];
		if(node != NULL)
		{
			++used;
			continue;
		}
	}
	unused = (float)MAX_LEN - used;
	
	printf("Hash Table Used is: %lf\n",(used/MAX_LEN)*100);
	printf("Hash Table Unused is: %lf\n",(unused/MAX_LEN)*100);
	printf("Total Key Inserted in Hash Table is: %ld\n",total_key);
}	




void print_hastable_loadfactor(void)
{
	float* lfactor = NULL;
	struct wordrec* node = NULL;
	struct wordrec* head = NULL;
	unsigned long i;
	float count = 0.0;

    lfactor = (float*)calloc(sizeof(float),MAX_LEN);
	
	for(i = 0;i < MAX_LEN;++i)
	{
		node = table[i];
		if(node == NULL)
		{
			continue;
		}
		else
		{
			for(head = node; head != NULL; head = head->next)
			{
				++count	;
			}
		}
		lfactor[i] = count;
		count = 0;
	}
	
	for(i = 0;i < MAX_LEN;++i)
	{
		if(lfactor[i])
		{
			printf("%s\t%lf\n",table[i]->word, lfactor[i]);
		}
	}


	free((void*)lfactor);
}




void destroy_hastable(void)
{
	struct wordrec* node = NULL;
	struct wordrec* head = NULL;
	struct wordrec* temp = NULL;
	unsigned long i;
		
	for(i = 0;i < MAX_LEN;++i)
	{
		node = table[i];
		if(node == NULL)
		{
			continue;
		}
		else
		{
			for(head = node; head != NULL;)
			{
				temp = head->next;
				destroy_wordrec_object(head);
				head = temp;
			}				
		}
	}
}




int main(int argc, const char* argv[])
{
	const char *filename = "input.txt";
	char line[LEN+1];
	FILE *fp;
	char *access = "r";
	struct wordrec* output = NULL;
	const char* queary = "ababababababab";
	size_t len = 0;
	fp = fopen(filename, access);
	memset(line,'\0',LEN+1);
	while ( (fgets(line, LEN,fp ) != NULL ) ) 
	{
		/* 'line' may contains the line feed at 
		*  the end in the buffer. Remove them before
		*  passing to hash table insertion.
		*/
		len  = strlen(line);
		if((line[len-1])== 0xa)
		{
			line[len-1] = 0x0;
		}
		
		lookup(line,1);
		memset(line,'\0',LEN+1);
		++total_key;
	}	
	fclose(fp);
	
	
	/* 
	* Uncomment these two lines two fetch the additional
	* information/print about all entries in the hash table.
	*/
    // print_hashtable_entry();
	// print_hastable_loadfactor();
	print_hashtable_statistics();
	destroy_hastable();
	
	/* Now search the key stored in the queary variable 
	* from hash table 'table'.
	*/
	output = lookup(queary,0);
	if(output)
	{
		printf("%s is in the table\n",queary);
	}

	return 0;
}

