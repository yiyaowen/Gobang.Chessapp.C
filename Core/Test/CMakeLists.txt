include_directories(${PROJECT_SOURCE_DIR}/Src)

link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(CoreTest CoreTest.c)

target_link_libraries(CoreTest core)

install(TARGETS CoreTest
    RUNTIME DESTINATION bin
)
