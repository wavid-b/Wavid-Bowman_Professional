#include <string>
#include <unordered_set>
#include <iostream>
#include <vector>
using namespace std;
struct words {
  words();
  unordered_set<std::string> w[15];
  unordered_set<std::string> valid_words;
  void makeSets(std::string fileName = "input/my_words3.txt");
  void numOfLetters(int num);
  void letterInput(char letter, bool inWord = false);
  void letterInWithPos(char letter, int pos);
  void printWordsLeft();
  void letterInPosMultiple(vector<int> indicies, char letter);
};