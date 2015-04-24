CPPFLAGS = -I include -O3 -Wall

.PHONY: help
help:
	cat makehelp.txt


.PHONY: list-all-combinations
list-all-combinations: list-all-permutations sort-each-hand-by-rank.pl
	./sort-each-hand-by-rank.pl < permutations-5-cards-unsorted.txt > permutations-5-cards-sortedhands.txt ; cat permutations-5-cards-sortedhands.txt | sort |uniq > combinations-5-cards.txt


.PHONY: list-all-permutations
list-all-permutations: list-permutations
	./list-permutations > permutations-5cards-unsorted.txt


.PHONY: find-all-hands
find-all-hands: identify_poker_hands hands-readable.pl combinations-5-cards.txt
	cat combinations-5-cards.txt | ./identify_poker_hands > hands-marked-unsorted.txt ; cat hands-marked-unsorted.txt |sort > hands-marked-sorted.txt ; cat hands-marked-sorted.txt | ./hands-readable.pl > hands-marked-readable.txt ; cat hands-marked-readable.txt  |cut -d ' ' -f 2- | sort | uniq -c | sort --numeric |perl -pe 'BEGIN {$total = 0;} s/(\s*)(\d*) ([A-Z]|-)/$2\t$3/; $total += $2; END {print "$total\tTOTAL\n"; }' > summary.txt


combinations-5-cards.txt: list-all-combinations

ante-up: identify_poker_hands

identify_poker_hands: identify_poker_hands.o card_sort_helpers.o

list-permutations: card_sort_helpers.o

identify_poker_hands.o: pokerproblem.h

card_sort_helpers.o: pokerproblem.h

list-permutations.o: pokerproblem.h


.PHONY: clean
clean:
	rm *.o permutations-5-cards-sortedhands.txt hands-marked-unsorted.txt
