qt_add_library(core_module STATIC
    BinarySearchTree.h
    BinarySearchTree.cpp
)
target_include_directories(core_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
