/* This was done in Fall 2015 */
/* This program creates a concordance (list in alphabetical order) from a set of words. */

/* Jacob Chapin */
/* CS211 */
/* Assignment 3 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Function Prototypes */

int insert(char *, char *[], int);
void print(char *[], int);
void empty(char *[], int);

int main(int argc, char *argv[])
{
	/* Get table size and create table */

	int tablesize = atoi(argv[1]);
	char *table[tablesize];
	int tablefilled = 0;

	/* Get lines from standard input */

	char *line = NULL;
	size_t length = 0;
	char *pch;
	int i;
	while (getline(&line, &length, stdin) != -1)
	{
		/* Separate lines into words */

		pch = strtok(line, " .,;:!?\"");
		while (pch != NULL)
		{
			/* Make word lowercase if needed */
			
			for (i = 0; pch[i]; i++)
			{
				pch[i] = tolower(pch[i]);
			}

			/* See if word should be inserted into table */

			tablefilled = insert(pch, table, tablefilled);
			if (tablefilled >= tablesize)
			{
				printf("ERROR: Table is full\n");
				print(table, tablefilled);
				return 0;
			}
			pch = strtok(NULL, " .,;:!?\"\n");
		}
	}
	free(line);
	print(table, tablefilled);
	empty(table, tablefilled);
	return 0;
}

/* Create word table */

int insert(char *word, char *table[], int n)
{
	/* If table is currently empty, add word to table */
	if (n == 0)
	{
		table[0] = word;
		return (n + 1);
	}

	/* If table is not empty, add word to table if it is unique */
	else
	{
		/* Use binary search to see if word is unique */

		int low = 0;
		int high = n;
		int mid;
		int position;
		while (low <= high)
		{
			mid = (low + ((high - low) / 2));
			position = (strcmp(word, table[mid]));
			if (position == 0)
			{
				return n;
			}
			else if (position < 0)
			{
				high = (mid - 1);
			}
			else if (position > 0)
			{
				low = (mid + 1);
			}
			
		}

		/* Element is unique; insert into sorted position */

		int i;
		if (position < 0)
		{
			for (i = (n - 1); i >= mid; i--)
			{
				table[i + 1] = table[i];
			}
			table[i + 1] = word;
		}
		else if (position > 0)
		{
			for (i = (n - 1); i > mid; i--)
			{
				table[i + 1] = table[i];
			}
			table[i + 1] = word;
		}
	}
	return n + 1;
}

/* Print the table */

void print(char *table[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d. %s\n", (i + 1), table[i]);
	}
}

/* Free the table */

void empty(char *table[], int tablefilled)
{
	int i;
	for (i = 0; i < tablefilled; i++)
	{
		free(table[i]);
	}
	free(table);
	return;
}
