#!/bin/bash
echo "running test_wadfs.sh - mounting the wadfs file system"
# Change permissions of /dev/fuse
sudo chmod 666 /dev/fuse
#installing dependencies
echo "installing dependencies"
sudo apt install g++
sudo apt install libfuse-dev fuse
# Navigate to the wadfs and libWad directories and run make
cd ./libWad
make
cd ../wadfs
make

# Navigate to the Sample directory and refresh files
cd ../wadFiles
#unzip the tar in the folder to reset the files
tar -xf wadFiles.tar.gz
cd ..
echo "creating mount directory - mountdir"
mkdir mountdir
echo "running wadfs"
#run wadfs
#if no arguments are passed, default to sample1.wad
WAD_FILE=${1:-wadFiles/sample1.wad}
./wadfs/wadfs -s $WAD_FILE ./mountdir

# tell user you are good to go
echo "File system mounted at ./mountdir"

