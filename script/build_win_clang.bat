call gn gen out/clang_x86 --args="import(\"//yealink/build/args/all.gni\") is_clang=true target_cpu=\"x86\" is_debug=false"
call gn gen out/clang_x86_debug --args="import(\"//yealink/build/args/all.gni\") is_clang=true target_cpu=\"x86\" is_debug=true"

call gn gen out/clang_x64--args="import(\"//yealink/build/args/all.gni\") is_clang=true target_cpu=\"x64\" is_debug=false"
call gn gen out/clang_x64_debug --args="import(\"//yealink/build/args/all.gni\") is_clang=true target_cpu=\"x64\" is_debug=true"

call ninja -C out/clang_x86
call ninja -C out/clang_x86 yealink

call ninja -C out/clang_x86_debug
call ninja -C out/clang_x86_debug yealink

call ninja -C out/clang_x64
call ninja -C out/clang_x64 yealink

call ninja -C out/clang_x64_debug
call ninja -C out/clang_x64_debug yealink
