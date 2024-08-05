#########################################################################
# File Name: build.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: Fri Jun 14 17:01:09 2024
#########################################################################
#!/bin/bash

PLATFORM=x86
echo -e "Choose the target platform:"
echo -e "\t0. X64 \n\t1. R16 \n\t2. R328"

num=0
# read -t 10 num
if [[ $num -eq 0 ]]; then
	PLATFORM=x64
elif [[ $num -eq 1 ]]; then
	PLATFORM=R16
elif [[ $num -eq 2 ]]; then
	PLATFORM=R328
else
	echo -e "Input the num: $num invalid"
	exit 0
fi

echo -e "Choose the build type: \n\t0. Debug (Default)\n\t1. Release"
TYPE="Debug"
# read -t 10 num
if [[ $num -eq 0 ]]; then
	TYPE="Debug"
elif [[ $num -eq 1 ]]; then
	TYPE="Relase"
else
	echo -e "Input the num: $num invalid"
fi

echo -e "Clear the cache? Y:Yes; N:No"
read -t 5 clear
if [[ $clear == "Y" || $clear == "y" || $clear == "Yes" || $clear == "yes" ]]; then
	echo "Remove the build dir"
	rm ./build -rf
fi

# Add the build directory
if [[ ! -d build/$PLATFORM ]]; then
	mkdir -p build/$PLATFORM
fi
cd build/$PLATFORM

# cmake
cmake -D BUILD_TYPE="$TYPE" -D CMAKE_TOOLCHAIN_FILE="../../toolchain/${PLATFORM}.cmake" ../..

make -j4
