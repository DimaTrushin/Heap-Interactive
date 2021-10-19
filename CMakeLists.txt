cmake_minimum_required(VERSION 3.5)

project(HeapInteractive LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(HeapInteractive main.cpp Application.cpp HeapPrinter.cpp Colorizor.cpp)
