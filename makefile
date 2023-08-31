final: plagiarismCatcher hashTable
	g++ -o plagiarismCatcher plagiarismCatcher.o hashTable.o
plagiarismCatcher:
	g++ -std=c++11 -O0 -g -Wall -Werror -o plagiarismCatcher.o -c plagiarismCatcher.cpp
hashTable:
	g++ -std=c++11 -O0 -g -Wall -Werror -o hashTable.o -c hashTable.cpp