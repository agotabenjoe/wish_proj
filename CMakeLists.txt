cmake_minimum_required(VERSION 3.20)
project(wish_proj)

set(CMAKE_CXX_STANDARD 98)

add_executable(wish_proj main.cpp  memtrace.cpp List.cpp ListElement.cpp String.cpp User.cpp UserList.cpp Wish.cpp WishList.cpp Array.hpp memtrace.h gtest_lite.h List.hpp ListElement.hpp String.hpp User.hpp UserList.hpp Wish.hpp WishList.hpp AuthMenu.hpp Menu.hpp JSONParser.cpp)
