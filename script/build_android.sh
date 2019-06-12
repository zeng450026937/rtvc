#!/bin/bash

gn gen out/android_x86/ --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"x86\" target_os=\"android\" is_debug=false"
gn gen out/android_x86_debug/ --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"x86\" target_os=\"android\" is_debug=true"

gn gen out/android_x64/ --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"x64\" target_os=\"android\" is_debug=false"
gn gen out/android_x64_debug --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"x64\" target_os=\"android\" is_debug=true"

gn gen out/android_arm --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"arm\" target_os=\"android\" is_debug=false"
gn gen out/android_arm_debug --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"arm\" target_os=\"android\" is_debug=true"

gn gen out/android_arm64 --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"arm64\" target_os=\"android\" is_debug=false"
gn gen out/android_arm64_debug --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"arm64\" target_os=\"android\" is_debug=true"

ninja -C out/android_x86/ yealink
ninja -C out/android_x86_debug/ yealink

ninja -C out/android_x64/ yealink
ninja -C out/android_x64_debug/ yealink

ninja -C out/android_arm/ yealink
ninja -C out/android_arm_debug/ yealink

ninja -C out/android_arm64/ yealink
ninja -C out/android_arm64_debug/ yealink
