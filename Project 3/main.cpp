#include "anagrams.h"
#include "permutation.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "main.h"

using namespace std;


int main() {
    string results[MAXRESULTS];
    vector<string> dict(MAXDICTWORDS);
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = vocabularyCreator(dictfile, dict.data());

    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = potentialSequences(word, dict.data(), nwords, results);
    if (!numMatches) {
        cout << "No matches found" << endl;
    }
    else {
        outcomeDisclosure(results, numMatches);
    }
    return 0;
}