#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokerproblem.h"

/***********************************************************************/
/* This is pretty ugly, repetitive code, and not particularly fast,    */
/* due to the repeated calls to sprintf(), memcmp(), and qsort().  It  */
/* does have the virtue of being very conservative in memory usage; it */
/* needs just a couple of dozen bytes on the stack at any one time,    */
/* and no heap space, because it prints the hands one a time as they   */
/* are calculated (presumably to disk).				       */
/***********************************************************************/

int doubles(size_t thingsize, void *mem1, unsigned int len1);
    
int main(int ARGC, char **ARGV)
{
    char cards[CARD_WIDTH * NUM_CARDS + 1];
    
    char i1, i2, j1, j2, k1, k2, l1, l2, m1, m2;
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
							printf("%s\n", cards);
						}
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

	
    
