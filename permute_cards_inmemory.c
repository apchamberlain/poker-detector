#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokerproblem.h"

// TODO: nothing really changed here yet.

// Consider a 2-d array of pointers to pointers to char
// then sorting the pointers, and uniquifying as we output;
// Be open to a different sort than library qsort as well!




// The alternative "adder" algorithm would use as much heap space as
// the minimal data structure to hold all the permutations (not
// combinations) possible of the hand, plus some stack space. (Roughly
// 3.4 Gb.) It would have the virtue of (probably) greater speed and a
// smaller compilation unit (and the resulting data structure could be
// searched, sorted, or analyzed in any other way in memory, rather
// than needing to be read back in from disk in order to be processed,
// e.g. by identify_poker_hands.c).  For example, we could run this
// list through qsort() and then through a purely in-memory
// implementation of the algorithm used by uniq(1) to end up with the
// possible combinations of five cards, not permutations.

// Another compromise is the "adder" algorithm combined with an
// insertion sort to both keep the list sorted as it is generated, and
// also weed out duplicates as they are generated, thereby creating a
// true list of combinations in memory on the fly (not a list of
// permutations which can then be modified into a list of
// combinations).  I believe this could be written to take only a
// little more heap space than needed to store the finished
// combination list (11 * XX [combos ] Mb).


// Consider replacing quicksort for the hand sorts with an insertion sort
// and profiling.

#define DECK_SIZE 52

int member(size_t thingsize, void *mem1, unsigned int len1, void *mem2, unsigned int len2);

int doubles(size_t thingsize, void *mem1, unsigned int len1);

int handcompare(void *a, void *b);

int main(int ARGC, char **ARGV)
{
    char cards[CARD_WIDTH * NUM_CARDS + 1];
    
    char i1, i2, j1, j2, k1, k2, l1, l2, m1, m2;

    int i;
    
    unsigned long permutation_count, c;

    for (permutation_count = DECK_SIZE, i = 0; i < NUM_CARDS; i++)
	permutation_count *= (DECK_SIZE - i - 1);
    
    char **cardlists;

    if (!(cardlists = (char**)(malloc(sizeof(char*) * permutation_count))))
    {
	fprintf(stderr, "Not enough memory to allocate permutations pointer array on heap.\n");
	exit(1);
    }

    c = 0;

    for (i1 = 'a'; i1 <= 'm'; i1++)
	for (i2 = 'A'; i2 <= 'D'; i2++)
	    for (j1 = 'a'; j1 <= 'm'; j1++)
		for (j2 = 'A'; j2 <= 'D'; j2++)
			for (k1 = 'a'; k1 <= 'm'; k1++)
			    for (k2 = 'A'; k2 <= 'D'; k2++)
				    for (l1 = 'a'; l1 <= 'm'; l1++)
					for (l2 = 'A'; l2 <= 'D'; l2++)
					    for (m1 = 'a'; m1 <= 'm'; m1++)
						for (m2 = 'A'; m2 <= 'D'; m2++)
						{
						    sprintf(cards, "%c%c%c%c%c%c%c%c%c%c",
							    i1, i2, j1, j2, k1, k2, l1, l2, m1, m2);
						    qsort(cards, 5, sizeof(char) * CARD_WIDTH,
							  rank_first_compare);
						    if (!doubles(sizeof(char) * CARD_WIDTH, cards, 5))
						    {
							if (!(cardlists[c] = (char*)(malloc((sizeof(char) * CARD_WIDTH * NUM_CARDS + 1)))))
							{
							    fprintf(stderr, "Not enough memory to allocate string for permutation %l\n", c);
							    exit(1);
							}
							strcpy(cardlists[c++], cards);
						    }
						}

    // Note just sorting the pointers!
    qsort(cardlists, permutation_count, sizeof(char*), handcompare);

    for (c = 0; c < permutation_count; c++)
    {
	printf("%s\n", cardlists[c]);
	free(cardlists[c]);
    }

    free(cardlists);

// uniq?
}



int handcompare(void *a, void *b)
{
    char *c = *((char**)a);
    char *d = *((char**)b);

    char *p1, *p2;
    
    int r;

    for (p1 = c, p2 = d; p1 < c + CARD_WIDTH * NUM_CARDS; p1 += CARD_WIDTH, p2 += CARD_WIDTH)
    {
	if (r = rank_first_compare(p1, p2))
	    return r;
    }
    return 0;
}
	




/* Return 1 if any doubled elements are found side-by-side in mem1,
   which has length len1, all lengths expressed in
   thingsizes. */
int doubles(size_t thingsize, void *mem1, unsigned int len1)
{
    char *p;
    for (p = mem1; p < mem1 + (thingsize * (len1 - 1)); p += thingsize)
	if (!memcmp(p, p + thingsize, thingsize))
	    return 1;
    return 0;
}

	
    
    
/* Return 1 if mem2, which has length len2, is found anywhere in mem1
   which has length len1, all lengths expressed in
   thingsizes. */
int member(size_t thingsize, void *mem1, unsigned int len1, void *mem2, unsigned int len2)
{
    char *p;
    for (p = mem1; p < mem1 + thingsize * len1; p += thingsize * len2)
	if (!memcmp(p, mem2, len2))
	    return 1;
    return 0;
}

	
    
