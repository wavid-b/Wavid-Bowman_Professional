#include "helpers.h"
#include "tree.h"
//for recursive fns, FN is called by the tree function named FN_
//destructor

Tree::~Tree() {
    root->destroyTree();
}
Tree::TreeNode::~TreeNode() {
    
}
void Tree::TreeNode::destroyTree() {
    //do a post order traversal and destroy each one

    if (right != nullptr) {
        right->destroyTree();
    }
    if (left != nullptr) {
        left->destroyTree();
    }
    delete this;
}
//constructors

Tree::Tree() {
    root = nullptr;
    count = 0;
}
Tree::TreeNode::TreeNode(TreeNode* root){
    name = "";
    id = 0;
    balance = 0;
    left = nullptr; 
    right = nullptr;
}
//balancing tree
void Tree::TreeNode::setBalance(bool local) {
    //sets balanced based on the fact that balance should be obtainable iff level(right) and level(left) are within 1 of each other
    unsigned int leftLvl = 0;
    unsigned int rightLvl = 0;
    //do recursively so everyone's balance is the same
    if (left != nullptr) {
        leftLvl = left->getLevelCount();
        if (!local) {
            left->setBalance();
        }
    }
    if (right != nullptr) {
        rightLvl = right->getLevelCount();
        if (!local) {
            right->setBalance();
        }
    }
    balance = rightLvl - leftLvl;
}

//rotating tree to make it better balanced
Tree::TreeNode* Tree::TreeNode::rotateLeft(TreeNode* _parent, bool fromRight) {
    //returns ptr to next node in this spot - from ppt
    TreeNode* grandchild = this->right->left;
    TreeNode* newParent = this->right;
    newParent->left = this;
    this->right = grandchild;
    //now make old stuff point to new parent
    if (_parent != nullptr) {
        if (fromRight) {
            _parent->left = newParent;
        }
        else {
            _parent->right = newParent;
        }
    }
    return newParent;
}
Tree::TreeNode* Tree::TreeNode::rotateRight(TreeNode* _parent, bool fromRight) {
    //returns ptr to next node in this spot
    TreeNode* grandchild = this->left->right;
    TreeNode* newParent = this->left;
    newParent->right = this;
    this->left = grandchild;
    //now make old stuff point to new parent
    if (_parent != nullptr) {
        if (fromRight) {
            _parent->left = newParent;
        }
        else {
            _parent->right = newParent;
        }
    }
    return newParent;
}
void Tree::checkBalance_() {
    if(root!=nullptr){
        root->setBalance();
        root = root->checkBalance(root);
        root->setBalance();
    }

}
Tree::TreeNode* Tree::TreeNode::checkBalance(TreeNode* _root, TreeNode* _lastRoot, bool local) {
    //post-order traversal of checking balance
    if (!local) {
        if (_root->left != nullptr) {
            _root->setBalance();
            _root->left->checkBalance(_root->left, _root);
        }
        if (_root->right != nullptr) {
            _root->setBalance();
            _root->right->checkBalance(_root->right, _root);
        }
    }
    
    //what to do when unbalanced - much influence from ppt 4 slides 11-20
    //too much on the right side
    if (_root->balance > 1) {
        //make sure that it is actually not balanced
        _root->setBalance();
        if (_root->balance > 1) {
            //check cases
            TreeNode* child = _root->right;
            if (child != nullptr) {
                //check for right right vs right left case
                    //set balance to be correct before you check
                child->setBalance();
                if (child->balance == 1) {
                    //right right case
                    _root = _root->rotateLeft(_lastRoot);

                }
                else if (child->balance == -1) {
                    //right left case
                    child = child->rotateRight(_root);
                    _root = _root->rotateLeft(_lastRoot);
                }
                //now reset the balances & parents to be correct
                _root->setBalance();
            }
            else {
                cout << "something is wrong with balances" << endl;
            }
        }
    }
    //other 2 cases
    if (_root->balance < -1) {
        //make sure it really is unbalanced
        _root->setBalance();
        if (_root->balance < -1) {
            TreeNode* child = _root->left;
            if (child != nullptr) {
                child->setBalance();
                if (child->balance == -1) {
                    //left left case
                    _root = _root->rotateRight(_lastRoot, true);
                }
                else if (child->balance == 1) {
                    //left right case
                    child = child->rotateLeft(_root, true);
                    _root = _root->rotateRight(_lastRoot, true);
                }
                //now reset the balances & parents to be correct
                _root->setBalance();

            }
            else {
                cout << "something is wrong with balances" << endl;
            }
        }
    }
    return _root;
}
//getters/setters

Tree::TreeNode* Tree::getRoot() {
    return root;
}
void Tree::setRoot(Tree::TreeNode* _root) {
    root = _root;
}
void Tree::setCount(int c) {
    count = c;
}
int Tree::getCount() {
    return count;
}
//helpers inside tree
Tree::TreeNode* Tree::TreeNode::getParent(TreeNode* _child, TreeNode* _root) {
    //find the parent of the child
        //go right
    if (_child->id > _root->id && _root->right != nullptr) {
        if (_root->right != _child) {
            _root = _root->getParent(_child, _root->right);
        }
    }
    if (_child->id < _root->id && _root->left != nullptr) {
        if (_root->left != _child) {
            _root = _root->getParent(_child, _root->left);
        }
    }
    if (_root == _child) {
        return nullptr;
    }
    return _root;
}
void Tree::iterate() {
    count++;
}
void Tree::TreeNode::printId() {
    //prints id with correct number of 0's
    if (id < 10) {
        cout << "0000000" << id;
    }
    else if (id < 100) {
        cout << "000000" << id;
    }
    else if (id < 1000) {
        cout << "00000" << id;
    }
    else if (id < 10000) {
        cout << "0000" << id;
    }
    else if (id < 100000) {
        cout << "000" << id;
    }
    else if (id < 1000000) {
        cout << "00" << id;
    }
    else if (id < 10000000) {
        cout << "0" << id;
    }
    else {
        cout << id;
    }
    cout << endl;
}
//searching

string Tree::TreeNode::searchID(unsigned int _id, string output){
    //this is working for insert, but not for search and not sure why
    //check the tree for node with id 
    //left side if greater, right side if lesser 

    if(left!=nullptr&&_id<id){
        output = left->searchID(_id, output);
    }
    if(right!=nullptr&&_id>id){
        output = right->searchID(_id, output);
    }
    if(id == _id){
        output = name;
    }
    //it finished root last, so when it does root, cout the stuff
    
    return output; 

}
void Tree::searchID_(unsigned int _id) {
    string output = "unsuccessful";
    if (root != nullptr) {
        output = root->searchID(_id);
    }
    cout << output << endl;
}
void Tree::TreeNode::searchName(string _name, bool &atLeastOne) {
    //print each match in pre-order transversal order
    if (name == _name) {
        printId();
        atLeastOne = true;
    }
    if (left != nullptr) {
        left->searchName(_name, atLeastOne);
    }
    if (right != nullptr) {
        right->searchName(_name, atLeastOne);
    }
    return;
}
void Tree::searchName_(string _name) {
    bool output = false;
    //check if _name has the "" how it is supposed to 
    if (_name.find("\"") == string::npos ||
        _name.find_first_of("\"") == _name.find_last_of("\"")) {
        cout << "unsuccessful" << endl;;
        return;
    }
    //cut out the "" for comparison
    _name = _name.substr(_name.find("\"") + 1, _name.find_last_of("\"") - 1);
    if (root != nullptr) {
        root->searchName(_name, output);
    }
    if (!output) {
        cout << "unsuccessful" << endl;
    }
}
//insertion

Tree::TreeNode* Tree::TreeNode::insert(TreeNode* _root, unsigned int _id, string _name,  bool &worked){
    //validate input

    //check if you have an input root 
    if(_root == nullptr){
        TreeNode* temp = new TreeNode;
        temp->name = _name;
        temp->id = _id;
        worked = true;
        return temp;
    }
    //check if num is already a student ID number
    if(_root->searchID(_id)!="unsuccessful"){
        return _root;
    }
    //if not, you put it in the correct spot
    //augmented insert code from trees ppt - 4th input allows us to track if something was inserted
    if (_id < _root->id){
        _root->left = insert(_root->left, _id, _name, worked);
        _root->balance--;
        //check balance locally (not recursive process)
        _root->left = _root->left->checkBalance(_root->left, _root, true);
    }
    else{
        _root->right = insert(_root->right, _id, _name, worked);
        _root->balance++;
        _root->right = _root->right->checkBalance(_root->right, _root, true);
    }
    _root = _root->checkBalance(_root, nullptr, true);
    return _root;
}
bool Tree::insert_(unsigned int _id, string _name) {
    //calls the helper fn inside the node class and returns if sucessful or not
    bool worked = false;
    root = root->insert(root, _id, _name, worked);
    return worked;
}
//level count

unsigned int Tree::TreeNode::getLevelCount() {
    //if left and right are both null, return 1
    unsigned int rightLevel = 0;
    unsigned int leftLevel = 0;
    if (right != nullptr) {
        rightLevel = right->getLevelCount();
    }
    if (left != nullptr) {
        leftLevel = left->getLevelCount();
    }
    //otherwise, return the higher of left and right
    if (rightLevel > leftLevel) {
        return rightLevel + 1;
    }
    else {
        return leftLevel + 1;
    }
}
unsigned int Tree::getLevelCount_() {
    if (root == nullptr) {
        return 0;
    }
    return root->getLevelCount();
}
//printers

void Tree::TreeNode::printPreorder() {
    cout << name;
    if (left != nullptr) {
        cout << ", ";
        left->printPreorder();
    }
    if (right != nullptr) {
        cout << ", ";
        right->printPreorder();
    }
}
void Tree::printPreorder_() {
    //empty tree edge case
    if (root == nullptr) {
        cout << endl;
        return;
    }
    root->printPreorder();
    cout << endl;
}
void Tree::TreeNode::printPostorder() {
    if (left != nullptr) {
        left->printPostorder();
        cout << ", ";
    }
    if (right != nullptr) {
        right->printPostorder();
        cout << ", ";
    }
    cout << name;
}
void Tree::printPostorder_() {
    //empty tree edge case
    if (root == nullptr) {
        cout << endl;
        return;
    }
    root->printPostorder();
    cout << endl;
}
void Tree::TreeNode::printInorder(unsigned int &_count) {
    //causing issues, so using the count variable to make it work better 
    if (left != nullptr) {
        left->printInorder(_count);
    }
    //fix this logic
    if (_count != 1) {
        cout << name << ", ";
        _count--;

    }
    else {
        cout << name;
    }
    if (right != nullptr) {
        right->printInorder(_count);
    }
}
void Tree::printInorder_() {
    //empty tree edge case
    if (root == nullptr) {
        cout << endl;
        return;
    }
    unsigned int countCopy = count;
    root->printInorder(countCopy);
    cout << endl;
}
//deletion

Tree::TreeNode* Tree::TreeNode::removeAt(unsigned int _id, bool& worked, TreeNode* parent) {
    //call erase to delete things, its the deletion fn I made
    TreeNode* output = this;
    if (left != nullptr && _id < id) {
        left = left->removeAt(_id, worked, this);
    }
    if (right != nullptr && _id > id) {
        right = right->removeAt(_id, worked, this);
    }
    if (_id == id) {
        worked = true;
        output = erase(parent);
    }
    return output;
}
/*Tree::TreeNode* Tree::TreeNode::eraseNext() {
    //effectively, call erase with this as parent on next

}*/
Tree::TreeNode* Tree::TreeNode::erase(TreeNode* parent){
    //3 cases - no children, 1 child, 2 children
    //no children -> parent points to null now
    if (left == nullptr && right == nullptr) {
        if (parent != nullptr) {
            //check which child I am
            if (parent->left == this) {
                parent->left = nullptr;
                delete this;
                return nullptr;
            }
            else {
                parent->right = nullptr;
                delete this;
                return nullptr;
            }
        }
        else {
            delete this;
            return nullptr;
        }
    // 1 child -> parent points to child now
    }else if(left == nullptr && right != nullptr) {
        //right child case
        if (parent != nullptr) {
            //check which child I am
            if (parent->left == this) {
                parent->left = right;
                delete this;
                return parent->left;
            }
            else {
                parent->right = right;
                delete this;
                return parent->right;

            }
        }
        else {
            TreeNode* temp = right;
            delete this; 
            return temp;
        }
        //left child case
    }else if (left != nullptr && right == nullptr) {
        if (parent != nullptr) {
            //check which child I am
            if (parent->left == this) {
                parent->left = left;
                delete this;
                return parent->left;
            }
            else {
                parent->right = left;
                delete this;
                return parent->right;
            }
        }
        else {
            TreeNode* temp = left;
            delete this;
            return temp;
        }
    }
    // 2 children -> change value of node to inorder successor 
    else if (left != nullptr && right != nullptr) {
        //find inorder successor
        TreeNode* temp = right;
        TreeNode* tempParent = this;
        //first pass seperately because need to store parent
        if (right->left != nullptr) {
            temp = temp->left;
            tempParent = tempParent->right;
        }
            //leftmost member of right subtree
        while (temp->left != nullptr) {
            temp = temp->left;
            tempParent = temp->left;
        }
        this->id = temp->id;
        this->name = temp->name;
        // then delete successor
        temp = temp->erase(tempParent);
        return this;
    }
    return this;
}
bool Tree::removeAt_(unsigned int _id) {
    bool worked = false;
    root = root->removeAt(_id, worked);
    checkBalance_();
    if (worked) {
        count--;
    }
    return worked;
}
Tree::TreeNode* Tree::TreeNode::traverseInorder(unsigned int &index, TreeNode* &output) {
    if (left != nullptr) {
        left->traverseInorder(index, output);
    }
    if (index == 0) {
        output = this;
    }
    else {
        index--;
    }
    if (right != nullptr && output == nullptr) {
        right->traverseInorder(index, output);
    }
    return output;
}
bool Tree::removeInorder(unsigned int index) {
    if (index >= count) {
        return false;
    }
    else {
        //traverse tree inorder (index) times, then erase that node
        TreeNode* temp = nullptr;
        TreeNode* toRemove = root->traverseInorder(index, temp);
        //trouble getting it to work other ways, so just save the ID and removeAt the id
        unsigned int idToRemove = toRemove->id;
        bool worked = removeAt_(idToRemove);
        if (worked) {
            return true;
        }
        else {
            return false;
        }
    }
}