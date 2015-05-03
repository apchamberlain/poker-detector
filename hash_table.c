#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pokerproblem.h"

#define HASH_MODULUS 1759


typedef struct node
{
    char *data;
    struct node *next;
} node;


node *table[HASH_MODULUS];


unsigned int hash(char* s)
{
    unsigned long t, a;
    char *p;
    int j, k;

    t = 0;
    
    for (j = 1, p = s; p < s + CARD_WIDTH * NUM_CARDS; p++, j++)
    {
	a = 1;
	for (k = 0; k < j; k++)
	    a *= (unsigned long)((*p) - 'a');
	t += a;
    }
    
    return (t % HASH_MODULUS);
}


void init_hash_table(void)
{
    unsigned int i;

    for (i = 0; i < HASH_MODULUS; i++)
 	table[i] = NULL;
}


void add_to_hash_table(char* string)
{
    node *p, *bucket;
    unsigned int index;
    
    index = hash(string);


                                         if (index >= HASH_MODULUS)
							{
							    fprintf(stderr, "oops\n");

							    exit(1);
							}

    
    bucket = table[index];
    p = malloc(sizeof(node));
    p->data = string;        /* deliberately not a copy--this memory
				is alloc'd/freed elsewhere */
    p->next = bucket;
    table[index] = p;
}


int in_hash_table_p(char *string)
{
    node *p, *bucket;
    unsigned int index;
    
    index = hash(string);

                                         if (index >= HASH_MODULUS)
							{
							    fprintf(stderr, "oops\n");

							    exit(1);
							}

    bucket = table[index];
    p = bucket;
    
    while (p)
    {
	if (!strcmp(string, p->data))
	    return 1;
	p = p->next;
    }

    return 0;
}


void destroy_hash_table(void)
{
    node *p, *bucket, *dead;
    unsigned int i;

    unsigned long c, min, max, total;
    unsigned long counts[HASH_MODULUS];

    min = 1000000;
    
    for (i = 0; i < HASH_MODULUS; i++)
    {
	c = 0;
	bucket = table[i];
	p = bucket;
	while (p)
	{
	    c++;
	    dead = p;
	    p = p->next;
	    free(dead);
	}
	counts[i] = c;
    }

    total = 0;
    for (i = 0; i < HASH_MODULUS; i++)
    {
	c = counts[i];
	total += c;
	if (c < min)
	    min = c;
	if (c > max)
	    max = c;
    }

    fprintf(stderr, "Max bucket depth: %lu\n", max);
    fprintf(stderr, "Min bucket depth: %lu\n", min);
    fprintf(stderr, "Avg bucket depth: %lu\n", total / HASH_MODULUS);
}
