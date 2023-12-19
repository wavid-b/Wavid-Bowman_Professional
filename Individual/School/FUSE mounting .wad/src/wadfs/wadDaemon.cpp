//using open source code from fntlnz/fuse-example

#define FUSE_USE_VERSION 26

#include <string.h>
#include <fuse.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "../libWad/Wad.h"

using namespace std;
static int getattr_callback(const char *path, struct stat *stbuf)
{
    string pathStr(path);
    Wad* myWad = (Wad*)fuse_get_context()->private_data;
    if(myWad->isDirectory(pathStr))
    {
        stbuf->st_mode = S_IFDIR | 0777;
        stbuf->st_nlink = 2;
        return 0;
    }
    else
    {
        if(myWad->isContent(pathStr))
        {
            stbuf->st_mode = S_IFREG | 0777;
            stbuf->st_nlink = 1;
            stbuf->st_size = myWad->getSize(pathStr);
            return 0;
        }
        else
        {
            return -ENOENT;
        }
    }
}

static int read_callback(const char *path, char *buf, size_t size, off_t offset,
    struct fuse_file_info *fi) {
    string pathStr(path);
    int output;
    Wad* myWad = (Wad*)fuse_get_context()->private_data;
    if(myWad->isContent(pathStr))
    {
        output = myWad->getContents(pathStr, buf, size, offset);
        return output;
    }
    else
    {
        return -ENOENT;
    }
}
static int write_callback(const char *path, const char *buf, size_t size, off_t offset,
    struct fuse_file_info *fi) {
    string pathStr(path);
    int output;
    Wad* myWad = (Wad*)fuse_get_context()->private_data;
    if(myWad->isContent(pathStr))
    {
        output = myWad->writeToFile(pathStr, buf, size, offset);
        return output;
    }
    else
    {
        return -ENOENT;
    }
}
static int mknod_callback(const char *path, mode_t mode, dev_t dev) {
    string pathStr(path);
    Wad* myWad = (Wad*)fuse_get_context()->private_data;

    if(myWad->isDirectory(pathStr))
    {
        return -EEXIST;
    }
    else if (myWad->isContent(pathStr))
    {
        return -EEXIST;
    }
    else
    {
        myWad->createFile(pathStr);
        return 0;
    }
}
static int mkdir_callback(const char *path, mode_t mode) {
    string pathStr(path);
    Wad* myWad = (Wad*)fuse_get_context()->private_data;

    if(myWad->isDirectory(pathStr))
    {
        return -EEXIST;
    }
    else if (myWad->isContent(pathStr))
    {
        return -EEXIST;
    }
    else
    {
        myWad->createDirectory(pathStr);
        return 0;
    }
}
static int readdir_callback(const char *path, void *buf, fuse_fill_dir_t filler,
    off_t offset, struct fuse_file_info *fi) {
    string pathStr(path);
    Wad* myWad = (Wad*)fuse_get_context()->private_data;
    vector<string> directory;
    if(myWad->isDirectory(pathStr))
    {
        myWad->getDirectory(pathStr, &directory);
        filler(buf, ".", NULL, 0);
        filler(buf, "..", NULL, 0);
        for(int i = 0; i < directory.size(); i++)
        {
            filler(buf, directory[i].c_str(), NULL, 0);
        }
        return 0;
    }
    else
    {
        return -ENOENT;
    }
}
static int open_callback(const char *path, struct fuse_file_info *fi) {
  return 0;
}
static int close_callback(const char *path, struct fuse_file_info *fi) {
  return 0;
}

static struct fuse_operations operations = {
    .getattr = getattr_callback,
    .mknod = mknod_callback,
    .mkdir = mkdir_callback,
    .open = open_callback,
    .read = read_callback,
    .write = write_callback,
    .release = close_callback,
    .readdir = readdir_callback,
};
int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Usage: %s <wad file> <mount point>\n", argv[0]);
        exit(EXIT_SUCCESS);
    }
    //
    string wadPath = argv[argc - 2];
    if(wadPath.at(0) != '/'){
        wadPath = string(get_current_dir_name()) + "/" + wadPath;
    }
    Wad* myWad = Wad::loadWad(wadPath);

    //augment whats in the CLI, we just want flags and a mount directory
    argv[argc - 2] = argv[argc - 1];
    argc--;

    //fuse_get_context()->private_data 
    return fuse_main(argc, argv, &operations, myWad);
}