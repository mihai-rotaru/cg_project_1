# !/bin/bash

# update_ver.bash
# this script will:
# 1. create a backup of the main file
# 2. look up the version and build number and inject the correct values
# 3. modify the makefile, to set the executable name
# 4. will run MinGW32-make
# 5. copy back the original main file ( else, VCS will mark the working folder as dirty )
# 6. copy back the original makefile

declare file=main.cpp
declare makefile=makefile
declare create_inspection_files=false

# executable name
declare EXE_NAME=main

# store version ( git describe ) in a variable
declare VERSION=$(git describe)
echo "VERSION:    " $VERSION

# generate build name
declare BUILD_NAME=$(git describe --long --dirty --abbrev=5)

# generate executable name
EXE_NAME=$EXE_NAME"_"$(echo $BUILD_NAME | sed -e 's/^V//' -e 's/-dirty/-d/' -e 's/clean/-c/')
echo "EXE NAME: $EXE_NAME"

# generate build time and name
declare BUILD_TIME=$(date "+%a, %e %b %Y, %H:%M%p")
BUILD_NAME=$BUILD_NAME" @ "$BUILD_TIME
echo "BUILD NAME: " $BUILD_NAME

# create a copy of the main.cpp file
echo "creating a copy of $file..."
cp $file $file.tmp

# create a copy of the makefile file
echo "creating a copy of $makefile..."
cp $makefile $makefile.tmp

# check if temp files were created
if [ ! -f $file.tmp -or ! -f $makefile.tmp ] 
then
    echo "one of the backup files not detected; exiting..."
    exit 1
fi

# inject the build number into it
echo "injecting version and build numbers into $file ..."
sed -i -e "/^char VERSION\[[0-9]\+\] = / s/<unknown>/Version: $VERSION/" $file
sed -i -e "/^char BUILD_NAME\[[0-9]\+\] = / s/<unknown>/Build:   $BUILD_NAME/" $file

# inject executable name into makefile
echo "injecting executable name ( $EXE_NAME ) into $makefile ..."
sed -i -e "s/EXECUTABLE=.*/EXECUTABLE=$EXE_NAME.exe/" $makefile

# compile
MinGW32-make

# create a copy of the modified file, for inspection
if $create_inspection_files;
then
    cp $file $file.tmp.~
    cp $makefile $makefile.tmp.~
fi

# copy back temp file
echo "deleting temporary files ( $file.tmp, $makefile.tmp ) ..."
mv $file.tmp $file
mv $makefile.tmp $makefile
