#!/bin/bash

gn gen out/x86 --args="import(\"//yealink/build/args/linux.gni\") target_cpu=\"x86\" is_debug=false"
gn gen out/x86_debug --args="import(\"//yealink/build/args/linux.gni\") target_cpu=\"x86\" is_debug=true"

gn gen out/x64 --args="import(\"//yealink/build/args/linux.gni\") target_cpu=\"x64\" is_debug=false"
gn gen out/x64_debug --args="import(\"//yealink/build/args/linux.gni\") target_cpu=\"x64\" is_debug=true"

ninja -C out/x86/
ninja -C out/x86/ yealink

ninja -C out/x86_debug/
ninja -C out/x86_debug/ yealink

ninja -C out/x64/
ninja -C out/x64/ yealink

ninja -C out/x64_debug/
ninja -C out/x64_debug/ yealink
