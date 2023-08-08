#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAXRESULTS = 20;       // Max matches that can be found
const int MAXDICTWORDS = 30000;  // Max words that can be read in

size_t countLines(istream &dictfile, string dict[], size_t maxSize);
void loop(size_t i, const string& prefix, const string& rest, string result[],
          const string dict[], size_t size, int &count);
void printPermutations(string result[], const string dict[], size_t size, const string& prefix, const string& rest, int &count);
void filter(vector<string>& output, const string dict[], size_t length, size_t dictCount);
using COND = function<bool(const string &word)>;
bool search(const COND &cond, const string list[], size_t size, size_t steps);
bool match(const string &word, const string list[], size_t size,
           size_t steps = 1);
bool prefixMatch(const string &prefix, const string list[], size_t size,
                 size_t steps = 1);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Puts each string in dictfile into the array dict. Returns the number of words
// read into dict.This number should not be larger than MAXDICTWORDS since that
// is the size of the array.
int vocabularyCreator(istream &dictfile, string dict[]) {
  return countLines(dictfile, dict, MAXDICTWORDS);  // Use the countLines function to write "dict".
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Puts all the possibilities of word which are found in dict into results.
// Returns the number of matched words found.This number should not be larger
// than MAXRESULTS since that is the size of the array.The size is the number of
// words inside the dict array.
int potentialSequences(string word, const string dict[], int size,
                       string results[]) {
  int count = 0;
  vector<string> filteredDict;

  filter(filteredDict, dict, word.length(), size);

  printPermutations(results, filteredDict.data(), filteredDict.size(), "", word,
                    count);

  return count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Displays size number of strings from results. The results can be printed in
// any order.
void outcomeDisclosure(const string results[], int size) {
  if (size == 0) {
    return;
  }
  cout << "Matching word " << results[size - 1] << endl;
  outcomeDisclosure(results, size - 1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// helper functions:
//
//
// 

/**
 * @brief puts dictfile lines into dict
 * @param dictfile file read from text
 * @param dict words to search from
 * @param maxSize maximum number of allowed words in dict
 * @return number of lines in dict
*/
size_t countLines(istream &dictfile, string dict[], size_t maxSize) {
  if (dictfile.eof() || maxSize == 0) {
    return 0;
  }

  if (getline(dictfile, dict[0])) {
    return countLines(dictfile, &dict[1], maxSize - 1) + 1;
  }

  return 0;
}

/**
 * @brief create permutations by switching letters
 * @param i index to make sure iterations don't go over length of rest
 * @param beginning of word
 * @param rest remainder of word 
 * @param result list of permutations that exist in dict
 * @param dict words to search from
 * @param size number of words in dict
 * @param count how many words in result
*/
void loop(size_t i, const string& prefix, const string& rest, string result[],
          const string dict[], size_t size, int &count) {
  if (i >= rest.length()) {
    return;
  }
  std::string newPrefix = prefix + rest.substr(i, 1);
  std::string newRest = rest.substr(0, i) + rest.substr(i + 1);
  i++;
  printPermutations(result, dict, size, newPrefix, newRest, count);
  loop(i, prefix, rest, result, dict, size, count);
}

/**
 * @brief find word in dictionary
 * @param word the word to be searched for
 * @param dict words to search from
 * @param size number of words in dict
 * @return true if word and word in dict are the same
*/
bool match(const string &word, const string dict[], int size) {
  if (size == 0) {
    return false;
  }
  if (word == dict[size - 1]) {
    return true;
  }
  return match(word, dict, size - 1);
}

/**
 * @brief puts permutations into results if it matches a word
 * @param result list of permutations that exist in dict
 * @param dict words to search from
 * @param size number of words in dict
 * @param prefix beginning of word
 * @param rest remainder of word
 * @param count how many words in result
*/
void printPermutations(string result[], const string dict[], size_t size, const string& prefix, const string& rest, int &count) {
  if (count >= MAXRESULTS) {
    return;
  }
  if (rest.empty()) {
    if (!match(prefix, result, count) && match(prefix, dict, size)) {
      result[count++] = prefix;
    }
    return;
  }
  if (prefixMatch(prefix, dict, size, 100)) {
    // continue tring more permutations only if the prefix matches
    loop(0, prefix, rest, result, dict, size, count);
  }
}

/**
 * @brief checks dict for words of the same size
 * @param output the list of words in dict that are the same size as the length
 * @param dict the dictionary or words
 * @param length the length of the word
 * @param dictCount the number of words in dict
*/
void filter(vector<string>& output, const string dict[], size_t length, size_t dictCount) {
  auto lengthMatch = [&output, &length](const string &value) {
    if (length == value.length()) {
      output.push_back(value);
    }
    return false;
  };
  search(lengthMatch, dict, dictCount, 100);
}

/**
 * @brief find a word in an array
 * @param word the word to search
 * @param list the list of words
 * @param size the number of words in the array
 * @param steps number of words to process in a batch
 * @return true if found
 */
bool match(const string &word, const string list[], size_t size, size_t steps) {
  auto wholeWordMatch = [&word](const string &value) { return word == value; };
  return search(wholeWordMatch, list, size, steps);
}

/**
 * @brief check there is any word in the array has the prefix
 * @param prefix the prefix
 * @param list the list of words
 * @param size the number of words in the array
 * @param steps number of words to process in a batch
 * @return true if found
 */
bool prefixMatch(const string &prefix, const string list[], size_t size,
                 size_t steps) {
  if (prefix.empty()) {
    return true;
  }

  auto prefixMatch = [&prefix](const string &value) {
    return prefix == value.substr(0, prefix.length());
  };
  return search(prefixMatch, list, size, steps);
}

/**
 * @brief search the array by condition
 * @param cond the critieria to satisfy
 * @param list the list of strings
 * @param size the number of elements in the list
 * @param steps number of words to process in a batch
 * @return true if found
*/
bool search(const COND &cond, const string list[], size_t size, size_t steps) {
  if (0 == size) {
    return false;
  }

  if (size > steps && steps > 64) {
    if (search(cond, list, steps, 1)) {
      return true;
    }
    return search(cond, &list[steps], size - steps, steps);
  }

  if (cond(list[size - 1])) {
    return true;
  }

  return search(cond, list, size - 1, steps);
}