cmake_minimum_required(VERSION 3.14)

project(bits VERSION 1.0.0 LANGUAGES CXX)

add_library(${PROJECT_NAME})
add_library(Core::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/bit_base.cpp
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:inc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Compile for C++ 98 standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_98)

# Set the name of the exported package
set_target_properties(${PROJECT_NAME} PROPERTIES EXPORT_NAME Core)

# Register package in user's package registry
export(PACKAGE Core)

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Generic")

    if (BUILD_SUBMODULE_TESTS)

    enable_testing()

    add_subdirectory(test)

    endif()

endif()
