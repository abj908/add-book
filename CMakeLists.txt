cmake_minimum_required(VERSION 3.10)

project(AddressBook)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(address_book src/main.cpp src/address_book.cpp)
add_executable(address_book_tests tests/address_book_tests.cpp src/address_book.cpp)

target_link_libraries(address_book_tests gtest gtest_main pthread)

set(CMAKE_BUILD_TYPE Debug)