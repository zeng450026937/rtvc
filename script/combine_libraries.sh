#!/bin/sh
#
# Combine libraries of matching names but different architectures from directory $1 and directory $2 
# into directory $3.
#
# Usage:
#   =>  combine_matching_static_libraries.sh DIR_INPUT_1 DIR_INPUT_2 DIR_OUTPUT
###### 

pushd $1
    libraries=(*.a)
popd

echo "Matching up ${libraries[*]}..."

for library in ${libraries[*]}
do
    lipo -create "${1}/${library}" "${2}/${library}" -o "${3}/${library}"
    lipo -info "${3}/${library}"
done
