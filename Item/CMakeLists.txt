cmake_minimum_required(VERSION 3.15)

set(ProjectName Item)

project(${ProjectName} CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

add_executable(${ProjectName} item.cpp item.hpp nlohman/json.hpp main.cpp)
