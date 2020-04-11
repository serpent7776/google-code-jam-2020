Square Dance
============

Solving first test case was pretty simple. Read all contestants and then:
- calculate score of this round
- for each contestant:
	* get the number of competitors
	* calculate average skill of competitors
	* if average skill is higher than contestant mark him
- remove all marked contestants
- if at least one contestant was removed do next round

This worked well for first test case, but I got `TLE` on the second.
