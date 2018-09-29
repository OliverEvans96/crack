C code to brute force crack /etc/shadow entries

# Results

Took 39.5 minutes on 64 CPUs for a total of ~42 CPU hours to crack the password 'test' via brute force, allowing for capitals, numbers, and symbols.

Given that the password space increases exponentially with length, reasonable passwords with a variety of symbols are unrealistic to crack by brute force.

# Log

```
Using 64 threads.
salt: '$6$t21qsxdLd5DsnSjy'
givenHash: 'a3SKms/NLSQUKJMn8S.FMVG0y8hsBKgZYt8yGqZRNXkmcMA2gMhOroUXxlohDBAtNXijbFfO5jE6Eq298TDj00'
Searching...
len=0, nWords = 1
batch 1/1
len=1, nWords = 93
batch 1/1
len=2, nWords = 8649
batch 1/1
len=3, nWords = 804357
batch 1/1
len=4, nWords = 74805201
batch 1/59
batch 2/59
batch 3/59
batch 4/59
batch 5/59
batch 6/59
batch 7/59
batch 8/59
batch 9/59
batch 10/59
batch 11/59
batch 12/59
batch 13/59
batch 14/59
batch 15/59
batch 16/59
batch 17/59
batch 18/59
batch 19/59
batch 20/59
batch 21/59
batch 22/59
batch 23/59
batch 24/59
batch 25/59
batch 26/59
batch 27/59
batch 28/59
batch 29/59
Password is 'test'
133537.79user 110.29system 39:29.07elapsed 5641%CPU (0avgtext+0avgdata 1756maxresident)k
124inputs+0outputs (98major+5876minor)pagefaults 0swaps
```
