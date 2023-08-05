#include "permutation.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	string word = "abcde";
	vector<string> results;

	permutating(results, word, "", word);

	cout << "Permutations of '" << word << "':" << endl;
	for (string& result : results) {
		cout << result << endl;
	}
	return 0;
}