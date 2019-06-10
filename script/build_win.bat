call gn gen out/clang_x86_debug --args="import(\"//yealink/build/args/all.gni\") is_clang=true target_cpu=\"x86\" is_debug=true"
call gn gen out/clang_x86_release --args="import(\"//yealink/build/args/all.gni\") is_clang=true target_cpu=\"x86\" is_debug=false"

call gn gen out/clang_x64_debug --args="import(\"//yealink/build/args/all.gni\") is_clang=true target_cpu=\"x64\" is_debug=true"
call gn gen out/clang_x64_release --args="import(\"//yealink/build/args/all.gni\") is_clang=true target_cpu=\"x64\" is_debug=false"

call gn gen out/msvc_x86_debug --args="import(\"//yealink/build/args/all.gni\") is_clang=false target_cpu=\"x86\" is_debug=true"
call gn gen out/msvc_x86_release --args="import(\"//yealink/build/args/all.gni\") is_clang=false target_cpu=\"x86\" is_debug=false"

call gn gen out/msvc_x64_debug --args="import(\"//yealink/build/args/all.gni\") is_clang=false target_cpu=\"x64\" is_debug=true"
call gn gen out/msvc_x64_release --args="import(\"//yealink/build/args/all.gni\") is_clang=false target_cpu=\"x64\" is_debug=false"

call ninja -C out/clang_x86_debug yealink
call ninja -C out/clang_x86_release yealink

call ninja -C out/clang_x64_debug yealink
call ninja -C out/clang_x64_release yealink

call ninja -C out/msvc_x86_debug yealink
call ninja -C out/msvc_x86_release yealink

call ninja -C out/msvc_x64_debug yealink
call ninja -C out/msvc_x64_release yealink
