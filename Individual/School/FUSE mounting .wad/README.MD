##FOR LINUX DISTROS 
#WHAT IT DOES
mounts a wad formatted file as if it is a file system in linux. Allows you to easily edit and access info in a .wad file

#QUICKSTART GUIDE
download the wadfs.tar.gz 
unzip it 
$ tar -xzf wadfs.tar.gz
then run mount_wad.sh 
$chmod +x mount_wad.sh & ./mount_wad.sh

#USES 
mount_wad.sh [wad path] - mounts a file at a given path as a dir using FUSE
mount_wad.sh - mounts ./wadFiles/sample1.wad
    *NOTE: sample1.wad is reset each time mount_wad.sh is run
./wadfs/wadfs [threading tag] [wad file to mount] [mount dir] - more advanced use. Allows you set threading tag and mount dir as well as file to mount

#CODE
libWad - object-based approach to hold .wad data in memory and manipulate it 
wadfs - fuse daemon for utilizing libWad
wadFiles - basic folder for holding wadFiles 
mountdir - created by mount_wad.sh. Just a mounting directory

#NOTES
You can only make files that conform to wad file naming conventions (<=8 chars) and dir that conform to wad namespacedir naming conventions (<=2 characters)