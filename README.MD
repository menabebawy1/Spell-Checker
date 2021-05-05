Name: Mena Bebawy

Hashing with linear and quadratic probing:
I created linear_probing.h in order to implement linear probing.
It was different than quadratic probing due to the offset which was always 1.

I created a stream to read the given file and insert all the words into a hash table.

I also created accessor functions inside linear_probing.h, quadratic_probing.h, and double_hashing.h to
get the number of elements, table size, number of probes, and number of collisions.

I created another ifstream to ready query_words.txt and check if each word in it is in words.txt

Double hashing:
I implemented double_hashing.txt using a double hashing fucntion inside of FindPos().
I also created an accessor function to return the r-value that was used.
I also created a PreviousPrime() function inside of double_hashing.h in order to use for the R value.
Which is the the biggest prime number that is smaller than the table size.

Spell checker:
I implemented make dictionary which takes in a file, reads it word by word, and creates a dictionary of these words.
I then implemented spellchecker whcih reads a file word by word, and lets the user know if the word is correct or incorrect.
In order to do that, it calls 2 functions Clean() which cleans the given word (i.e. removes all non alphabet charachters
before and after the word + sets all letters to lowercase) and correctWord() which tries cases A, B, and C and checks if
the corrected word is in the dictionary.

---

iii. Complete instructions of how to run your program(s):

To compile on terminal type:  
make clean  
make all  

To run:  
make run1linear: to test linear probing  
make run1quadratic: to test quadratic probing  
make run1double: to test double hashing  
make run2short: to test the spell checker with document1_short.txt  
make run2: to test the spell checker with document1.txt  

---

Sources for linear probing:
Class Textbook
