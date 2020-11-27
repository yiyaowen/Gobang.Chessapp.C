file(GLOB_RECURSE c_header_files ./*.h)

install(FILES ${c_header_files} DESTINATION Interface)
