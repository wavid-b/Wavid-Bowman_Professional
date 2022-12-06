#include "FrequencyCalculator.h"

unordered_map<char, int> letterFrequency(unordered_set<string> words)
{
	unordered_map<char, int> letters;
	for (auto it = words.begin(); it!= words.end(); it++)
	{
		for (unsigned int j = 0; j < (*it).length(); j++)
		{
			char letter = (*it).at(j);
			if (letters.find(letter) == letters.end())
			{
				pair<char, int> temp;
				temp.first = letter;
				temp.second = 1;
				letters.insert(temp);
			}
			else
			{
				letters.find(letter)->second++;
			}
		}
	}
	return letters;
}

unordered_map<string, int> wordFrequency(unordered_set<string> words, unordered_map<char, int> letters)
{
	unordered_map<string, int> wordCount;
	for (auto it = words.begin(); it != words.end(); it++)
	{
		int count = 0;
		for (unsigned int j = 0; j < (*it).length(); j++)
		{
			char letter = (*it).at(j);
			count = count + letters.find(letter)->second;
		}
		pair<string, int> temp;
		temp.first = (*it);
		temp.second = count;
		wordCount.insert(temp);
	}
	return wordCount;
}