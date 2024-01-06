cmake_minimum_required(VERSION 3.14)

project(test_bits LANGUAGES CXX)

include(GoogleTest)

add_executable(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/test_bit_base.cpp
    ${CMAKE_CURRENT_LIST_DIR}/test_bit_buffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/test_bit_signal.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

target_link_libraries(${PROJECT_NAME} gtest_main gtest pthread Core::bits)

add_test(${PROJECT_NAME} ${PROJECT_NAME})
