#include "Wad.h"
#include <iostream>
#include <cstring>
using namespace std;
void fixChildren(Dir* root);
bool checkMapDir(string name);
string makeDirString(const vector<Dir*>& nestedDirectories){
    string dirString = "";
    for(int i = 0; i<nestedDirectories.size(); i++){
        dirString += nestedDirectories[i]->name;
        if(i != nestedDirectories.size()-1){
            dirString += "/";
        }
    }
    return dirString;
}
Wad* Wad::loadWad(const string& path){
    return new Wad(path);
}
Wad::Wad(string path){
    //remove any of the old stuff
    pathMap = unordered_map<string, FileEntity*>();
    fileNames = vector<string>();

    //grab the stuff from the file at that path location
    actualyFilePath = path;
    root = Dir("", "/", 0, 0);
    ifstream file(path);
    if(!file.is_open()){
        throw "File not found at " + path + ". ";
    }
    pathMap.insert({"/", &root});
    char buffer[4];
    char stringBuffer[9];
    file.read(buffer, 4);
    magic = string(buffer, 4);
    file.read(buffer, 4);
        //casting then dereferencing
    numDescriptors = *(unsigned*)buffer;
    file.read(buffer, 4);
    descriptorOffset = *(unsigned*)buffer;
    //ok now that we have the descriptor offset and the number of descriptors, we read in those files
    file.seekg(descriptorOffset);
   //iterate and accept the stuff
    vector<Dir*> nestedDirectories;
    nestedDirectories.push_back(&root);
    for(int i = 0; i<numDescriptors; i++){
        //element offset
        file.read(buffer, 4);
        unsigned elementOffset = *(unsigned*)buffer;
        //element size
        file.read(buffer, 4);
        unsigned elementSize = *(unsigned*)buffer;
        //name
        file.read(stringBuffer, 8);
        stringBuffer[8] = '\0';
        string name = string(stringBuffer);
        //parse if name is a directory or a file
        
        //add the filename to the list -- this is for knowing where to add new dir or file obj
        fileNames.push_back(name);
        if(name.size() >= 7 && (name.substr(2) == "_START" || name.substr(1) == "_START")){
            //namespace_directory opening
            //create the new directory as a child of the last directory in the nestedDirectories vector
            name = name.substr(0, name.find('_'));
            Namespace_Dir* temp = new Namespace_Dir(name, makeDirString(nestedDirectories) + "/" + name, elementOffset, elementSize, nestedDirectories[nestedDirectories.size()-1]);
            //add it to the last directory in the nestedDirectories vector
            nestedDirectories[nestedDirectories.size()-1]->children.push_back(temp);
            //make the new directory the last directory in the nestedDirectories vector

            //last child of it

            nestedDirectories.push_back(temp);
            pathMap.insert({temp->path, temp});
            paths.push_back(temp->path);
        }
        else if(name.size() >= 5 && (name.substr(2) == "_END" || name.substr(1) == "_END")){
            //namespace_directory closing
            //set end offset of the last directory in the nestedDirectories vector
            string currentPath = makeDirString(nestedDirectories);
            
            if(isDirectory(currentPath)){
                Dir* temp = dynamic_cast<Dir*>(pathMap[makeDirString(nestedDirectories)]);
                temp->endIndex = i;
            }
            nestedDirectories.pop_back();
        }
            //make this more robust
        else if(checkMapDir(name)){
            //map_dir
            Map_Dir* temp = new Map_Dir(name, makeDirString(nestedDirectories) + "/" + name, elementOffset, elementSize, nestedDirectories[nestedDirectories.size()-1]);
                //add it to the last directory in the nestedDirectories vector  
            
            nestedDirectories[nestedDirectories.size()-1]->children.push_back(temp);
            //make the new directory the last directory in the nestedDirectories vector
                
                //last child of it
            
            nestedDirectories.push_back(temp);
            pathMap.insert({temp->path, temp});
            paths.push_back(temp->path);

        }else{
            //file
            //go grab the contents
            ifstream getContent(path);
            getContent.seekg(elementOffset);
            char* content = new char[elementSize];
            getContent.read(content, elementSize);
                //make it and pop if its the last element for a map_dir
            File* temp = new File(name, makeDirString(nestedDirectories) + "/" + name, elementOffset, elementSize, nestedDirectories[nestedDirectories.size()-1]);

            temp->setContent(content);
            
            bool dontPop = nestedDirectories[nestedDirectories.size()-1]->addChild(temp);
            if(!dontPop){
                nestedDirectories.pop_back();
            }
            pathMap.insert({temp->path, temp});
            paths.push_back(temp->path);

        }
    }
    fixChildren(&root);
}
void fixChildren(Dir* root){
    //starting at root, ensure that each node that has children does not hold a pointer to itself in children
    //if it does, remove it
    vector<FileEntity*> children = root->children;
    for(int i = 0; i<children.size(); i++){
        if(children[i] == root){
            root->children.erase(root->children.begin() + i);
        }
    }
    //now iterate again to recursive call if the type of the child is dir or namespace_dir
    for(int i = 0; i<root->children.size(); i++){
        if(root->children[i]->type == "dir"){
            fixChildren(static_cast<Dir*>(root->children[i]));
        }
        if(root->children[i]->type == "namespace_dir"){
            fixChildren(static_cast<Dir*>(root->children[i]));
        }
    }

}
bool checkMapDir(string name){
    //check if the name is a map_dir
    if(name.size() == 4 && name.substr(0, 1) == "E" && name.substr(2, 1) == "M" &&
        isdigit(name[1]) && isdigit(name[3])){

        return true;
    }
    return false;
}
FileEntity::~FileEntity(){
    
}


bool Wad::isPath(const string& path){
    string tempPath = path;
    //remove last character of path if it is a / and the string is not just /
    if(path.size()>=1 && path[path.size()-1] == '/' && path != "/"){
        tempPath = path.substr(0, path.size()-1);
    }
    return pathMap.count(tempPath) != 0;
}
bool Wad::isContent(const string& path){
   string tempPath = path;
    //remove last character of path if it is a / and the string is not just /
    if(path.size()>=1 && path[path.size()-1] == '/' && path != "/"){
        tempPath = path.substr(0, path.size()-1);
    }
    if(isPath(tempPath)){
        //check if the type of the thing stored here is File
        if(pathMap[tempPath]->type == "file"){
            return true;
        }
    }
    return false;
}
bool Wad::isDirectory(const string& path){
    string tempPath = path;
    //remove last character of path if it is a / and the string is not just /
    if(path.size()>=1 && path[path.size()-1] == '/' && path != "/"){
        tempPath = path.substr(0, path.size()-1);
    }
    if(isPath(tempPath)){
        //check if the type of the thing stored here is not a File - if not File it's dir
        if(pathMap[tempPath]->type != "file"){
            return true;
        }
    }
    return false;
}
int Wad::getSize(const string &path){
    if(isContent(path)){
        return pathMap[path]->elementSize;
    }
    return -1;
}
int Wad::getContents(const string& path, char* buffer, int length, int offset){
    if(isContent(path)){
        File* file = static_cast<File*>(pathMap[path]);
        //check if the offset is within the bounds of the file
        if(offset >= pathMap[path]->elementSize){
            return 0;
        }
        //check if the offset + length is within the bounds of the file
        if(offset + length > pathMap[path]->elementSize){
            //set the length to as high as it can be without going out of bounds 
            length = pathMap[path]->elementSize - offset;
            if(length<0){
                length = 0;
            }
        }
        //copy the contents of the file into the buffer
        for(int i = 0; i<length; i++){
            buffer[i] = file->content[i + offset];
        }
        return length;
    }
    return -1;
}
int Wad::getDirectory(const string &path, vector<string> *directory){
    //remove last character of path if it is a / 
    if(path[path.size()-1] == '/' && path != "/"){
        string temp = path.substr(0, path.size()-1);
        return getDirectory(temp, directory);
    }
    if(isDirectory(path)){
        Dir* dir = static_cast<Dir*>(pathMap[path]);
        //iterate through the children of the directory and add their names to the vector
        for(int i = 0; i<dir->children.size(); i++){
            directory->push_back(dir->children[i]->name);
        }
        return dir->children.size();
    }
    return -1;
}
void Wad::createFile(const string &path){
    string tempPath = path;
    if(path[path.size()-1] == '/' && path != "/"){
        tempPath = path.substr(0, path.size()-1);
    }
    string dirPath = tempPath.substr(0, tempPath.find_last_of("/"));
    if(dirPath == ""){
        dirPath = "/";
    }
    //check if dirPath exists
    if(!isDirectory(dirPath) || pathMap[dirPath]->type == "map_dir"){
        return;
    }
    else{
        //check if the path already exists
        if(isPath(tempPath)){
            return;
        }
        Dir* dir = static_cast<Dir*>(pathMap[dirPath]);
        
        string name = path.substr(path.find_last_of("/")+1);
        //validate name
        if(name.size()>8 || name.size() == 0 || (checkMapDir(name))){
            return;
        }
        

        //create the file
        File* temp = new File(name, path, 0, 0, pathMap[dirPath]);
       
        
        //add it to the parent directory
        dir->children.push_back(temp);
        //add it to the pathMap
        pathMap.insert({temp->path, temp});
        bool isRoot = false;
        if(dir->path == "/"){
            isRoot = true;
        }

        //get the index of the end of the parent directory from parent itself
        int index = dir->endIndex;
        
        //insert the new directory into the fileNames vector before the end of the parent directory - or at end of the parent directory is root
        if(!isRoot){
            fileNames.insert(fileNames.begin() + index, temp->name);
            paths.push_back(temp->path);
            //change end indexes by 1 if behind the new file
            incrementEndIndex(index);
        }else{
            fileNames.push_back(temp->name);
            paths.push_back(temp->path);
        }

        //now edit the actual file itself - interact with what's at actualFilePath
        //open the file
        fstream file(actualyFilePath, std::ios::binary | std::ios::in | std::ios::out);  
        if(!file.is_open()){
            throw "File not found at " + actualyFilePath + ". ";
        }
        //add 2 to the list of descriptors in the file
        numDescriptors += 1;
        file.seekp(4, ios::beg);
        file.write(reinterpret_cast<char*>(&numDescriptors), 4);
        file.close();
        file.open(actualyFilePath, std::ios::in | std::ios::out);
        char holding[16];
        
        if(isRoot){
            //put it at the very end of the file - no need to move anything
                //-1 because haven't written it yet
            file.seekp((numDescriptors-1)*16+descriptorOffset, ios::beg);
        }else{
            //for each directory after where the new one should go, move it down by 16 bytes
            for(int i = fileNames.size() - 1; i >= index + 1; i--){
                //get the name of the directory
                //get the offset of the directory
                file.seekg(descriptorOffset + (i-1)*16, ios::beg);
                file.read(holding, 16);
                //write the offset of the directory 16 bytes down
                file.seekp(descriptorOffset + (i)*16), ios::beg;
                file.write(holding, 16);   
            }
            //put it at the end of the parent directory - where it used to be 
            file.seekp((index*16+ descriptorOffset), ios::beg);
        }
        //now that seekp is in right spot and we moved everything, write the new descriptors
        file.write(reinterpret_cast<char*>(&temp->elementOffset), 4);
        file.write(reinterpret_cast<char*>(&temp->elementSize), 4);
        file.write((temp->name ).c_str(), 8);
        file.close();

        

        return;
    }
}
void Wad::createDirectory(const string &path){
   //remove the path except for past the last /
   //strip the last character if it is a /
    string tempPath = path;
    if(path[path.size()-1] == '/' && path != "/"){
        tempPath = path.substr(0, path.size()-1);
    }
    string dirPath = tempPath.substr(0, tempPath.find_last_of("/"));
    if(dirPath == ""){
        dirPath = "/";
    }
    //check if dirPath exists
    if(!isDirectory(dirPath) || pathMap[dirPath]->type == "map_dir"){
        return;
    }
    else{
        //check if the path already exists
        if(isPath(tempPath)){
            return;
        }
        Dir* dir = static_cast<Dir*>(pathMap[dirPath]);
        //create the directory
        //get off set from the end offset of the parent directory
        Namespace_Dir* temp = new Namespace_Dir(tempPath.substr(tempPath.find_last_of("/")+1), tempPath, dir->elementOffset, 0, pathMap[dirPath]);
        //add it to the parent directory
        if(temp->name.size() >2){
            return;
        }
        dir->children.push_back(temp);
        //add it to the pathMap
        pathMap.insert({temp->path, temp});
        bool isRoot = false;
        if(dir->name == ""){
            isRoot = true;
        }
        //get the index of the end of the parent directory from the parent
        int index = dir->endIndex;

        
        //insert the new directory into the fileNames vector before the end of the parent directory - or at end of the parent directory is root
        if(!isRoot){
            fileNames.insert(fileNames.begin() + index, temp->name + "_START");
            fileNames.insert(fileNames.begin() + index + 1, temp->name + "_END");
            //change end indexes by 2 if behind the new node
            incrementEndIndex(index, 2);
            temp->endIndex = index + 1;
        }else{
            temp->endIndex = numDescriptors + 1;
            fileNames.push_back(temp->name + "_START");
            fileNames.push_back(temp->name + "_END");
        }

        //now edit the actual file itself - interact with what's at actualFilePath
        //open the file
        fstream file(actualyFilePath, std::ios::binary | std::ios::in | std::ios::out);  
        if(!file.is_open()){
            throw "File not found at " + actualyFilePath + ". ";
        }
        //add 2 to the list of descriptors in the file
        numDescriptors += 2;
        file.seekp(4, ios::beg);
        file.write(reinterpret_cast<char*>(&numDescriptors), 4);
        file.close();
        file.open(actualyFilePath, std::ios::in | std::ios::out);
        //move the data after the new directory down by 16 bytes - repeat until no more directories
        char holding[16];
        
        if(isRoot){
            //put it at the very end of the file - no need to move anything
                //-2 because haven't written them yet
            file.seekp((numDescriptors-2)*16+descriptorOffset, ios::beg);
        }else{
            //for each directory after where the new one should go, move it down by 32 bytes
            for(int i = fileNames.size() - 1; i >= index + 2; i--){
                //get the name of the directory
                //get the offset of the directory
                file.seekg(descriptorOffset + (i-2)*16, ios::beg);
                file.read(holding, 16);
                //write the offset of the directory 32 bytes down
                file.seekp(descriptorOffset + (i)*16), ios::beg;
                file.write(holding, 16);   
            }
            //put it at the end of the parent directory - where it used to be 
            file.seekp((index*16+ descriptorOffset), ios::beg);
        }
        //now that seekp is in right spot and we moved everything, write the new descriptors
        file.write(reinterpret_cast<char*>(&temp->elementOffset), 4);
        file.write(reinterpret_cast<char*>(&temp->elementSize), 4);
        file.write((temp->name + "_START").c_str(), 8);
        file.write(reinterpret_cast<char*>(&temp->elementOffset), 4);
        file.write(reinterpret_cast<char*>(&temp->elementSize), 4);
        file.write((temp->name + "_END").c_str(), 8);


        
        file.close();
        return;
    }
}

int Wad::writeToFile(const string &path, const char *buffer, int length, int offset){
    //fix path to not have the / at end if it does
    string tempPath = path;
    if(path[path.size()-1] == '/' && path != "/"){
        string tempPath = path.substr(0, path.size()-1);
        return writeToFile(tempPath, buffer, length, offset);
    }
    
    if(!isContent(path)){
        return -1;
    }
    File* temp = static_cast<File*>(pathMap[path]);
    if (temp->content != nullptr){
        //if nonempty, return 0
        return 0;
    }
    if(offset == 0){
        //generate a new offset (just use old descriptor offset)
        offset = descriptorOffset;
        //push the descriptor offset back by length bytes
        pushDescriptorBack(length);
    }
    //write the new information to the file
    fstream file = fstream(actualyFilePath, ios::binary | ::ios::in | std::ios::out);
    if(!file.is_open()){
        throw "File not found at " + actualyFilePath + ". ";
    }
    //save the buffer in the File obj
    char* content = new char[length];
    for(int i = 0; i<length; i++){
        content[i] = buffer[i];
    }
    temp->setContent(content);
    //also change the File object in the pathMap
    temp->elementOffset = offset;
    temp->elementSize = length;
    //write the new information to the file
    file.seekp(offset, ios::beg);
    file.write(buffer, length);
    //now edit the descriptor in the file itself - interact with what's at actualFilePath
    bool isRoot = false;
    if(temp->parent->name == ""){
        isRoot = true;
    }
    //if root, we look for the last descriptor with the right name
    if(isRoot){
        for(auto iter = fileNames.rbegin(); iter != fileNames.rend(); iter++){
            if(*iter == temp->name){
                //write the new offset and size to the descriptor 
                    //DESCRIPTOR OFFSET WAS CHANGED, SO DECREASE BY LENGTH
                file.seekp(descriptorOffset + ((numDescriptors -1 -(iter - fileNames.rbegin()))*16), ios::beg);
                file.write(reinterpret_cast<char*>(&offset), 4);
                file.write(reinterpret_cast<char*>(&length), 4);
                file.write((temp->name).c_str(), 8);
                break;
            }
        }
        
    }else{
        //cast parent to a namespace dir if it works
        Namespace_Dir* parent = static_cast<Namespace_Dir*>(temp->parent);
        //otherwise start at parent->endIndex
        for(int i = parent->endIndex; i > 0; i--){
            //iterate until we find the item with the right name
            if(fileNames[i] == temp->name){
                //write the new offset and size to the descriptor
                file.seekp(descriptorOffset + i*16, ios::beg);
                file.write(reinterpret_cast<char*>(&offset), 4);
                file.write(reinterpret_cast<char*>(&length), 4);
                file.write((temp->name).c_str(), 8);
                break;
            }
        }
    }
    
    file.close();
    return length;
}
void Wad::pushDescriptorBack(unsigned numberOfBytes){
    //starting at the end of the file, move everything back by numberOfBytes
    //open the file
    fstream file(actualyFilePath, std::ios::binary | std::ios::in | std::ios::out);
    if(!file.is_open()){
        throw "File not found at " + actualyFilePath + ". ";
    }
    //move data of descriptors down number of bytes, then push descriptor offset back by number of bytes
    char holding[16];
    for(int i = fileNames.size() - 1; i >= 0; i--){
        //get the data into holding, then move it down by numberOfBytes
        file.seekg(descriptorOffset + (i)*16, ios::beg);
        file.read(holding, 16);
        file.seekp(descriptorOffset + (i)*16 + numberOfBytes, ios::beg);
        file.write(holding, 16);
    }
    //update the descriptor offset
    descriptorOffset += numberOfBytes;
    //now update it in the file
    file.seekp(8, ios::beg);
    file.write(reinterpret_cast<char*>(&descriptorOffset), 4);
    file.close();
    return;
}
string Wad::getMagic(){
    return magic;
}


FileEntity::FileEntity(){
    this->name = "";
    this->path = "";
    this->elementOffset = 0;
    this->elementSize = 0;
    this->parent = nullptr;
}
FileEntity::FileEntity(string name, string path, unsigned elementOffset,
unsigned elementSize, FileEntity* parent){
    this->name = name;
    this->path = path;
    this->elementOffset = elementOffset;
    this->elementSize = elementSize;
    this->parent = parent;
}
bool Dir::addChild(FileEntity* child){
    this->children.push_back(child);
    return true;
}
Dir::Dir(){
    this->name = "";
    this->path = "";
    this->elementOffset = 0;
    this->elementSize = 0;
    this->parent = nullptr;
    type = "dir";
}
Dir::Dir(string name, string path, unsigned elementOffset,
unsigned elementSize, FileEntity* parent){
    this->name = name;
    this->path = path;
    this->elementOffset = elementOffset;
    this->elementSize = elementSize;
    this->parent = parent;
    type = "dir";
}

Dir::~Dir(){
    for(int i = 0; i<children.size(); i++){
        if (children[i] != nullptr && children[i] != this){
            delete children[i];
        }
        children[i] = nullptr;
    }
}
Namespace_Dir::Namespace_Dir(string name, string path, unsigned elementOffset,
unsigned elementSize, FileEntity* parent){
    this->name = name;
    this->path = path;
    this->elementOffset = elementOffset;
    this->elementSize = elementSize;
    this->parent = parent;
    type = "namespace_dir";
}
Map_Dir::Map_Dir(string name, string path, unsigned elementOffset,
unsigned elementSize, FileEntity* parent){
    this->name = name;
    this->path = path;
    this->elementOffset = elementOffset;
    this->elementSize = elementSize;
    this->parent = parent;
    this->count = 10;
    type = "map_dir";

}
bool Map_Dir::addChild(FileEntity* child){
    this->children.push_back(child);
    this->count--;
    if(this->count == 0){
        return false;
    }
    return true;
}
File::~File(){
    if(content != nullptr){
        delete[] content;
        content = nullptr;
    }
}
File::File(string name, string path, unsigned elementOffset,
unsigned elementSize, FileEntity* parent){
    this->name = name;
    this->path = path;
    this->elementOffset = elementOffset;
    this->elementSize = elementSize;
    this->parent = parent;
    type = "file";
}
void File::setContent(char* content){
    this->content = content;
    return;
}
void Wad::incrementEndIndex(int index, int amount){
    // Iterate over the map and if it is a namespace dir, increment end index by amount if current index is at or after the end index
    for(auto iter = pathMap.begin(); iter != pathMap.end(); iter++){
        if(iter->second->type == "namespace_dir"){
            Namespace_Dir* nsDir = static_cast<Namespace_Dir*>(iter->second);
            if(index <= nsDir->endIndex) {
                nsDir->endIndex += amount;
            }
        }
    }
}

//TESTING STUFF
void Wad::printEndIndex(string path){
    if(isDirectory(path)){
        Dir* dir = static_cast<Dir*>(pathMap[path]);
        cout << path << ": " << dir->endIndex << endl;
    }
}
void Wad::printMap(){
    for(auto it = pathMap.begin(); it != pathMap.end(); it++){
        cout << it->first << endl;
    }
}
//print flattened - for debugging
void Wad::printFlattened(){
    for(int i = 0; i<fileNames.size(); i++){
        cout << fileNames[i] << endl;
    }
}


// int main(){
//     myTest5();
//     return 0;
// }















