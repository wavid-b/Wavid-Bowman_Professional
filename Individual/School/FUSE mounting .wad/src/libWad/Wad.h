#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
struct FileEntity{
    string type;
    FileEntity* parent; //null if root
    string name;
    string path;
    unsigned elementOffset;
    unsigned elementSize;
    FileEntity();
    FileEntity(string name, string path, unsigned elementOffset,
        unsigned elementSize, FileEntity* parent = nullptr);
    virtual ~FileEntity();
};
struct Dir : FileEntity{
    int endIndex = 0;
    vector<FileEntity*> children;
    //inherit the constructor
    Dir(string name, string path, unsigned elementOffset,
        unsigned elementSize, FileEntity* parent = nullptr);
        //need addChild to add children to the vector - different for map_dir
    virtual bool addChild(FileEntity* child);  
    ~Dir(); 
    Dir(); 
};
struct File : FileEntity{
    //inherit the constructor
    char* content = nullptr;
    File(string name, string path, unsigned elementOffset,
        unsigned elementSize, FileEntity* parent = nullptr);
    void setContent(char* content);
    ~File();
};
struct Namespace_Dir : Dir{
    Namespace_Dir(string name, string path, unsigned elementOffset,
        unsigned elementSize, FileEntity* parent = nullptr);
    using Dir::addChild;
    
};
struct Map_Dir : Dir{
    int count;
    Map_Dir(string name, string path, unsigned elementOffset,
        unsigned elementSize, FileEntity* parent = nullptr);
    bool addChild(FileEntity* child);
};
class Wad{
    string actualyFilePath;
    Dir root; 
    string magic;
    unsigned numDescriptors;
    unsigned descriptorOffset;
    vector<string> paths;
    vector<string> fileNames; 
    unordered_map<string, FileEntity*> pathMap;
    void incrementEndIndex(int index, int amount = 1);
public:
    void printEndIndex(string path);
    Wad(string path);
    static Wad* loadWad(const string& path);
    bool isPath(const string& path);
    bool isContent(const string& path);
    bool isDirectory(const string& path);
    //create a thing that accesses the FileEntity at a given path
    string getMagic();
    int getSize(const string &path);
    int getContents(const string &path, char *buffer, int length, int offset = 0);
    int getDirectory(const string &path, vector<string> *directory);
    void createDirectory(const string &path);
    void createFile(const string &path);
    int writeToFile(const string &path, const char *buffer, int length, int offset = 0);
    void printFlattened();
    void printMap();
    void pushDescriptorBack(unsigned numberOfBytes);
};


