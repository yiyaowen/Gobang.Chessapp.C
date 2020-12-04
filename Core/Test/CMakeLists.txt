include_directories(${CORE_PATH}/Interface)

add_executable(CoreTest CoreTest.c)

target_link_libraries(CoreTest core)
