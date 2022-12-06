#include <unordered_map>
#include <iostream>
#include <string>
#include "Sorting.h"

using namespace std;

//Sorting letters from greatest to least
//0
string CombSort(unordered_map<char, int>& myMap)
{
    int length = myMap.size();
    int gap = length;
    double shrink = 1.3;
    bool sorted = false;
    string word = "";

    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        word.push_back(it->first);
    }

    while (!sorted)
    {
        gap = floor(gap / shrink);
        if (gap <= 1)
        {
            sorted = true;
            gap = 1;
        }
        for (int i = 0; i < length - gap; i++)
        {
            if (myMap[word.at(i)] < myMap[word.at(i + gap)])
            {
                char temp = word.at(i);
                word.at(i) = word.at(i + gap);
                word.at(i + gap) = temp;
                sorted = false;
            }
        }
    }
    return word;
}
//1
string BubbleSort(unordered_map<char, int>& myMap)
{
    int size = myMap.size();
    string word = "";

    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        word.push_back(it->first);
    }

    for (int i = 0; i < size - 1; i++)
    {
        bool swap = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (myMap[word.at(j)] < myMap[word.at(j + 1)])
            {
                char temp = word.at(j);
                word.at(j) = word.at(j+1);
                word.at(j+1) = temp;
                swap = true;
            }
        }
        if (!swap)
        {
            break;
        }
    }
    return word;
}
//2
string SelectionSort(unordered_map<char, int>& myMap)
{
    int size = myMap.size();
    string word = "";

    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        word.push_back(it->first);
    }

    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (myMap[word.at(j)] > myMap[word.at(minIndex)])
            {
                char temp = word.at(j);
                word.at(j) = word.at(minIndex);
                word.at(minIndex) = temp;
            }
        }
    }
    return word;
}
//3
string InsertionSort(unordered_map<char, int>& myMap)
{
    int size = myMap.size();
    string word = "";

    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        word.push_back(it->first);
    }

    for (int i = 1; i < size; i++)
    {
        int keyFrequency = myMap[word.at(i)];
        char keyLetter = word.at(i);
        int j = i - 1;
        while (j>=0 && keyFrequency > myMap[word.at(j)])
        {
            word.at(j + 1) = word.at(j);
            j--;
        }
        word.at(j + 1) = keyLetter;
    }
    return word;
}

int partitionWORD(unordered_map<char, int>& myMap, int low, int high, string& word) {
    int pivot = myMap[word.at((low + high) / 2)];
    int down = high;
    int up = low;
    while (up < down) {
        for (int i = up; i < high; i++) {
            if (myMap[word.at(up)] < pivot) {
                break;
            }
            up++;
        }
        for (int i = high; i > low; i--) {
            if (myMap[word.at(down)] > pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            //how do I do the swapping
            char temp = word.at(up);
            word.at(up) = word.at(down);
            word.at(down) = temp;
        }
    }
    //how do I do the swapping
    char temp = word.at(low);
    word.at(low) = word.at(down);
    word.at(down) = temp;
    return down;
}
void quickSortHelperWORD(unordered_map<char, int>& myMap, int low, int high, string& word) {
    if (low < high) {
        int pivot = partitionWORD(myMap, low, high, word);
        //piv - 1
        quickSortHelperWORD(myMap, low, pivot - 1, word);
        quickSortHelperWORD(myMap, pivot + 1, high, word);
    }
}

string QuickSort(unordered_map<char, int>& myMap)
{
    string word = "";
    int size = myMap.size();
    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        word.push_back(it->first);
    }
    quickSortHelperWORD(myMap, 0, size - 1, word);
    //now word is sorted???

    return word;
}

string MergeSort(unordered_map<char, int>& myMap)
{
    string word = "";
    int size = myMap.size();
    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        word.push_back(it->first);
    }
    mergeSortHelperWORD(myMap, 0, size - 1, word);
    return word;
}

void mergeSortHelperWORD(unordered_map<char, int>& myMap, int left, int right, string& word)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortHelperWORD(myMap, left, mid, word);
        mergeSortHelperWORD(myMap, mid + 1, right, word);

        mergeWORD(myMap, left, mid, right, word);
    }
}

void mergeWORD(unordered_map<char, int>& myMap, int left, int mid, int right, string& word)
{
    int size1 = mid - left + 1;
    int size2 = right - mid;

    string x(size1, ' ');
    string y(size2, ' ');

    for (int i = 0; i < size1; i++)
    {
        x.at(i) = word.at(left + i);
    }
    for (int j = 0; j < size2; j++)
    {
        y.at(j) = word.at(mid + 1 + j);
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < size1 && j < size2)
    {
        if (myMap[x.at(i)] >= myMap[y.at(j)])
        {
            word.at(k) = x.at(i);
            i++;
        }
        else
        {
            word.at(k) = y.at(j);
            j++;
        }
        k++;
    }

    while (i < size1)
    {
        word.at(k) = x.at(i);
        i++;
        k++;
    }

    while (j < size2)
    {
        word.at(k) = y.at(j);
        j++;
        k++;
    }
}


//Sorting words from greatest to least
vector<string> CombSort(unordered_map<string, int>& myMap)
{
    int length = myMap.size();
    int gap = length;
    double shrink = 1.3;
    bool sorted = false;
    vector<string> words;

    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        words.push_back(it->first);
    }

    while (!sorted)
    {
        gap = floor(gap / shrink);
        if (gap <= 1)
        {
            sorted = true;
            gap = 1;
        }
        for (int i = 0; i < length - gap; i++)
        {
            if (myMap[words[i]] < myMap[words[i+gap]])
            {
                string temp = words[i];
                words[i] = words[i + gap];
                words[i + gap] = temp;
                sorted = false;
            }
        }
    }
    return words;
}

vector<string> BubbleSort(unordered_map<string, int>& myMap)
{
    vector<string> words;
    int size = myMap.size();

    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        words.push_back(it->first);
    }

    for (int i = 0; i < size - 1; i++)
    {
        bool swap = false;
        for (int j = 0; j < size - i - 1; j++)
        {
            if (myMap[words[j]] < myMap[words[j+1]])
            {
                string temp = words[j];
                words[j] = words[j + 1];
                words[j+1] = temp;
                swap = true;
            }
        }
        if (!swap)
        {
            break;
        }
    }
    return words;
}

vector<string> SelectionSort(unordered_map<string, int>& myMap)
{
    vector<string> words;
    int size = myMap.size();

    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        words.push_back(it->first);
    }

    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (myMap[words[j]] > myMap[words[minIndex]])
            {
                string temp = words[j];
                words[j] = words[minIndex];
                words[minIndex] = temp;
            }
        }
    }
    return words;
}

vector<string> InsertionSort(unordered_map<string, int>& myMap)
{
    vector<string> words;
    int size = myMap.size();

    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        words.push_back(it->first);
    }

    for (int i = 1; i < size; i++)
    {
        int keyFrequency = myMap[words[i]];
        string keyWord = words[i];
        int j = i - 1;
        while (j >= 0 && keyFrequency > myMap[words[j]])
        {
            words[j+1]= words[j];
            j--;
        }
        words[j+1] = keyWord;
    }
    return words;
}

int partitionVECTOR(unordered_map<string, int>& myMap, int low, int high, vector<string>& words) {
    int pivot = myMap[words[(low + high) / 2]];
    int down = high;
    int up = low;
    while (up < down) {
        for (int i = up; i < high; i++) {
            if (myMap[words[up]] < pivot) {
                break;
            }
            up++;
        }
        for (int i = high; i > low; i--) {
            if (myMap[words[down]] > pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            //how do I do the swapping
            string temp = words[up];
            words[up] = words[down];
            words[down] = temp;
        }
    }
    //how do I do the swapping
    string temp = words[low];
    words[low] = words[down];
    words[down] = temp;
    return down;
}

void quickSortHelperVECTOR(unordered_map<string, int>& myMap, int low, int high, vector<string>& words) {
    if (low < high) {
        int pivot = partitionVECTOR(myMap, low, high, words);
        //piv - 1
        quickSortHelperVECTOR(myMap, low, pivot - 1, words);
        quickSortHelperVECTOR(myMap, pivot + 1, high, words);
    }

}

vector<string> QuickSort(unordered_map<string, int>& myMap)
{
    vector<string> words;
    int size = myMap.size();
    int count = 0;
    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        words.push_back(it->first);
    }
    //quickSortHelperVECTOR(myMap, 0, size - 1, words);
    quickSortHelperVECTOR(myMap, 0, size - 1, words);
    return words;
}

vector<string> MergeSort(unordered_map<string, int>& myMap)
{
    vector<string> words;
    int size = myMap.size();
    for (auto it = myMap.begin(); it != myMap.end(); it++)
    {
        words.push_back(it->first);
    }
    mergeSortHelperVECTOR(myMap, 0, size - 1, words);

    return words;
}

void mergeSortHelperVECTOR(unordered_map<string, int>& myMap, int left, int right, vector<string>& words)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortHelperVECTOR(myMap, left, mid, words);
        mergeSortHelperVECTOR(myMap, mid + 1, right, words);

        mergeVECTOR(myMap, left, mid, right, words);
    }
}

void mergeVECTOR(unordered_map<string, int>& myMap, int left, int mid, int right, vector<string>& words)
{
    int size1 = mid - left + 1;
    int size2 = right - mid;

    vector<string> x(size1, "");
    vector<string> y(size2, "");

    for (int i = 0; i < size1; i++)
    {
        x[i] = words[left + i];
    }
    for (int j = 0; j < size2; j++)
    {
        y[j] = words[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while (i < size1 && j < size2)
    {
        if (myMap[x[i]] >= myMap[y[j]])
        {
            words[k] = x[i];
            i++;
        }
        else
        {
            words[k] = y[j];
            j++;
        }
        k++;
    }

    while (i < size1)
    {
        words[k] = x[i];
        i++;
        k++;
    }

    while (j < size2)
    {
        words[k] = y[j];
        j++;
        k++;
    }
}
