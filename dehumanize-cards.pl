#!/usr/bin/env perl -p

# Try to generate the terse format expected by identify_poker_hands.c
# from a plain-English description of a list of set of cards, one set
# per line.   Blank lines are passed straight through.

if (!(m/\w+/))   # Got to have someting to go on.
{
    next;
}
else
{
    @cards = split /\/+|\-+|;|,/;     # Allowable characters to separate cards on a line
    $_ = join('', map &dehumanize($_), @cards);
    $_ .= "\n";
}

sub dehumanize
{
    # Matches e.g. "Queen of Hearts", "jack of clubs", "4:di", "ACE OF SPACE"

    $card = shift;
    ($rank, $suit) = ($card =~ /\b      # Start at word boundary to ignore spaces
                                (\w+)   # Capture rank
                                \s*     # Ignore whitespace, if any
                                (?:     # Skip over whatever separates rank and suit
                                   of   # Hopefully it's "of"
                                  |\|   # but it might be a bar
                                  |:    # or maybe a colon
                                  |\/   # possibly a slash
                                     )  # but there's got to be something
                                \s*     # Ignore whitespace again
                                (\w+)   # Capture suit
                                \b      # End at word boundary
                               /ix);    # Case insensitive match

    if ($rank =~ m/^\d$/)
    {
        $rank =~ tr/1-9/a-i/;
    }
    else
    {
	$rank =~ s/^ace|one/a/i;
	$rank =~ s/^two|deuce|duece/b/i;
	$rank =~ s/^three|trey|tray/c/i;
	$rank =~ s/^four/d/i;
	$rank =~ s/^five/e/i;
	$rank =~ s/^six/f/i;
	$rank =~ s/^seven/g/i;
	$rank =~ s/^eight/h/i;
	$rank =~ s/^nine/i/i;
	$rank =~ s/^ten|10/j/i;
	$rank =~ s/^jack/k/i;
	$rank =~ s/^queen/l/i;
	$rank =~ s/^king/m/i;
    }

    $suit =~ s/^cl.*/A/i;
    $suit =~ s/^di.*/B/i;
    $suit =~ s/^(he|ha).*/C/i;
    $suit =~ s/^sp.*/D/i;

    $rval = $rank . $suit;
    if (length($rval) != 2)
    {	
	die("Parse error in input line $.");
    }
    
    return $rval;
}
