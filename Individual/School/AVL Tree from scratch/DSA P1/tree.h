#pragma once
#include <iostream>
#include <string>

using namespace std;
class Tree {
    struct TreeNode {
        //variables
        int balance;
        unsigned int id;
        string name;
        TreeNode* left;
        TreeNode* right;
        //constructor/deconstructor
        TreeNode(TreeNode* root = nullptr);
        ~TreeNode();
        void destroyTree();
        //helpers
        TreeNode* getParent(TreeNode* _child, TreeNode* _root);
        void printId();
        //search
        void searchName(string _name, bool& atLeastOne);
        string searchID(unsigned int identifier, string out = "unsuccessful");
        //balancing stuff
        TreeNode* rotateLeft(TreeNode* _parent = nullptr, bool fromRight = false);
        TreeNode* rotateRight(TreeNode* _parent = nullptr, bool fromRight = false);
        TreeNode* checkBalance(TreeNode* _root, TreeNode* _lastRoot = nullptr, bool local = false) ;
        void setBalance(bool local = false); 
        //insert
        TreeNode* insert(TreeNode* _root, unsigned int num, string n, bool& worked);
        //level count
        unsigned int getLevelCount();
        //recursive prints
        void printPreorder();
        void printPostorder();
        void printInorder(unsigned int& _count);
        //deletion 
        TreeNode* removeAt(unsigned int _id, bool& worked, TreeNode* parent = nullptr);
            //cant use delete
        TreeNode* erase(TreeNode* parent = nullptr);
        //TreeNode* eraseNext();
        Tree::TreeNode* traverseInorder(unsigned int &index, TreeNode* &output);
    };
    TreeNode* root;
    unsigned int count;
public:
    //getter & setter
    TreeNode* getRoot();
    void setRoot(TreeNode* _root);
    void setCount(int c);
    int getCount();
    //other fns
    void iterate();
    //balancing
    void checkBalance_();
    //searching
    void searchName_(string _name);
    void searchID_(unsigned int _id);
    //insert
    bool insert_(unsigned int num, string n);
    //level count
    unsigned int getLevelCount_();
    //printing 
    void printPreorder_();
    void printPostorder_();
    void printInorder_();
    //deleting
    bool removeAt_(unsigned int _id);
    bool removeInorder(unsigned int index);
    //constructor/destructor
    Tree();
    ~Tree();




};

