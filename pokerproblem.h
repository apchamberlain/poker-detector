
#define CARD_WIDTH 2
#define NUM_CARDS  5

#define ROYAL_FLUSH 0
#define STRAIGHT_FLUSH 1
#define FOUR_OF_A_KIND 2
#define FULL_HOUSE 3
#define FLUSH 4
#define ROYAL_STRAIGHT 5
#define STRAIGHT 6
#define THREE_OF_A_KIND 7
#define TWO_PAIR 8
#define PAIR 9


extern char handcodes[10][3];

extern int suit_first_compare(void *a, void *b);
extern int rank_first_compare(void *a, void *b);
extern void insertion_sort(void *data, unsigned int length, size_t chunksize, int(*compare)(void *, void*));



//  http://stackoverflow.com/questions/375913/what-can-i-use-to-profile-c-code-in-linux/378024#378024
