#include <iostream> 
#include <String>
#include "tree.h"
#include "helpers.h"
/* to do
    check if code runs properly for inserting 
*/
using namespace std;
int main(){
    //tring out the stuff
    TreeNode* root = makeRoot(12345678, "Jeff");
    root.insert(23456789, "Bob");
    root.insert(10000000, "Wavid");
    root.printPreorder();
    //setup on input parsing
    string input = "";
    while(input!="stop"){
        cout << "Input any command with arguments seperated by spaces. For list of commands, please enter \"help\". Enter \"stop\" to stop";
        cin >> input; 
        if(input == "stop"){
            break;
        }
        if(input == "help"){
            cout << "here are a list of possible commands with their arguements";
            cout << "insert NAME ID" << endl; 
            cout << "remove ID" << endl;
            cout << "search ID" << endl;
            cout << "search NAME" << endl;
            cout << "printInorder" << endl;
            cout << "printPreorder" << endl;
            cout << "printPostorder" << endl;
            cout << "printLevelCount" << endl;
            cout << "removeInorder N" << endl;
            break;
        }
        
    }
    return 0;
}