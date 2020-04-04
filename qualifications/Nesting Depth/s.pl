use warnings;
use strict;

my $N = <>;
for (my $n = 0; $n < $N; $n++)
{
	my $case = $n + 1;
	my $s = <>;
	chomp $s;
	$s =~ s/(1+)/($1)/g;
	print "Case #$case: $s\n";
}
