#include <string.h>
#include <stdlib.h>
#include "pokerproblem.h"

int rank_first_compare(void *a, void *b)
{
    char rank1 = *( (char*)a);
    char suit1 = *(((char*)a + 1));
    char rank2 = *( (char*)b);
    char suit2 = *(((char*)b + 1));

    if (rank1 < rank2)
	return -1;
    else if (rank1 > rank2)
	return 1;
    else if (suit1 < suit2)
	return -1;
    else if (suit1 > suit2)
	return 1;
    else
	return 0;
}

int suit_first_compare(void *a, void *b)
{
    char rank1 = *( (char*)a);
    char suit1 = *(((char*)a + 1));
    char rank2 = *( (char*)b);
    char suit2 = *(((char*)b + 1));

    if (suit1 < suit2)
	return -1;
    else if (suit1 > suit2)
	return 1;
    else if (rank1 < rank2)
	return -1;
    else if (rank1 > rank2)
	return 1;
    else
	return 0;
}


/* Deliberately has the same function signature as the library
 * qsort(); should be a drop-in replacement */
void insertion_sort(void *data, unsigned int length, size_t chunksize,
		    int(*compare)(void *, void*))
{
    void *c, *d;
    void *swap;

    swap = malloc(chunksize);
    
    for (c = data + chunksize; c < data + chunksize * length; c += chunksize)
    {
	d = c;
	while ( d > data && compare(d, d - chunksize) < 1)
	{
	    memcpy(swap, d, chunksize);
	    memcpy(d, d - chunksize, chunksize);
	    memcpy(d - chunksize, swap, chunksize);
 	    d -= chunksize;
	}
    }
    
    free(swap);
}

