#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokerproblem.h"


#define SWAPBYTES(CHOMP) ((((CHOMP) << 8) & 0x0) & (((CHOMP) >> 8) & 0xFF00))

void custom_insertion_sort(uint16_t *data, size_t length)
{
    uint16_t *c, *d;
    uint16_t swap;

    for (c = data + 1; c < data + length; c++)
    {
	d = c;
	while ( d > data && 

/* two chars (rank, suit) is like one 16-bit unsigned int where the
   LSB is the rank and the MSB is the suit, thanks to Intel
   little-endianness.  So if we just compared the uint16_ts directly
   we'd get a by-suit sort, or we can swap the upper and lower eight
   bits and get a by-rank sort, exactly equivalent to the
   commented-out parenthesized expression */		


		//TODO - save this on an alternate branch of craziness

		
		
		SWAPBYTES(*d) < SWAPBYTES(*(d - 1))
//		(
//		*((char*)d) < *((char*)(d - chunksize))
//		|| (*((char*)d) == *((char*)(d - chunksize))
//		    && *((char*)(d+1)) == *((char*)(d+1 - chunksize)))
//		    )
	    )
	{
	    swap =*d;
	    *d = *(d-1);
	    *(d-1) = swap;
 	    d--;
	}
    }
}




int main(int ARGC, char **ARGV)
{
    char cards[CARD_WIDTH * NUM_CARDS + 1];

    while (scanf("%s", cards) != EOF)
    {
	custom_insertion_sort((uint16_t*)cards, NUM_CARDS);
//	insertion_sort(cards, 5, sizeof(char) * CARD_WIDTH, rank_first_compare);
//	qsort(cards, 5, sizeof(char) * CARD_WIDTH, rank_first_compare);
        printf("%s\n", cards);
    }
}


/* Sorting the permutations file using Perl:
real	29m42.152s
user	29m1.998s
sys	0m15.537s

   Using this program with library qsort:
real	1m8.469s
user	1m1.460s
sys	0m5.353s

   This program with fairly naive, general-purpose handcoded
   insertion sort:
real	1m24.771s
user	1m16.985s
sys	0m5.939s

   This program with slightly optimized handcoded insertion sort (no
   malloc/free per call to get the intermediate swap buffer, just
   allocating stack RAM):
real	1m5.884s
user	0m59.083s
sys	0m5.265s

   This program with yet slightly more optimized handcoded insertion
   sort (inlining the comparison function):
real	1m1.603s
user	0m53.976s
sys	0m5.845s

   This program with even more optimized handcoded insertion sort (no
   calls to memcpy() or comparisons of bytes, just treat each two
   bytes (rank, suit) as a 16-bit unsigned int):
real	0m59.504s
user	0m51.962s
sys	0m5.771s

*/
