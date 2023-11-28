# Text Analytics and Regular Expressions

For this exercise, you will perform an initial text analysis of a book 
(The Great Gatsby by F. Scott Fitzgerald - provided by [Project Gutenberg](https://www.gutenberg.org/))
with the provided code.

You'll then need to write additional regular expressions to search for specific words within the text.

Finally, you must write additional regular expressions to find specific text patterns.

## Steps

1. Examine the source code for `wordfreq.cpp` and `wordfreq_stop.cpp`. These two 
   programs are nearly identical.  Both read in a file line by line and compute word frequencies.
   They both lowercase the input to avoid differences in lower versus upper case letters (a common
   stop in text analysis when cleansing data). However, `wordfreq_stop` excludes common words 
   from being counted.
2. Compile the programs using make. 
3. Run both programs against the provided book:
   ```bash
   ./wordfreq TheGreatGatsby.txt 
   ./wordfreq_stop stopwords.txt TheGreatGatsby.txt 
   ```
   and examine the differences in the outputs.
4. Next write regular expressions that find various text elements. You can modify `wordfreq.cpp` 
   to test your regular expressions.  However, you'll only need to submit the actual regular 
   expressions to the grader:

   a. Find all words containing 'zz'.

   b. Find all words that end in 'x'

   c. A common rule of thumb in spelling English words is "i before e except after c".
      Find all words that contract this guideline.

   d. Find words containing four consecutive consonants.

5. Write a regular expression to match zip codes in the United States.  Zip codes either contain 5 digits
   or 5 digits, a dash(`-`), and then four more digits. Examples:  XXXXX    XXXXX-XXXX
6. Write a regular expression to match dates in the format of mm/dd/yyyy and extract the year
   portion using a group.  You do not need to valid the digits.
7. Write a regular expression that performs basic matching of a Visa credit card. For this 
   assignment, assume that such a number starts with 4, and has 4 groups of numbers, separated by a space.
   Example: 4xxx xxxx xxxx xxxx

You can alter `wordfreq.cpp` to test your regular expressions or use a site such as 
[https://regex101.com/](https://regex101.com/).

## Submission
For the submissions, answer the following questions in a file called "answers.txt" and submit to the
Gradescope assignment. Do not include the question number.  The file will looks will look like - 
```text
was
daisy
\\b[a-zA-Z]+\\b
...
A
```

1. Including the stop words, which word appears most frequently?
2. Excluding stop words, which word appears most frequently?
3. What is the regular expression used to find all words containing 'zz'?
4. What is the regular expression to find all words that end in 'x'?
5. What is a regular expression that finds words where 'ei' appears after letters besides 'c'?
6. What is a regular expression that finds words with four consecutive consonants?
7. What is the regular expression to find valid zip codes?
8. What is the regular expression to match dates in the format of mm/dd/yyyy with the capability to 
   extract the year?
9. What is the regular expression to match the credit card number as defined in the assignment?
10. The word frequency programs use a C++ Standard Template map class to store words and their 
    frequencies.  Which data structure does C++ use to implement a map?
    
    A. a linked list

    B. a hash table

    C. an AVL tree

    D. a red-black tree

    E. b+ index tree  
