#include "words.h"
#include <fstream>
#include <iostream>
using namespace std;
vector<int> findIndicies1(char guess, string solution) {
    vector<int> output;
    string g = "";
    g += guess;
    for (int i = 0; i < solution.length(); i++) {
        if (solution.substr(i, g.length()) == g) {
            output.push_back(i);
        }
    }
    return output;
}
void words::makeSets(string fileName) {
  ifstream input(fileName);
  string curLine;
  int curLen;
  int count = 0;
  while (input) {
    input >> curLine;
    curLen = curLine.size();
    w[curLen].insert(curLine);
    valid_words.insert(curLine);
  }
  cout << "sets made" << endl;
}
void words::numOfLetters(int num) { valid_words = w[num]; }
void words::letterInput(char letter, bool inWord) {
  unordered_set<string> with;
  unordered_set<string> without;
  string curString;
  for (auto it = valid_words.begin(); it != valid_words.end(); it++) {
    // check if the word at the iterator has the letter or not
    curString = *it;
    if (curString.find(letter) != string::npos) {
      with.insert(curString);
    } else {
      without.insert(curString);
    }
  }
  if (inWord) {
    valid_words = with;
  } else {
    valid_words = without;
  }
}
words::words() {}
void words::letterInWithPos(char letter, int pos) {
  unordered_set<string> with;
  string curString;
  for (auto it = valid_words.begin(); it != valid_words.end(); it++) {
    // check if the word at the iterator has the letter in right spot       or
    // not
    curString = *it;
    if (curString.find(letter) == pos) {
      with.insert(curString);
    }
  }
  valid_words = with;
}
void words::printWordsLeft() {
  for (auto it = valid_words.begin(); it != valid_words.end(); it++) {
    cout << *it << endl;
  }
}
void words::letterInPosMultiple(vector<int> indicies, char letter) {
    //make sure every word has that letter only in those indicies
    //for each word, findIndicies1 and see if they match with indicies in method
    unordered_set<string> with;
    string curString;
    for (auto it = valid_words.begin(); it != valid_words.end(); it++) {
        curString = *it;
        vector<int> curIndicies = findIndicies1(letter, curString);
        if (curIndicies == indicies) {
            with.insert(curString);
        }
    }
    valid_words = with;
}