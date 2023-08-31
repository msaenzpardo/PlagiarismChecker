Melanie Saenzpardo 
mis868
ECE312 Summer 2023 

Plagiarism Catcher 

The goal of this project is to check for plagiarism in essays submitted by students. 

The algorithm of this program is to preprocess an essay where we will convert to lowercase
and then remoe punctuation and special characters except the apostrophes('). We will then 
partition that essay in sentence sequences of P. We will compare the list of p-sequences
against the rest fo the essays and so on until all combinations of pairs of essays have been 
iterated through. If a pair of essays has higher or equal than M number of sequences we will
order those pairs in descending order and then it will print the pairs of essays that share 
those sequences from largest to smallest number of p-sequences. The essays that print are the
essays that have a plagiarism suspicion index. 

How to run it? 

BEFORE:: (Unzip file)
-Download the zip file 
- put it into your linux directory 
- type in unzip filename.zip 

1) Insert the directory of files that you want to compare inside the parent directory.
Which is where you have your makefile, your plagiarismCatcher.cpp, hashTable.cpp, and
hashTable.h. 
2) Once you are in the parent directory (by typing cd) type "make"
3) Once the files have been made, type "./plagiarismCatcher name_of_dir p m"
4) Run and have fun!! 

Beware:

- Program might not work for big directories (but can work for medium directories) 
- Please do not try to partition the essays with p values less than 2
- Please do not try to choose 0 as your m otherwise all of the files will print
- Program might be off in count from the original document (posted in ECE312 class)


