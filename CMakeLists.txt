cmake_minimum_required(VERSION 3.13)

project(bits VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)

add_library(${PROJECT_NAME}_${PROJECT_VERSION} STATIC)
add_library(
    Core::${PROJECT_NAME}_${PROJECT_VERSION}
    ALIAS ${PROJECT_NAME}_${PROJECT_VERSION}
    )

target_sources(
    ${PROJECT_NAME}_${PROJECT_VERSION}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/bit_base.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/bit_signal_data.cpp
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/inc/bits
    )

target_include_directories(
    ${PROJECT_NAME}_${PROJECT_VERSION}
    PUBLIC
    $<INSTALL_INTERFACE:inc>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    )

set_target_properties(
    ${PROJECT_NAME}_${PROJECT_VERSION}
    PROPERTIES
    PREFIX
    ""
    EXPORT_NAME
    ${PROJECT_NAME}_${PROJECT_VERSION}
    )

export(
    TARGETS ${PROJECT_NAME}_${PROJECT_VERSION}
    NAMESPACE Core::
    FILE ${PROJECT_NAME}_${PROJECT_VERSION}Config.cmake
    )

export(PACKAGE ${PROJECT_NAME}_${PROJECT_VERSION})

# Link library
target_link_libraries(${PROJECT_NAME}_${PROJECT_VERSION})

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Generic")

    if (BUILD_SUBMODULE_TESTS)

        enable_testing()

        add_subdirectory(test)

    endif()

endif()
