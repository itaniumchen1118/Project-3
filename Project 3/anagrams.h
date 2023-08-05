#pragma once
#include <string>
#include <vector>
using namespace std;

const int MAXRESULTS = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

void countLines(istream& dictfile, string dict[], int& linecount);

int vocabularyCreator(istream& dictfile, string dict[]);

void loop(int i, int max, string prefix, string rest);

void printPermutations(vector<string>& result, const string& word, string prefix, string rest);

void match(string word, const string dict[], int size, string results[]);

void searchDict(int i, int max, vector<string> permutations, const string dict[], int size, string results[]);

int potentialSequences(string word, const string dict[], int
    size, string results[]);

void outcomeDisclosure(const string results[], int size);