include_directories(
    DataUtility
    Location
    Pair
    Point
    RenjuGroup
)

file(GLOB_RECURSE DataModelSourceFiles "*.c")

add_library(datamodel STATIC ${DataModelSourceFiles})