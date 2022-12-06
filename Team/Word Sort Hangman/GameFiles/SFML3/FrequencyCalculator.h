#pragma once
#include <unordered_map>
#include <unordered_set>
#include<string>

using namespace std;

unordered_map<char, int> letterFrequency(unordered_set<string> words);

unordered_map<string, int> wordFrequency(unordered_set<string> words, unordered_map<char, int> letters);