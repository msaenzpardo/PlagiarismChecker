#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <errno.h>
#include <queue>
#include <fstream>
#include <string>
#include <iostream>
#include "hashTable.h"

/*
 * melanie saenzpardo
 * mis868
 * ece312 summer 2023
 */
using namespace std;

/*
 * create a class in order to keep track of the count
 */
class Count
{
public:
    string file1, file2;
    int numColli;
    bool operator < (Count const &rhs) const {
        return (numColli < rhs.numColli);
    }
};

/*
 * open directory
 */
int getdir (string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


int main(int argc, char *argv[]) {

    string dir = argv[1];
    //string dir = string("C:\\Users\\melan\\OneDrive\\Documents\\ECE312\\Project 8\\sm_doc_set");//argv[1];
    vector<string> files = vector<string>();
    string str;
    vector <string> chunksW;
    int pSeqs = stoi(argv[2]);
    //int pSeqs = 6;
    int nComm = stoi(argv[3]);
    //int nComm = 200;

    getdir(dir,files);

    /*
     * we will delete the indexes that have the . and ..
     * that way we can start of files at 0
     */
    for(unsigned int i = 0; i < files.size(); i++){
        if(files[i].substr(0,1) == "."){
            files.erase(files.begin()+i);
            i--;
        }
    }

    /*
     * initialize the hash table with a big number
     */
    Hash h(1000003);

    //int arr[files.size()][(files.size()-1)/2];


    ifstream myFile;
    // testing
    /*int i = 5;
    int j = 20;
    string line = dir + '/' + files[i];
    h.getChunks(dir, line, pSeqs);

    string temp = dir + '/' + files[j];
    int num = h.chunk(dir, temp, pSeqs);
    cout << files[i] << " and " << files[j] << ": " << num << endl;
    */
    /*
     * vector to store the results with a type of count.
     */
    vector<Count> results;
    for (unsigned int i = 0; i <files.size(); i++) {
        /*
         * get the file that we will place the file 1 in and process it.
         */
        string line = dir + '/' + files[i];
        h.getChunks(dir, line, pSeqs);
        for (unsigned int j = i+1; j < files.size(); j++) {
            /*
             * compare against the file 2 and iterate through all of them.
             */
            string temp = dir + '/' + files[j];
            /*
             * if the count is equal or higher than the number of p sequences in common, then we will store the file1,
             * file 2, and the string or key.
             */
            if (h.chunk(dir, temp, pSeqs) >= nComm) {
                Count next;
                next.file1 = files[i];
                next.file2 = files[j];
                next.numColli = h.chunk(dir, temp, pSeqs);

                results.push_back(next);
            }
        }
        /*
         * we clear the hash table and do it again
         */
        h.clear();
    }

    /*
     * sort the results that we got.
     */
    sort(results.begin(), results.end());

    /*
     * iterate through them in descending order!
     */
    for (vector<Count>::iterator i = results.end()-1; i >= results.begin(); i--) {
        cout << i->numColli << ": " << i->file1 << " " << i->file2 << endl;
    }

    myFile.close();
    return 0;
}