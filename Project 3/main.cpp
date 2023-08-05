#include "anagrams.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = vocabularyCreator(dictfile, dict);

    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = potentialSequences(word, dict, nwords, results);
    if (!numMatches) {
        cout << "No matches found" << endl;
    }
    else {
        outcomeDisclosure(results, numMatches);
    }

    return 0;
}