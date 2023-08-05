#pragma once

#include <string>
#include <vector>

/// @brief find all permutations of a word/// 
/// @param result, all the permutations
/// @param word, given word
void permutating(std::vector<std::string>& result, const std::string& word, std::string prefix, std::string rest);