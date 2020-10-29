file(GLOB_RECURSE c_src_files ./*.c)

file(GLOB_RECURSE c_header_files ./*.h)

add_library(core_shared SHARED ${c_src_files})
add_library(core_static STATIC ${c_src_files})

set_target_properties(core_shared PROPERTIES OUTPUT_NAME "core")
set_target_properties(core_static PROPERTIES OUTPUT_NAME "core")

install(TARGETS core_shared core_static
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(FILES ${c_header_files} DESTINATION include)
