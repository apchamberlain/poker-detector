#!/usr/bin/env perl -p

# Try to generate a plain-English description of a list of set of
# cards given the terse format expected by identify_poker_hands.c, one
# set per line.  Blank lines are passed straight through.

if (!(m/\w+/))   # Got to have someting to go on.
{
    next;
}
else
{
    @cards = $_ =~ /../sg;
    $_ = join(', ', map &humanize($_), @cards);
    $_ .= "\n";
}

sub humanize
{
    $card = shift;
    ($rank, $suit) = ($card =~ /([a-m])([A-D])/);
    
    $rank =~ s/^a/Ace/;
    $rank =~ s/^b/Deuce/;
    $rank =~ s/^c/Three/;
    $rank =~ s/^d/Four/;
    $rank =~ s/^e/Five/;
    $rank =~ s/^f/Six/;
    $rank =~ s/^g/Seven/;
    $rank =~ s/^h/Eight/;
    $rank =~ s/^i/Nine/;
    $rank =~ s/^j/Ten/;
    $rank =~ s/^k/Jack/;
    $rank =~ s/^l/Queen/;
    $rank =~ s/^m/King/;

    $suit =~ s/A$/Clubs/;
    $suit =~ s/B$/Diamonds/;
    $suit =~ s/C$/Hearts/;
    $suit =~ s/D$/Spades/;

    $rval = "$rank of $suit";
    if (length($rval) < 6)
    {	
	die("Parse error in input line $.");
    }
    
    return $rval;
}
