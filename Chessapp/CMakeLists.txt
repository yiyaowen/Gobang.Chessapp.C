include_directories(${CORE_PATH}/Interface)

file(GLOB_RECURSE c_src_files . *.c)

add_executable(Main
    ${c_src_files}
)

target_link_libraries(Main
    core
)
