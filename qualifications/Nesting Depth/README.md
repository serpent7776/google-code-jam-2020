Nesting Depth
=============

Test set 1
----------
This problem seemed a bit hard initially, so I wrote a quick perl script that just wrapped each block of repeating digit 1 in parens using one simple regex.

Test set 2
----------
Regex was not the way to go for this set. Instead I read digit one by one (say, `A` and `B`), and depending on the difference between the two (`D = B - A`), I put `D` parens right before `B`. When the difference was positive, opening parens were added, when it was negative, closing parens were added.
