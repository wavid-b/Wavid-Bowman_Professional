#include "helpers.h"
#include "tree.h"
#include<string>
#include<chrono>
using namespace std;
using namespace std::chrono;
bool inputValid(int _id, string _name){
    if(_id>99999999){
        return false;
    }
    //had to find "find_first_not_of" on the c++ library, have never used it before 
    //checks if there is a character not in that list 
    if(_name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ") != string::npos){
        return false;
    }
    return true;
}
void parseInput() {
    Tree tree;
    string input = "";
    int numRuns = 0;
    getline(cin, input);
    numRuns = stoi(input);
    // auto start = high_resolution_clock::now();
    for (int i = 0; i < numRuns; i++) {
        bool inputEmpty = false;
        getline(cin, input);
        string temp = "";
        if (input.find(" ") != string::npos) {
            int pos = input.find_first_of(" ");
            temp = input.substr(0, pos);
            input = input.substr(pos+1);
        }else{
            temp = input;
            bool inputEmpty = true;
        }
//help - not for final but for me
        /*if (temp == "help") {
            cout << "here are a list of possible commands with their arguements" << endl;
            cout << "insert NAME ID" << endl;
            cout << "remove ID" << endl;
            cout << "search ID" << endl;
            cout << "search NAME" << endl;
            cout << "printInorder" << endl;
            cout << "printPreorder" << endl;
            cout << "printPostorder" << endl;
            cout << "printLevelCount" << endl;
            cout << "removeInorder N" << endl;
            continue;
        }*/
//insert
        if (temp == "insert") {
            //get name
           
            string _name = "";
            //check for if it has the ""
            if (input.find("\"") == string::npos) {
                cout << "unsuccessful" << endl;;
                continue;
            }
            if (input.find_last_of("\"") == string::npos){
                cout << "unsuccessful" << endl;;
                continue;
            }
            if (input.find_first_of("\"") == input.find_last_of("\"")) {
                cout << "unsuccessful" << endl;;
                continue;
            }

            //cut out the name without the ""
            _name = input.substr(input.find("\"")+1, input.find_last_of("\"")-1);
            input = input.substr(input.find_last_of("\"")+1);
            //get number
            //number with space(hopefully)
            if (input.find(" ") != string::npos) {
                int pos = input.find_first_of(" ");
                input = input.substr(pos + 1);
            }
            else {
                cout << "unsuccessful" << endl;;
                continue;
            }
            //validate input
            if (input.find_first_not_of("0123456789")!=string::npos) {
                cout << "unsuccessful" << endl;
                continue;
            }
            if (input.length() != 8) {
                cout << "unsuccessful" << endl;
                continue;
            }
            unsigned int _id = stoi(input);
            if (!inputValid(_id, _name)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            //now actually insert - returns true if it works
            bool success = tree.insert_(_id, _name);
            if (success) {
                cout << "successful" << endl;
                tree.iterate();
            }
            else {
                cout << "unsuccessful" << endl;
            }
            continue;
        }
//remove
        if (temp == "remove") {
            //check if there is an ID with the given number
            if (!inputEmpty) {
                temp = input;
            }
            if (temp.find_first_not_of("0123456789") != string::npos) {
                cout << "unsuccessful" << endl;
                continue;
            }
            unsigned int _id = stoi(temp);
            bool worked = false;
            worked = tree.removeAt_(_id);
            //rebalance to an AVL if needed - O(n)
            if (worked) {
                cout << "successful" << endl;
                continue;
            }
            else {
                cout << "unsuccessful" << endl;
                continue;
            }
        }
//search
        if (temp == "search") {
            //check if its an ID or a Name
            if (!inputEmpty){
                temp = input;
            }
            //name case
            if (temp.find_first_not_of("0123456789") != string::npos) {
                tree.searchName_(temp);
                continue;
            }
            //id case
            else {
                int _id = stoi(temp);
                tree.searchID_(_id);
                continue;
            }
        }
//printInorder
        if (temp == "printInorder") {
            tree.printInorder_();
            continue;
        }
//printPreorder
        if (temp == "printPreorder") {
            tree.printPreorder_();
            continue;
        }
//printPostorder
        if (temp == "printPostorder") {
            tree.printPostorder_();
            continue;
        }
//level count
        if (temp == "printLevelCount") {
            cout << tree.getLevelCount_() << endl;
            continue;
        }
//remove inorder
        if (temp == "removeInorder") {
            if (!inputEmpty) {
                temp = input;
            }
            if (temp.find_first_not_of("0123456789") != string::npos) {
                cout << "unsuccessful" << endl;
                continue;
            }
            unsigned int index = stoi(temp);
            bool worked = false;
            worked = tree.removeInorder(index);
            //reset to an AVL if needed - O(n)
            if (worked) {
                cout << "successful" << endl;
                continue;
            }
            else {
                cout << "unsuccessful" << endl;
                continue;
            }
        }
        cout << "unsuccessful" << endl;
    }
    /*auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "time passed: " << duration.count();*/
}