#include "words.h"
#include <map>
using namespace std;
struct game {
  // variables
  string solution;
  int solSize;
  words w;
  int guesses;
  string wordSoFar;
  bool lettersGuessed[26];
  //which sort is which int is gonna be in comments
  int sortOn;
  int startIndex;
  int endIndex;
  bool evenCase;

  //fns
  //chose your word
  game(string seed);
  //random word
  game();
  void run(bool hard = false);
  bool checkLetter(char letter);
  bool checkWin();
  //unknown number of letters
  game(bool hardmode);
  void init(string seed = "", bool normal = true);
  void printSuggestions();
  void setSortOn(int sort);
  void getSuggestions(vector<string>& suggestedWords, vector<string>& suggestedChars);
};