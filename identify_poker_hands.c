#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokerproblem.h"

typedef enum orderings { RANK_FIRST, SUIT_FIRST } ordering;

char handcodes[10][3] =
{
    "RF", /* Royal flush        */
    "SF", /* Straight flush     */
    "4K", /* Four of a kind     */
    "FH", /* Full house         */
    "FL", /* Flush              */
    "RS", /* Straight           */
    "ST", /* Straight           */
    "3K", /* Three of a kind    */
    "2P", /* Two pair           */
    "PR"  /* Pair               */
};


int highhand(char *cards, char *hand_id);
int match(char *pat, char *handp, ordering o);


int main(int ARGC, char **ARGV)
{
    char cards[CARD_WIDTH * NUM_CARDS + 1];
    char hand_id[5];
    int success;

    while (scanf("%s", cards) != EOF)
    {
        success = highhand(cards, hand_id);
        printf("%s %s\n", cards, success ? hand_id : "--");
    }
}



/* Determine whether the cards array "cards" constitutes a scoring
   five-card-draw-poker hand other than just "nothing with a high
   card."  It is assumed that a function is available that will sort
   the cards ascending by rank first, then suit if any two cards are
   of the same rank but different suits (where "sorted" in the case of
   suits means by alphabetical order, i.e. clubs first, etc.).  If
   successful, "cards" will be unchanged, "hand_id" will contain the
   two-letter code for the hand defined above in this source file, and
   the function will return 1.  If unsuccessful the function will
   return 0. */
int highhand(char *cards, char *hand_id)
{
    int h=-1;
    int i;
    char *p;
    int ace_high=0;

    // Flop aces to "high."
    for (p = cards; p < cards + CARD_WIDTH * 5; p += CARD_WIDTH)
    {
        if (*p == 'a')
        {
            *p = 'n';
            ace_high = 1;
        }
    }
    if (ace_high)
    {
        // Re-sort by rank.
        qsort(cards, 5, sizeof(char) * CARD_WIDTH, rank_first_compare);
        if (match("aA<A<A<A<A", cards, RANK_FIRST))
            h = ROYAL_FLUSH;
        else if (match("aX<X<X<X<X", cards, RANK_FIRST))
            h = ROYAL_STRAIGHT;
    }

    /* Flop aces _back_ but leave cards sorted showing ace high,
       if we have either of the two hands where it matters. */
    for (p = cards; p < cards + CARD_WIDTH * 5; p += CARD_WIDTH)
        if (*p == 'n')
            *p = 'a';

    if (ace_high)
        goto DONE;

    qsort(cards, 5, sizeof(char) * CARD_WIDTH, rank_first_compare);
    if (match("aA<A<A<A<A", cards, RANK_FIRST))
        h = STRAIGHT_FLUSH;
    else if (   match("aAaBaCaDxX", cards, RANK_FIRST)
             || match("xXaAaBaCaD", cards, RANK_FIRST))
        h = FOUR_OF_A_KIND;
    else if (   match("aXaXaXbXbX", cards, RANK_FIRST)
             || match("aXaXbXbXbX", cards, RANK_FIRST))
        h = FULL_HOUSE;
    else if (   match("xAxAxAxAxA", cards, RANK_FIRST))
        h = FLUSH;
    else if (   match("aX<X<X<X<X", cards, RANK_FIRST))
        h = STRAIGHT;
    else if (   match("aXaXaXxXxX", cards, RANK_FIRST)
             || match("xXaXaXaXxX", cards, RANK_FIRST)
             || match("xXxXaXaXaX", cards, RANK_FIRST))
        h = THREE_OF_A_KIND;
    else if (   match("aXaXbXbXxX", cards, RANK_FIRST)
             || match("aXaXxXbXbX", cards, RANK_FIRST)
             || match("xXaXaXbXbX", cards, RANK_FIRST))
        h = TWO_PAIR;
    else if (   match("aXaXxXxXxX", cards, RANK_FIRST)
             || match("xXaXaXxXxX", cards, RANK_FIRST)
             || match("xXxXaXaXxX", cards, RANK_FIRST)
             || match("xXxXxXaXaX", cards, RANK_FIRST))
        h = PAIR;

    DONE:
    if (h >= 0)
    {
        strcpy(hand_id, handcodes[h]);
        return 1;
    }
    return 0;
}


/* TODO maybe: Change pat to be able to be smaller than handp and slid
   around a la classic search algorithms.  Right now, expects pat to
   be the same length as handp */
int match(char *pat, char *handp, ordering o)
{
    char *p, *h, *s;
    char prev_rank[5], prev_suit[5];
    char prev_rank_raw=0, prev_suit_raw=0;
    int prev_rank_idx=-1, prev_suit_idx=-1;
    char goalrank, goalchar, goalsuit;

    /* Initialize prev_rank and prev_suit arrays */
    for (p = prev_rank, s = prev_suit; p < prev_rank + 5; p++, s++)
        *p = *s = 0;

    qsort(handp, 5, sizeof(char) * CARD_WIDTH, o == RANK_FIRST ?
          rank_first_compare : suit_first_compare);

    if (o == RANK_FIRST)
    {
        for (p = pat, h = handp; p < pat + CARD_WIDTH * NUM_CARDS; p += CARD_WIDTH, h += CARD_WIDTH)
        {
            if (*p == 'x')      /* match any rank */
                ;
            else if (*p == '<') /* match previous card's rank + 1 */
            {
                if (*h != prev_rank_raw + 1)
                    return 0;
                else
                    prev_rank_raw = *h;
            }
            else
            {
                for (goalchar = 'a', goalrank = 0; goalchar <= 'e'; goalchar++, goalrank++)
                {
                    if (*p == goalchar) /* match any rank, and save it */
                    {
                        if (prev_rank[goalrank] && prev_rank[goalrank] != *h)
                            return 0;
                        prev_rank_idx = goalrank;
                        prev_rank[goalrank] = *h;
                        prev_rank_raw = *h;
                    }
                }
            }

            if (*(p+1) == 'X')          /* match any suit */
                ;
            else
            {
                for (goalchar = 'A', goalsuit = 0; goalchar <= 'D'; goalchar++, goalsuit++)
                {
                    if (*(p+1) == goalchar)     /* match any suit, and save it */
                    {
                        if (prev_suit[goalsuit] && prev_suit[goalsuit] != *(h+1))
                            return 0;
                        prev_suit_idx = goalsuit;
                        prev_suit[goalsuit] = *(h+1);
                        prev_suit_raw = *(h+1);
                    }
                }
            }
        }
    }
    else
    {
        for (p = pat, h = handp; p < pat + CARD_WIDTH * NUM_CARDS; p += CARD_WIDTH, h += CARD_WIDTH)
        {
            if (*(p+1) == 'X')          /* match any suit */
                ;
            else if (*(p+1) == '<')     /* match previous card's suit + 1 */
            {
                if (*(h+1) != prev_suit_raw + 1)
                    return 0;
                else
                    prev_suit_raw = *(h+1);
            }
            else
            {
                for (goalchar = 'A', goalsuit = 0; goalchar <= 'D'; goalchar++, goalsuit++)
                {
                    if (*(p+1) == goalchar)     /* match any suit, and save it */
                    {
                        if (prev_suit[goalsuit] && prev_suit[goalsuit] != *(h+1))
                            return 0;
                        prev_suit_idx = goalsuit;
                        prev_suit[goalsuit] = *(h+1);
                        prev_suit_raw = *(h+1);
                    }
                }
            }

            if (*p == 'x')      /* match any rank */
                ;
            else
            {
                for (goalchar = 'a', goalrank = 0; goalchar <= 'e'; goalchar++, goalrank++)
                {
                    if (*p == goalchar) /* match any rank, and save it */
                    {
                        if (prev_rank[goalrank] && prev_rank[goalrank] != *h)
                            return 0;
                        prev_rank_idx = goalrank;
                        prev_rank[goalrank] = *h;
                        prev_rank_raw = *h;
                    }
                }
            }
        }
    }
    return 1;
}
