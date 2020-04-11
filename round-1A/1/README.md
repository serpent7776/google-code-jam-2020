Pattern Matching
================

I initially aimed at solving test case 1. After reading all patterns I found the longest one and checked if the rest was a substring of that (ignoring the asterisk char). If all patterns matched, the longest pattern was the answer. Otherwise there was no possible answer.
To solve test case 2, this was extended to match both prefixes and suffixes, each independently. The answer was prefix concatenated with suffix.
