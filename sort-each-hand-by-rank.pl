#!/usr/bin/env perl -p
@c = ($_ =~ m/../g);
$_ = join('', (sort { substr($a,0,1) cmp substr($b,0,1) 
			  ||  substr($a,1,1) cmp substr($b,1,1)  } @c));
$_ .= "\n";



