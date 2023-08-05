#include "permutation.h"

void permutating(std::vector<std::string>& result, const std::string& word, std::string prefix, std::string rest)
{
	if (rest.empty()) {
		result.push_back(prefix);
		return;
	}
	else {
		for (int i = 0; i < rest.length(); i++) {
			std::string newPrefix = prefix + rest.substr(i,1);
			std::string newRest = rest.substr(0, i) + rest.substr(i + 1);
			permutating(result, word, newPrefix, newRest);
		}
	}
}
