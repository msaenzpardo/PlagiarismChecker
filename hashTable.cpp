//
// Created by melan on 8/8/2023.
//
#include "hashTable.h"
#include <iostream>

using namespace std;

/*
 * select your bucket size for your hash table. will construct it.
 */
Hash::Hash(int n) {
    bucketSize = n;
    table = new list<string>[bucketSize];
}

/*
 * inserts the element in the bucket that is calculated through the hashing function.
 */
void Hash::insertElement(string key) {
    key = hashProcess(key);
    table[getHash(key)].push_back(key);
    //cout << key << endl;
}

/*
 * if a string is found, we will remove the element from that bucket.
 */
void Hash::removeElement(string key) {
    int x = getHash(key);
    bool done = false;
    list<string>::iterator i;
    for (i = table[x].begin(); i != table[x].end() && !done; i++) {
        if (*i == key) {
            done = true;
        }
    }

    // if item was found in the list then delete it.
    if (i != table[x].end()) {
        table[x].erase(i);
    }
}

/*
 * a function where we will print all of the contents of the hashing function. This hash table does
 * chaining when detecting collisions.
 */
void Hash::printAll() {
    for (int i = 0; i < bucketSize; i++) {
        cout << "Index" << i << ": ";
        for (string j : table[i]) {
            cout << j << "=> ";
        }
        cout << endl;
    }
}

/*
 * this will calculate in which bucket the key will go.
 * the way that this works is that we add the ascii value of each set of strings and we multiply by the
 * hashMul plus the initia value. that result is then modded by the bucket size and that is our final result.
 */
int Hash::getHash(string key) {
    int initialVal = 0;
    int hashMul = 1;
    for (unsigned int i = 0; i < key.length(); i++) {
        initialVal = (initialVal * hashMul) + key[i];
    }
    int res = initialVal % bucketSize;
    return res;
}

/*
 * process the essay by lower casing sentences and eliminating punctuation marks except apostrophes
 */
string Hash::hashProcess(string key) {
    for (unsigned int i = 0; i < key.length(); i++) {
        /*
         * de-capitalize letters (convert back to lowercase haha)
         */
        if (key[i] >= 65 && key[i] <= 90) {
            key[i] += 32;
        }

        /*
         * remove any punctuation marks
         */
        if (key[i] == '.' || key[i] == ',' || key[i] == '?' || key[i] == '!' || key[i] == ':' || key[i] == ';' || key[i] == '"' || key[i] == '-') {
            key.erase(key.begin()+i);
            i--;
        }
    }
    return key;
}

/*
 * this function will basically partition the string that we will be comparing and then store it into the
 * hash table.
 */
void Hash::getChunks(string fileName, string line, int p) {
    ifstream file;
    file.open(line.c_str());
    vector<string> seqQueue;

    bool done = false;

    string tmp;
    if (file.is_open()) {
        for (int i = 0; i < p && !done; i++) {
            if (file.eof()) {
                done = true;
            } else {
                file >> tmp;
                seqQueue.push_back(tmp);
            }
        }
        /*
         * partition in a sequence by the number of p
         */
        while (!done) {
            string key = "";
            for (vector<string>::iterator i = seqQueue.begin(); i < seqQueue.end(); i++) {
                if (i == seqQueue.end() - 1) {
                    key += *i;
                }
                else {
                    key += *i + ' ';
                }
            }
            //cout << key << endl;
            // add the space to the hash table
            /*
             * insert once its been done
             */
            insertElement(key);

            file >> tmp;
            if (file.eof()) {
                done = true;
            }

            else {
                seqQueue.push_back(tmp);
                seqQueue.erase(seqQueue.begin());
            }
        }
    }

    else {
        cout << "Could not open file" << endl;
    }
}

/*
 * this function is similar to chunk but it wont add it to the hash table, we are just partioning the essay that
 * we want to compare with file 1 in order for them to be segmented in the same amount p
 */
int Hash::chunk(string fileName, string line, int p) {
    ifstream file;
    file.open(line.c_str());
    vector<string> seqQueue;
    int colCount = 0;
    bool done = false;

    string tmp;
    if (file.is_open()) {
        for (int i = 0; i < p && !done; i++) {
            if (file.eof()) {
                done = true;
            } else {
                file >> tmp;
                seqQueue.push_back(tmp);
            }
        }

        while (!done) {
            string key = "";
            for (vector<string>::iterator i = seqQueue.begin(); i < seqQueue.end(); i++) {
                if (i == seqQueue.end() - 1) {
                    key += *i;
                }
                else {
                    key += *i + ' ';
                }
            }
            //cout << key << endl;
            // add the space to the hash table

            /*
             * only thing that changes is that this will return the count of how many times we found the
             * string that we processed in the hash table. this will let us know that we had a collision.
             * and then return the number of collisions (mComm)
             */
            string check = hashProcess(key);
            int hashValue = getHash(check);
            for (const string& element: table[hashValue]) {
                if (element == check) {
                    colCount++;
                }
            }

            file >> tmp;
            if (file.eof()) {
                done = true;
            }

            else {
                seqQueue.push_back(tmp);
                seqQueue.erase(seqQueue.begin());
            }
        }
    }

    else {
        cout << "Could not open file" << endl;
    }
    return colCount;
}

/*
 * clear the hash table once it has been used by the file so that it can be ready to use of the next file.
 */
void Hash::clear() {
    for (int i = 0; i < bucketSize; i++) {
        table[i].clear();
    }
}
