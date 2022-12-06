#include "game.h"
#include "FrequencyCalculator.h"
#include "Sorting.h"
#include <cstdlib>
#include <iostream>
using namespace std;
vector<int> findIndicies(char guess, string solution, bool& found) {
	vector<int> output;
	string g = "";
	g += guess;
	for (int i = 0; i < solution.length(); i++) {
		if (solution.substr(i, g.length()) == g) {
			output.push_back(i);
			found = true;
		}
	}
	return output;
}

void game::init(string seed, bool normal) {
	// chose a random word to use as solution
	w.makeSets();
	if (seed == "") {
		srand(time(0));
		int index = rand() % (w.valid_words.size() - 1);
		//cout << "random int is: " << index << endl;
		auto it = w.valid_words.begin();
		for (int i = 0; i < index; i++) {
			it++;
		}
		solution = *it;
		solSize = solution.size();
		if (normal) {
			w.numOfLetters(solSize);
		}
	}
	else {
		solution = seed;
		solSize = solution.size();
		
	}

	guesses = 0;
	wordSoFar = "";
	sortOn = 0;
	for (int i = 0; i < solSize; i++) {
		wordSoFar += "_";
	}
	// initialize your boolean
	for (int i = 0; i < 26; i++) {
		lettersGuessed[i] = false;
	}
	if (solSize % 2 == 0) {
		evenCase = true;
		startIndex = (10 - solSize) / 2;
		endIndex = startIndex + solSize - 1;
	}
	else {
		startIndex = (9 - solSize) / 2;
		endIndex = startIndex + solSize - 1;
		evenCase = false;
	}
//	cout << "word: " << solution << endl;
}
game::game() { init(); }
game::game(string seed) { init(seed); }
void game::run(bool hard) {
	//if on hardMode
	if (hard) {
		while (guesses < 9) {
			bool say = true;
			
			if (say) {
				cout << "You do not get word length" << endl;
				cout << "You have used " << guesses
					<< " incorrect guesses so far out of 8" << endl;
				cout << "You do not get a word so far" << endl;
				cout << "You have guessed the letter(s): ";
				for (int i = 0; i < 26; i++) {
					if (lettersGuessed[i]) {
						// output the letters that has been guessed 
						cout << char(i + 97) << " ";
					}
				}
				cout << endl;
				printSuggestions();
				cout << "Enter your letter guess in lowercase" << endl;
				say = false;
			}
			char guess;
			cin >> guess;
			int guessInt = int(guess);
			// check if lower case character or no
			if (guessInt > 122 || guessInt < 97) {
				cout << "Please enter a letter in lowercase";
				continue;
			}
			guessInt -= 97;
			lettersGuessed[guessInt] = true;
			// check if the letter is in the solution word -> make helper fn
			bool found = false;
			// thing for finding words
			vector<int> indicies = findIndicies(guess, solution, found);
			for (int i = 0; i < indicies.size(); i++) {
				wordSoFar[indicies[i]] = guess;
				//w.letterInWithPos(guess, indicies[i]);
			}
			w.letterInPosMultiple(indicies, guess);
			// whether found if block
			if (found) {
				cout << "hit!" << endl;
			}
			else {
				cout << "miss!" << endl;
				w.letterInput(guess);
				guesses++;
			}
			//check if they won
			if (wordSoFar.find('_') == string::npos) {
				// do won the game stuff
				cout << "word: " << solution << endl << "you won!";
				return;
			}
			say = true;
		}
		cout << "You lose. Maybe try easy mode next time.";

	}
	//what to do normally
	else {
		bool say = true;
		while (guesses < 9) {
			if (say) {
				cout << "Word length: " << solSize << endl;
				cout << "You have used " << guesses
					<< " incorrect guesses so far out of 8" << endl;
				cout << "Your word so far: " << wordSoFar << endl;
				cout << "You have guessed the letter(s): ";
				for (int i = 0; i < 26; i++) {
					if (lettersGuessed[i]) {
						// output the letters that has been guessed
						cout << char(i + 97) << " ";
					}
				}
				cout << endl;
				printSuggestions();
				cout << "Enter your letter guess in lowercase" << endl;
				say = false;
			}
			//suggestions section
			char guess;
			cin >> guess;
			int guessInt = int(guess);
			// check if lower case character or no
			if (guessInt > 122 || guessInt < 97) {
				cout << "Please enter a letter in lowercase";
				continue;
			}
			guessInt -= 97;
			lettersGuessed[guessInt] = true;
			// check if the letter is in the solution word
			bool found = false;
			// thing for finding words
			vector<int> indicies = findIndicies(guess, solution, found);
			//for each index, set that letter to it in wordSoFar
			for (int i = 0; i < indicies.size(); i++) {
				wordSoFar[indicies[i]] = guess;
				//w.letterInWithPos(guess, indicies[i]);
			}
			//no other letter spots can be that anymore
			w.letterInPosMultiple(indicies, guess);
			// whether found if block
			if (found) {
				cout << "hit!" << endl;
			}
			else {
				cout << "miss!" << endl;
				w.letterInput(guess);
				guesses++;
			}
			// check if they won the game
			if (wordSoFar.find('_') == string::npos) {
				// do won the game stuff
				cout << "word: " << solution << endl << "you won!";
				return;
			}
			say = true;
		}
		// only runs if they lose
		cout << "You lose :(";
	}
}
void game::printSuggestions() {
	//frequency calculation
	unordered_map<char, int> let_freq = letterFrequency(w.valid_words);
	unordered_map<string, int> word_freq = wordFrequency(w.valid_words, let_freq);
	//remove the confirmed letters from the recommended
	for (int i = 0; i < 26; i++) {
		if (lettersGuessed[i]) {
			//remove that letter from let_freq
			let_freq.erase(char(i + 97));
		}
	}
	//sort these now - choose based on what sort is on -> buttons will change that variable

	string sortedLetters;
	vector<string> sortedWords;
	switch (sortOn) {
		//bubble
	case 1:
		sortedLetters = BubbleSort(let_freq);
		sortedWords = BubbleSort(word_freq);

		//selection
	case 2:
		sortedLetters = SelectionSort(let_freq);
		sortedWords = SelectionSort(word_freq);
		//insertion
	case 3:
		sortedLetters = InsertionSort(let_freq);
		sortedWords = InsertionSort(word_freq);
		//comb
	case 4: 
		sortedLetters = QuickSort(let_freq);
		sortedWords = QuickSort(word_freq);
		//quick
	case 5:
		sortedLetters = MergeSort(let_freq);
		sortedWords = MergeSort(word_freq);
		//merge
	default:
		sortedLetters = QuickSort(let_freq);
		sortedWords = QuickSort(word_freq);
	}
	//after sorting, give the top 5 letters and words along with their frequencies
	cout << "Recommended letters: " << endl;
	for (int i = 0; i < 5; i++) {
		if (let_freq.size() > i) {
			cout << sortedLetters[i] << ": " << let_freq[sortedLetters[i]] << endl;
		}

		//top letter and frequency 
	}
	cout << "Recommneded Words: " << endl;
	for (int i = 0; i < 5; i++) {
		if (sortedWords.size() > i) {
			cout << sortedWords[i] << ": " << word_freq[sortedWords[i]] << endl;
		}
		//top letter and frequency 
	}
}
void game::setSortOn(int sort) {
	sortOn = sort;
}
game::game(bool hardMode) {
	if (hardMode) {
		//chose a random word, but dont tell how many letters it is
		//you no longer get a wordSoFar
		init("", false);
	}
	else {
		init();
	}
}
bool game::checkLetter(char letter) {
	bool found = false;
	// thing for finding words
	int guessInt = (int)letter;
	guessInt -= 97;
	lettersGuessed[guessInt] = true;
	vector<int> indicies = findIndicies(letter, solution, found);
	for (int i = 0; i < indicies.size(); i++) {
		wordSoFar[indicies[i]] = letter;
		//w.letterInWithPos(guess, indicies[i]);
	}
	w.letterInPosMultiple(indicies, letter);
	if (!found) {
		guesses++;
	}
	return found;
}
bool game::checkWin() {
	if (wordSoFar.find('_') == string::npos) {
		// do won the game stuff
		return true;
	}
	return false;
}
void game::getSuggestions(vector<string>& suggestedWords, vector<string>& suggestedChars){

	unordered_map<char, int> let_freq = letterFrequency(w.valid_words);
	unordered_map<string, int> word_freq = wordFrequency(w.valid_words, let_freq);
	//remove the confirmed letters from the recommended
	for (int i = 0; i < 26; i++) {
		if (lettersGuessed[i]) {
			//remove that letter from let_freq
			let_freq.erase(char(i + 97));
		}
	}
	//sort these now - choose based on what sort is on -> buttons will change that variable
	
	string sortedLetters;
	vector<string> sortedWords;
	switch (sortOn) {
		//bubble
	case 1:
		sortedLetters = BubbleSort(let_freq);
		sortedWords = BubbleSort(word_freq);
		break;
		//selection
	case 2:
		sortedLetters = SelectionSort(let_freq);
		sortedWords = SelectionSort(word_freq);
		break;
		//insertion
	case 3:
		sortedLetters = InsertionSort(let_freq);
		sortedWords = InsertionSort(word_freq);
		break;
		//quick
	case 4:
		sortedLetters = QuickSort(let_freq);
		sortedWords = QuickSort(word_freq);
		break;
		//comb
	case 5:
		sortedLetters = MergeSort(let_freq);
		sortedWords = MergeSort(word_freq);
		break;
		//merge
	default:
		sortedLetters = CombSort(let_freq);
		sortedWords = CombSort(word_freq);
		break;
	}
	//now add that shit to the two output vectors
	for (int i = 0; i < 5; i++) {
		if (let_freq.size() > i) {
			string letter = "";
			letter += sortedLetters.at(i);
			suggestedChars.push_back(letter);
		}
		if (word_freq.size() > i) {
			suggestedWords.push_back(sortedWords[i]);
		}
	}

}