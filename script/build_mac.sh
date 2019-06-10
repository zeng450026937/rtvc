#!/bin/bash

gn gen out/x64 --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"x64\" is_debug=false"
gn gen out/x64_debug --args="import(\"//yealink/build/args/all.gni\") target_cpu=\"x64\" is_debug=true"

ninja -C out/x64 yealink
ninja -C out/x64_debug/ yealink
