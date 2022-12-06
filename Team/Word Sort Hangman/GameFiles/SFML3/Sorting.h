#pragma once
#include <unordered_map>
#include <string>

using namespace std;

//Sorting letters from greatest to least
string CombSort(unordered_map<char, int> myMap);
string BubbleSort(unordered_map<char, int> myMap);
string SelectionSort(unordered_map<char, int> myMap);
string InsertionSort(unordered_map<char, int> myMap);
string QuickSort(unordered_map<char, int> myMap);
void quickSortHelperWORD(unordered_map<char, int> myMap, int low, int high, string& word);
int partitionWORD(unordered_map<char, int> myMap, int low, int high, string& word);
string MergeSort(unordered_map<char, int> myMap);
void mergeSortHelperWORD(unordered_map<char, int> myMap, int left, int right, string& word);
void mergeWORD(unordered_map<char, int> myMap, int left, int mid, int right, string& word);
 

//Sorting words from greatest to least
vector<string> CombSort(unordered_map<string, int> myMap);
vector<string> BubbleSort(unordered_map<string, int> myMap);
vector<string> SelectionSort(unordered_map<string, int> myMap);
vector<string> InsertionSort(unordered_map<string, int> myMap);
vector<string> QuickSort(unordered_map<string, int> myMap);
void quickSortHelperVECTOR(unordered_map<string, int> myMap, int low, int high, vector<string>& words);
int partitionVECTOR(unordered_map<string, int> myMap, int low, int high, vector<string>& words);
vector<string> MergeSort(unordered_map<string, int> myMap);
void mergeSortHelperVECTOR(unordered_map<string, int> myMap, int left, int right, vector<string>& words);
void mergeVECTOR(unordered_map<string, int> myMap, int left, int mid, int right, vector<string>& words);