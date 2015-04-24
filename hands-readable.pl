#!/usr/bin/env perl -p

# Convert the appreviated poker-hand codes from identify_poker_hands.c
# into something more human-friendly.

s/RF/Royal flush/;
s/SF/Straight flush/;
s/4K/Four of a kind/;
s/FH/Full house/;
s/FL/Flush/;
s/RS/Royal straight/;
s/ST/Straight/;
s/3K/Three of a kind/;
s/2P/Two pair/;
s/PR/Pair/;

