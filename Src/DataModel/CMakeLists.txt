file(GLOB_RECURSE DataModelSourceFiles "*.c")
file(GLOB_RECURSE DataModelHeaderFiles "*.h")

add_library(datamodel STATIC
    ${DataModelSourceFiles}
    ${DataModelHeaderFiles}
)