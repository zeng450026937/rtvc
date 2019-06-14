#!/bin/bash

gn gen out/arm64 --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"arm64\" target_os=\"ios\" is_debug=false ios_enable_code_signing=false"
gn gen out/arm64_debug --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"arm64\" target_os=\"ios\" is_debug=true ios_enable_code_signing=false"

gn gen out/arm --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"arm\" target_os=\"ios\" is_debug=false ios_enable_code_signing=false"
gn gen out/arm_debug --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"arm\" target_os=\"ios\" is_debug=true ios_enable_code_signing=false"

ninja -C out/arm64/
ninja -C out/arm64/ yealink

ninja -C out/arm64_debug/
ninja -C out/arm64_debug/ yealink

ninja -C out/arm/
ninja -C out/arm/ yealink

ninja -C out/arm_debug/
ninja -C out/arm_debug/ yealink

rm -r -f -d out/combined_debug
rm -r -f -d out/combined

mkdir out/combined_debug
mkdir out/combined

./yealink/script/combine_libraries.sh out/arm_debug/obj/ out/arm64_debug/obj/ out/combined_debug
./yealink/script/combine_libraries.sh out/arm/obj/ out/arm64/obj/ out/combined/

./yealink/script/combine_libraries.sh out/arm_debug/obj/yealink/ out/arm64_debug/obj/yealink/ out/combined_debug
./yealink/script/combine_libraries.sh out/arm/obj/yealink/ out/arm64/obj/yealink/ out/combined/
