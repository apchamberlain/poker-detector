# Ante up!

Some experimental code inspired by a coding puzzle I was once given in
a job interview:

_Given an arbitrary set of five playing cards, write a program to
determine whether it contains any of the standard poker hands._

It's harder than it sounds at first!  Think about it before looking at
the code, if you don't want to spoil it.

# Testing for valid poker hands

Once built with `make identify_poker_hands` (alternatively, `make
ante-up`), the executable `identify_poker_hands` accepts on standard
input a series of sets of five cards, one set of cards per line,
expressed as follows:

* Card: `a`-`m` maps to *ace* to *king* (low to high)
* Suit: `A` = *Clubs*, `B` = *Diamonds*, `C` = *Hearts*, `D` =
*Spades*

## Example

Given the following hand:

* Six of clubs
* Six of diamonds
* Three of clubs
* Six of spades
* Ace of spades

...the input to `identify_poker_hands` should be `fAfBkAfDaD`.

The program reads from standard input, so you can try it out
immediately, without first generating the complete set of standard data.  The
input does not need to be sorted--the cards in each row can be in any
order (although there are two small helper
scripts to sort all the sets of cards passed in, line by line:
`sort-each-hand-by-rank.pl` and `sort-each-hand-by-suit.pl`).
`identify_poker_hands` should identify the example hand just given as
a three of a kind.  Note that although the cards also contain a pair
(two of a kind), the three of a kind ranks higher in standard poker,
so it takes precedence.

The definitions and relative ranking of the hands are taken from [Wikipedia](http://en.wikipedia.org/wiki/List_of_poker_hands).

The script `dehumanize-cards.pl` reads a list of cards in plain
English, and tries to convert them, treating each line as a group,
into the compact notation expected by `identify_poker_hands.c`.
`humanize-cards.pl` does the opposite.

## Finding all the hands in the deck

This is where it gets fun: while the process of generating all
possible combinations of five cards in the 52-card deck is quite slow,
running `identify_poker_hands` on that data takes just a few seconds.

`make find-all-hands` will process the data file created by `make
list-all-combinations` (or create it if it doesn't already exist),
then generate a corresponding file with two columns, cards and poker
hand (if there is one).  It will also print some interesting summary
statistics about the number of each type of hand found in the sample
data--in other words, answering questions like "The next time I play
poker, what's the chance I'll be dealt a royal flush?" and so on.


# Producing the complete sample set

If you take five cards from a standard 52-card deck, without replacing
each card after you take it, there are 2,598,960 combinations in total
(["52 take 5"](https://www.mathsisfun.com/combinatorics/combinations-permutations.html)
if you remember your basic combinatorics).

Following the principle (first written down by
[Jon Bentley](http://www.amazon.com/dp/0201657880), I think) that code
that is run infrequently should favor simplicity and reliability over
speed--it doesn't matter whether it takes an hour or six hours to generate
your initial data set, if you're just going to start the job before
you leave work and let it run overnight--generating the complete set
of sample data via `make list-all-combinations` is straightforward but
slow.  It takes a couple of hours all told on the fastest machine I
have access to (a 3 Ghz Core i7), and generates an enormous (about 3.5
Gb) intermediate file containing all possible _permutations_ of a
five-card draw--that is, five unique cards where order matters.

In classic Unix style this permutation listing is then piped through a
series of small programs to filter out the duplicates (i.e., keeping
one hand from each set that differ from one another only by order) and
arrive at the canonical list of 2,598,960 combinations (at which point
you can `make clean` to delete the intermediate files if you
want--this latter file is "only" 29 Mb or so).

# How's it work?

`make help` will tell you all the possible make targets.

The heart of `identify_poker_hands.c` is the function `match()` which
essentially implements a state machine to parse a very limited,
specialized regular-expression-like syntax and apply it to a given
test string.  Function `highhand()` defines the possible poker hands
as patterns in this quasi-regex language and calls `match()` to test
the contents of the `cards` array (in the `aA`, etc. format
described above) against each pattern.
