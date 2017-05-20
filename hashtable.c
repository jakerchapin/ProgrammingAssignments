/* This was done in Fall 2015. */
/* This program stores words from a text file in a hash table. */

/* Jacob Chapin */
/* Assignment 4 */
/* Create a hash table to store words and word count */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

struct NodeType
{
	char *word;
	int count;
	struct NodeType *next;
};
typedef struct NodeType Node;

/* Function Prototypes */
char *lowercase(char *);
unsigned int hash(const char *);
Node **ht_create(void);
int ht_insert(Node **, const char *);
void ht_print(Node **);
void ht_destroy(Node **);

#define HASH_MULTIPLIER 65599
int htsize;

int main(int argc, char *argv[])
{	
	/* Make sure command line input is valid */
	if (argc != 2)
	{
		printf("ERROR: Usage: ./hashtable table_size\n");
		return 0;
	}
	htsize = atoi(argv[1]); // Get table size
	Node **Table; // Create table
	Table = ht_create();
	/* Read text from stdin */
	char *line = NULL;
	size_t length = 0;
	char *token;
	char *delim = " .,;:!?\"\n";
 	char *word;
	int insert_succeeded = 0;
	while (1)
	{
		if (getline(&line, &length, stdin) == -1)
		{
			break; // break at end of stdin
		}
		token = strtok(line, delim);
		while (token != NULL)
		{
			/* Convert string to lowercase and insert into table */
			word = lowercase(token);
			insert_succeeded = ht_insert(Table, word);
			assert(insert_succeeded == 1);
			token = strtok(NULL, delim);
		}
	}
	/* Free line, print table contents, and free the table */
	free(line);
	ht_print(Table);
	ht_destroy(Table);
	return 0;
}

/* Convert string to lowercase */
char *lowercase(char *str)
{
	char *word, *ptr;
	if ((word = strdup(str)) != NULL)
	{
		for (ptr = word; *ptr != '\0'; ptr++)
		{
			*ptr = tolower(*ptr);
		}
	}
	return word;
}
/* Compute hash value for word */
unsigned int hash(const char *str)
{
	int i;
	unsigned int h = 0U;
	for (i = 0; str[i] != '\0'; i++)
	{
		h = h * HASH_MULTIPLIER + (unsigned char) str[i];
	}
	return h % htsize;
}

/* Create hash table */
Node **ht_create(void)
{
	Node **hashtable;
        hashtable = (Node**)calloc(htsize, sizeof(Node));
	return hashtable;
}

/* Insert word into hash table */
int ht_insert(Node **Table, const char *str)
{
	/* Get hash value of word */
	unsigned int hashed;
	hashed = hash(str);
	/* Attempt to insert word into table */
	Node *p, *previous;
	if (Table[hashed] == NULL) 
	{
		p = (Node*)malloc(sizeof(Node));
		p->word = strdup(str);
		p->count = 1;
		p->next = NULL;
		Table[hashed] = p;
		return 1;
	}
	/* Make sure word is not in table */
	for (p = Table[hashed]; p != NULL; previous = p, p = p->next)
	{
		if (strcmp(p->word, str) == 0)
		{
			/* Word is in table; increase count by 1 */
			p->count = p->count+1;
			return 1;
		}
	}
	/* Word is not in table; add to table */
	p = (Node*)malloc(sizeof(Node));
	p->word = strdup(str);
	p->count = 1;
	p->next = NULL;
	previous->next = p;
	return 1;
}

/* Print the table */
void ht_print(Node **Table)
{
	int i;
	Node *p,*q;
	/* Iterate over buckets */
	for (i = 0; i < htsize; i++)
	{
		printf("HT[%d]:", i);
		/* Iterate over nodes in bucket */
		for (p=Table[i]; p!= NULL; p=q)
		{
			q=p->next;
			printf(" [%s, %d]", p->word, p->count);
		}
		printf("\n");
	}
}

/* Free the table */
void ht_destroy(Node **Table)
{
	int i;
	Node *p, *q;
	/* Iterate over buckets and free nodes */
	for (i = 0; i < htsize; i++)
	{
		for (p = Table[i]; p != NULL; p = q)
		{
			q = p->next;
			free(p);
		}
	}
}
