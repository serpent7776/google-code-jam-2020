ESAb ATAd
=========

Test set 1
----------
We have 10 bits to discover, but we have 10 reads before fluctuation happens, so just read all bits. That will be the answer.

Test set 2
----------
The approach is to find two pairs of indices that have same distance from the centre of the array (e.g. first and last bit). The first pair (I called that `si`) need to have both bits the same value. The second pair (I called that `di`) need to have different values of the bits.
For example if the real bit array is `11001010` then `di` would be `0` and `si` `1`.

```
 +-si-+
 |    |
11001010
|      |
+--di--+
```

Having that two pairs of bits we can detect any fluctuation after every 10 reads.
After every fluctuation we read all 4 bits and compare with values before fluctuation:
- if all the bits are the same, no change happened
- if all the bits changed, the array was complemented
- if `di` bits swapped its values with each other, but `si` weren't, the array was reversed
- if `di` pair stayed the same, but `si` changed, array was both reversed and flipped

When writing this README I noticed that my implementation was a bit more convoluted than that, but that's what you get writing code at 3 a.m. lol.

Test set 3
----------
Failed, as I was not able to optimise reads. Spending 4 reads just to detect fluctuation was not good enough to fit into 150 reads limit.
