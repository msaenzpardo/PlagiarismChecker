//
// Created by melan on 8/8/2023.
//

#ifndef PROJECT8_HASHTABLE_H
#define PROJECT8_HASHTABLE_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

class Hash
{
public:
    Hash(int n);
    void insertElement(string key);
    void removeElement(string key);
    void printAll();
    void getChunks(string fileName, string line, int p);
    int chunk (string fileName, string line, int p);
    void clear();
    ~Hash() {
        delete[] table;
    }
private:
    list <string> *table;
    int bucketSize;
    int getHash(string key);
    string hashProcess (string key);
};


#endif //PROJECT8_HASHTABLE_H
