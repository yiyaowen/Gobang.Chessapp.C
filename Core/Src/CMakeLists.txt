file(GLOB_RECURSE c_src_files . *.c)

add_library(core SHARED ${c_src_files})
