# Assignment 6: The Great Firewall of Santa Cruz

This program creates a library of words considered "oldspeak"
and through the use of bloom filters and hash tables, are then either
replaced or banned. The program also can take in text input to parse
through it for any oldspeak, and whether any found oldspeak is 
justification for counsel or re-education, as ruled by the GPRSC  

## How to access and run
- access your directory and find the location of asgn 6
- build the program through typing make with desired args
- the code will then run, prompting for any text to parse
- the user will be notified of any issue if oldspeak is found

## Inputs for files
- sorting uses both both boolean and input args
- valid input args: h:, f:, m
- h: asks for the size of the hashtable to create, default is 10,000
- f: asks for the size of the bloom filter to make, default is 2^20
- m: enables the mtf (move to front) option, optimizing bf and ht usage
- when inputting text to parse, valid words must be alphanumerical
- however, underscores, dashes, and apostrophes are permitted

