#!/usr/bin/env perl
$total = 0;
@freqs = ();
@percents = ();

while (<STDIN>)
{
    chomp;
    $total += $_;
    push @freqs, $_;
    $last = $_;
}

if ($ARGV[0] eq '-T' or $ARGV[0] eq '--totaled-already')
{
    $total -= $last;
    pop @freqs;
    push @freqs, $total;
}

foreach $v (@freqs)
{
    push @percents, (($v/$total) * 100);
}

foreach $p (@percents)
{
    printf("% 9.4f%%\n", $p);
}


    

