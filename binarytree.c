#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *input[] = {"now", "is", "the", "time", "for", "all","good", "men"
				 ,"to","come","to","the","aid","of","their","party" };

struct tnode* root = NULL;


struct tnode {
	char* word;
	int   count;
	struct tnode* left;
	struct tnode* right;
	struct tnode* parent;
};



// talloc: make a node
struct tnode* talloc(void)
{
	return (struct tnode*)calloc(1, sizeof(struct tnode));
}


// tassign: populate a node with values
struct tnode* tassign(char* wd)
{
	size_t len = 0;
	struct tnode* out = 0;
	
	if(wd)
	{
		len = strlen(wd);
		out = talloc();
		out->word = (char*)calloc(1, len+1);
		strcpy(out->word,wd);
		out->count = 1;
	}

	return out;
}

//trelase: relase a node and its internal memory held by word
void trelase(struct tnode* node)
{
	if(node)
	{
		free(node->word);	
		free(node);
	}
}



void treewalk_inoder(struct tnode* tree)
{
	if(tree != NULL)
	{
		treewalk_inoder(tree->left);
		printf("(%s,%d)\n",tree->word,tree->count);
		treewalk_inoder(tree->right);
	}
}	
	


struct tnode* treesearch(struct tnode* tree, char* key)
{
if((tree == NULL)||(strcmp(key, tree->word)== 0))
		return tree;
	if(strcmp(key, tree->word) < 0)
		return treesearch(tree->left,key);
	else
		return treesearch(tree->right, key);
}



struct tnode* treemaximum(struct tnode* tree)
{
	while(tree->right != NULL)
		tree = tree->right;
	return tree;
}



struct tnode* treeminimum(struct tnode* tree)
{
	while(tree->left != NULL)
		tree = tree->left;
	return tree;
}





void treeinsert(struct tnode* tree, struct tnode* z)
{
	struct tnode* y = NULL;
	struct tnode* x = root;
	
	while(x != NULL)
	{
		y = x;
		if(strcmp(z->word, x->word) < 0)
			x = x->left;
		else
			x = x->right;
	}		

	z->parent = NULL;

	if(y == NULL)
	{
		// Tree was empty
		root = z;
	}
	else if(strcmp(z->word, y->word) < 0)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}
}


// TODO : Delete The Node
// void treedelete(struct tnode* tree, struct tnode* z)




void do_some_realwork(void)
{
	struct tnode* tmp  = NULL;
	root  = tassign(input[0]);

	unsigned int count = sizeof(input)/sizeof(input[0]);

	for(unsigned int i = 1; i < count; i++)
	{	
		tmp = tassign(input[i]);
		treeinsert(root,tmp);
	}

	treewalk_inoder(root);
	printf("\n");

	tmp = NULL;
	tmp = treemaximum(root);
	if(tmp)
	{
		printf("maximum:%s\n",tmp->word);
	}

	tmp = NULL;
	tmp = treeminimum(root);
	if(tmp)
	{
		printf("minimum:%s\n",tmp->word);
	}

	tmp = NULL;
	char* key = "party";
	tmp = treesearch(root,key);
	if(tmp)
	{
		printf("key found with value: %s\n",tmp->word);
	}

}





int main(int argc, char** argv)
{
	do_some_realwork();
	return 0;
}

